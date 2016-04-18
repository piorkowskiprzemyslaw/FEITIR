//
// Created by Przemek Piórkowski on 07.03.2016.
//

#include "Database.h"

namespace feitir {

    Database::Database(const std::string &rootPath,
                       std::vector<CategoryPtr> categories,
                       std::vector<ImagePtr> images)
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

    Database::const_iterator Database::begin() const {
        return Database::const_iterator(this);
    }

    Database::const_iterator Database::end() const {
        const std::vector<ImagePtr> *currentVector = nullptr;
        if (this->categories.empty()) {
            currentVector = &(this->images);
        } else {
            currentVector = &(this->categories[this->categories.size() - 1]->getImages());
        }

        const std::vector<CategoryPtr> *categories = &(this->categories);
        std::vector<ImagePtr>::const_iterator currentIterator = currentVector->end();
        std::vector<CategoryPtr>::const_iterator nextCategory = this->categories.end();

        return Database::const_iterator(currentVector, categories, currentIterator, nextCategory);
    }

}