#!/usr/bin/env bash


OPENCV_BASELINE=opencv_3_1
OPENCV_LIBRARIES=(
libopencv_aruco.so
libopencv_calib3d.so
libopencv_ccalib.so
libopencv_core.so
libopencv_datasets.so
libopencv_dnn.so
libopencv_features2d.so
libopencv_flann.so
libopencv_imgproc.so
libopencv_xfeatures2d.so
libopencv_ximgproc.so
)

function isLibraryMissing {
  for LIBRARY in $OPENCV_LIBRARIES; do
    if [[ ! -e ~/$OPENCV_BASELINE/stage/lib/$LIBRARY ]]; then
      return 0
    fi
  done

  return 1
}

if isLibraryMissing; then
    mkdir -p "${HOME}/${OPENCV_BASELINE}"
    cd "${HOME}/${OPENCV_BASELINE}"
    git clone https://github.com/Itseez/opencv.git
    git clone https://github.com/opencv/opencv_contrib.git
    mkdir -p opencv/build
    cd opencv/build
    cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
          -DBUILD_opencv_legacy=OFF \
          -DCMAKE_INSTALL_PREFIX="${HOME}/${OPENCV_BASELINE}/stage" ..
    make -j4
    sudo make -j4 install
fi
