//
// Created by Przemek Piórkowski on 28.02.2016.
//

#include "ImageFactory.h"

namespace feitir {

    ImageFactory::ImageFactory() : fileNameRegex{"(([^\/\.]+).([^\/\.]+))$"} {

    }

    const std::shared_ptr<Image> ImageFactory::createImage(const std::string &imgPath) const {
        std::string fileName = extractFileName(imgPath);
        Extension extension = extractFileExtension(imgPath);

        return std::make_shared<Image>(imgPath, fileName, std::vector<cv::KeyPoint>(), extension);
    }

    std::string ImageFactory::extractFileName(const std::string &path) const {
        std::smatch smatch;
        std::regex_search(path, smatch, fileNameRegex);
        if (smatch.empty()) {
            return "";
        } else {
            return smatch[1].str().c_str();
        }
    }

    Extension ImageFactory::extractFileExtension(const std::string &path) const {
        std::smatch smatch;
        std::regex_search(path, smatch, fileNameRegex);
        if (smatch.empty()) {
            return Extension::UNKNOWN;
        } else {
            if (smatch[3].compare("png") || smatch[3].compare("PNG")) {
                return Extension::PNG;
            } else if (smatch[3].compare("tiff") || smatch[3].compare("TIFF")) {
                return Extension::TIFF;
            } else if (smatch[3].compare("jpeg") || smatch[3].compare("JPEG")) {
                return Extension::JPEG;
            } else {
                return Extension::UNKNOWN;
            }
        }
    }
}


