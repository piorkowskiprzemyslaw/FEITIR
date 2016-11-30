#!/usr/bin/env bash

EIGEN_BASELINE=eigen_3_2_9

if [ ! -d "${HOME}/${EIGEN_BASELINE}/install" ]; then

    mkdir -p "${HOME}/${EIGEN_BASELINE}"
    cd "${HOME}/${EIGEN_BASELINE}"
    wget --quiet "http://bitbucket.org/eigen/eigen/get/3.2.9.tar.gz"
    tar xzf 3.2.9.tar.gz
    mv "eigen-eigen-dc6cfdf9bcec" "eigen"
    mkdir -p "eigen/_build"
    cd "eigen/_build"

    # Build, make and install Eigen
    cmake .. -DCMAKE_INSTALL_PREFIX:STRING="${HOME}/${EIGEN_BASELINE}/install"
    make
    sudo make install

    # Check install
    pkg-config --modversion "eigen3 >= 3.2.0"
    pkg-config --cflags "eigen3 >= 3.2.0"

fi

