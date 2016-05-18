#!/usr/bin/env bash

set -ueo pipefail

# reset getopts variable
OPTIND=1

#base project directory
CURRENT_DIR=`pwd`
SRC_DIR="$CURRENT_DIR/.."
BUILD_DIR="$CURRENT_DIR/../build"
OS=`uname -s`
CMAKE_ADDITIONAL_OPTIONS=""

if [ "$OS" == "Darwin" ]; then
    echo "Darwin build"
    CMAKE_ADDITIONAL_OPTIONS="-DCMAKE_MODULE_PATH=/opt/local/share/cmake/Modules/"
elif [ "$OS" == "Linux" ]; then
    echo "Linux build"
    CMAKE_ADDITIONAL_OPTIONS="-DBOOST_ROOT=/home/przemek/Development/boost_1_60_0/
                              -DCMAKE_MODULE_PATH=/usr/share/cmake-2.8/Modules"
fi


function build() {
    cd $BUILD_DIR
    make
}

function clean() {
    cd $BUILD_DIR
    make clean
}

function clear() {
    if [ -d "$BUILD_DIR" ]; then
        printf '%s\n' "Removing directory ($BUILD_DIR)"
        rm -rf $BUILD_DIR
    fi
    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    cmake $SRC_DIR $CMAKE_ADDITIONAL_OPTIONS
}

function run() {
    $BUILD_DIR"/src/main/"FEITIR
}

function test() {
    cd $BUILD_DIR
    ctest --output-on-failure
}

while getopts ":cbrxht" opt; do
    case "$opt" in
    c) clean
        ;;
    b) build
        ;;
    r) run
        ;;
    x) clear
        ;;
    t) test
        ;;
    h)  echo "HELP message"
        echo "-c clean"
        echo "-b build"
        echo "-r run with no command line parameters"
        echo "-x clear"
        echo "-t run tests"
        ;;
    \?) echo "unknown option"
        ;;
    esac
done

shift $((OPTIND-1))
