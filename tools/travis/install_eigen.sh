#!/usr/bin/env bash

EIGEN_VERSION=3.2.9
EIGEN_HASH=dc6cfdf9bcec

ORIG_DIR=`pwd`

cd ${HOME}
wget --quiet "http://bitbucket.org/eigen/eigen/get/${EIGEN_VERSION}.tar.gz"
tar xzf ${EIGEN_VERSION}.tar.gz
mkdir -p "eigen-eigen-${EIGEN_HASH}/_build"
cd "eigen-eigen-${EIGEN_HASH}/_build"

# Build, make and install Eigen
cmake .. -DCMAKE_INSTALL_PREFIX:STRING="$install_dir"
make
make install
cd ${ORIG_DIR}

# Check install
pkg-config --modversion "eigen3 >= ${EIGEN_VERSION}"
pkg-config --cflags "eigen3 >= ${EIGEN_VERSION}"