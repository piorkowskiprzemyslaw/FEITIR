//
// Created by Przemek Piórkowski on 07.03.2016.
//

#include "Category.h"

namespace feitir {

    Category::Category(const std::string &name, const std::string &path, std::vector<ImagePtr> images)
            : uuid{boost::uuids::random_generator()()}, name{name}, path{path}, images{std::move(images)} { }

    const std::string &Category::getName() const {
        return name;
    }

    const std::string &Category::getPath() const {
        return path;
    }

    const std::vector<ImagePtr> &Category::getImages() const {
        return images;
    }

    Category::const_iterator Category::begin() const {
        return Category::const_iterator(images.begin());
    }

    Category::const_iterator Category::end() const {
        return Category::const_iterator(images.end());
    }

    const boost::uuids::uuid &Category::getUuid() const {
        return uuid;
    }

}
