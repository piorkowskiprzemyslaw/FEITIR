#!/usr/bin/env bash

ORIG_DIR=`pwd`

cd ~
git clone https://github.com/Itseez/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv
mkdir build
cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules -DBUILD_opencv_legacy=OFF ..
make -j4
sudo make -j4 install
cd ${ORIG_DIR}
