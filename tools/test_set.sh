#!/usr/bin/env bash

fullDatabase=${1};
baseXValidate=${2};
numberOfSets=${3};
numberOfItemsFromCategory=${4};
setsNumbers=($(seq ${numberOfSets}));

echo "Full database: "${fullDatabase}
echo "Base x validate path: "${baseXValidate}
echo "Number of sets: "${numberOfSets}
echo "Number of elements to choose from each category: "${numberOfItemsFromCategory}

categories=($(ls ${fullDatabase}));

tmpDir=($(mktemp -d))
cd ${fullDatabase}
cp -r . ${tmpDir}

# test sets
for setNo in "${setsNumbers[@]}"
do
    setDir=${baseXValidate}"/set_"${setNo}"/test"
    echo "Creating test set ${setNo} in directory ${setDir}"
    mkdir -p ${setDir}

    for category in "${categories[@]}"
    do
        mkdir -p ${setDir}"/"${category}

        cd ${tmpDir}"/"${category}

        ls |sort -R |tail -${numberOfItemsFromCategory} | while read file; do
            mv ${tmpDir}"/"${category}"/"${file} ${setDir}"/"${category}"/"
        done
    done
done

# train set
for setNo in "${setsNumbers[@]}"
do
    setDir=${baseXValidate}"/set_"${setNo}"/train"
    echo "Creating train set ${setNo} in directory ${setDir}"
    mkdir -p ${setDir}
    for category in "${categories[@]}"
    do
        mkdir -p ${setDir}"/"${category}
    done

    for otherSetNo in "${setsNumbers[@]}"
    do
        if [ ${otherSetNo} != ${setNo} ]; then
            otherSetDir=${baseXValidate}"/set_"${otherSetNo}"/test"

            for category in "${categories[@]}"
            do
                cd ${otherSetDir}"/"${category}
                cp * ${setDir}"/"${category}
            done
        fi
    done
done

rm -rf ${tmpDir}