//
// Created by Przemek Piórkowski on 07.03.2016.
//

#include "Database.h"

namespace feitir {

    Database::Database(const std::string &rootPath,
                               const std::vector<CategoryPtr> &&categories,
                               const std::vector<ImagePtr> &&images)
            : rootPath{rootPath}, categories{std::move(categories)}, images{std::move(images)} { }

    const std::string &Database::getRootPath() const {
        return rootPath;
    }

    const std::vector<CategoryPtr> &Database::getCategories() const {
        return categories;
    }

    const std::vector<ImagePtr> &Database::getImages() const {
        return images;
    }
}