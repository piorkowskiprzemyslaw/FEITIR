//
// Created by Przemek Piórkowski on 27.02.2016.
//

#include "Image.h"

namespace feitir {

    Image::Image(const std::string &name,
                 const std::string &fullPath,
                 const std::string &path,
                 const Extension extension,
                 const std::vector<cv::KeyPoint> && keyPoints,
                 const cv::Mat descriptors)
            : uuid{boost::uuids::random_generator()()}, fullPath{fullPath}, name{name}, path{path},
              keyPoints{std::move(keyPoints)}, extension{extension}, descriptors{descriptors} { }

    const std::vector<cv::KeyPoint> & Image::getKeyPoints() const {
        return keyPoints;
    }

    const std::string &Image::getFullPath() const {
        return fullPath;
    }

    const std::string &Image::getFileName() const {
        return name;
    }

    const Extension &Image::getExtension() const {
        return extension;
    }

    const cv::Mat &Image::getDescriptors() const {
        return descriptors;
    }

    const std::string &Image::getPath() const {
        return path;
    }
}
