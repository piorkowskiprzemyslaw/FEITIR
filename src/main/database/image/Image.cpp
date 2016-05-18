//
// Created by Przemek Piórkowski on 27.02.2016.
//

#include "Image.h"

namespace feitir {

    Image::Image(const std::string &name, const std::string &fullPath,
                 const std::string &path, const Extension extension,
                 const cv::Mat descriptors) : uuid(boost::uuids::random_generator()()),
                                              fullPath{fullPath},
                                              name{name},
                                              path{path},
                                              extension{extension},
                                              descriptors{descriptors} { }

    Image::Image(const std::shared_ptr<Image> img) : uuid(img->getUuid()),
                                                     fullPath{img->getFullPath()},
                                                     name{img->getFileName()},
                                                     path{img->getPath()},
                                                     extension{img->getExtension()},
                                                     descriptors{img->getDescriptors()},
                                                     matches{img->getMatches()} { }

    Image::Image(const std::shared_ptr<Image> img,
                 std::vector<cv::DMatch> matches) : uuid(img->getUuid()),
                                                    name{img->getFileName()},
                                                    fullPath{img->getFullPath()},
                                                    path{img->getPath()},
                                                    extension{img->getExtension()},
                                                    matches{std::move(matches)} {
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

    const cv::Mat Image::getDescriptors() const {
        return descriptors;
    }

    const std::string &Image::getPath() const {
        return path;
    }

    const std::vector<cv::DMatch> &Image::getMatches() const {
        return matches;
    }

    Image::~Image() {

    }

    const boost::uuids::uuid &Image::getUuid() const {
        return uuid;
    }
}
