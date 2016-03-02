//
// Created by Przemek Piórkowski on 28.02.2016.
//

#ifndef FEITIR_IMAGEFACTORY_H
#define FEITIR_IMAGEFACTORY_H

#include <iostream>
#include <utility>
#include <memory>
#include <regex>
#include "Image.h"

namespace feitir {

    class ImageFactory {
    private:
        const std::regex fileNameRegex;

    protected:
        std::string extractFileName(const std::string& path) const;
        Extension extractFileExtension(const std::string& path) const;

    public:
        explicit ImageFactory();
        const std::shared_ptr<Image> createImage(const std::string &imgPath) const;

    };

}

#endif //FEITIR_IMAGEFACTORY_H
