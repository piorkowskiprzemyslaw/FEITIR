#!/usr/bin/env bash

ORIG_DIR=`pwd`

cd ~
git clone https://github.com/Itseez/opencv.git
cd opencv
mkdir build
cd build
cmake ..
make -j4
sudo make -j4 install
cd ${ORIG_DIR}
