//
// Created by Przemek Piórkowski on 07.03.2016.
//

#include "Category.h"

namespace feitir {

    Category::Category(const std::string &name, const std::string &path, std::vector<ImagePtr> images)
            : name{name}, path{path}, images{std::move(images)} { }

    const std::string &Category::getName() const {
        return name;
    }

    const std::string &Category::getPath() const {
        return path;
    }

    const std::vector<ImagePtr> &Category::getImages() const {
        return images;
    }
}
