//
// Created by Przemek Piórkowski on 27.02.2016.
//

#include "Image.h"

namespace feitir {

    Image::Image(const std::string &path,
                 const std::string &name,
                 const std::vector<cv::KeyPoint> && keyPoints,
                 const Extension extension)
            : path{path}, name{name}, keyPoints{keyPoints}, extension{extension} { }

    const std::vector<cv::KeyPoint> & Image::getKeyPoints() const {
        return keyPoints;
    }

    const std::string &Image::getPath() const {
        return path;
    }

    const std::string &Image::getName() const {
        return name;
    }

    const Extension &Image::getExtension() const {
        return extension;
    }
}
