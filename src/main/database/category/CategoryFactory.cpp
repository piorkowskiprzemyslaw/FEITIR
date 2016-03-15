//
// Created by Przemek Piórkowski on 14.03.2016.
//

#include "CategoryFactory.h"

namespace feitir {

    CategoryFactory::CategoryFactory() { }


    const CategoryPtr CategoryFactory::createCategory(const std::string &path) const {
        return createCategory(path, true);
    }

    const CategoryPtr CategoryFactory::createCategory(const std::string &path, bool findRecursive) const {
        return nullptr;
    }
}