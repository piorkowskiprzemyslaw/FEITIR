#!/bin/bash

fullDir="${1}";
files=($(cd ${fullDir} && ls -1v *.jpg));
counter=1
dirCounter=1

echo "Database directory: "${fullDir}
echo "Number of elements in each category: "${2}

for fileName in "${files[@]}" 
do
    if [ ${counter} == "1" ]; then
        mkdir "$fullDir/${dirCounter}";
    fi
    
    mv "$fullDir/$fileName" "$fullDir/$dirCounter"

    if [ $counter == "${2}" ]; then
        counter=1
        dirCounter=$[${dirCounter} + 1]
    else
        counter=$[${counter} + 1]
    fi
done

