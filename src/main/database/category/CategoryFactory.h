//
// Created by Przemek Piórkowski on 14.03.2016.
//

#ifndef FEITIR_CATEGORYFACTORY_H
#define FEITIR_CATEGORYFACTORY_H

#include <boost/filesystem.hpp>
#include "src/main/util/Util.h"
#include "src/main/database/image/ImageFactory.h"
#include "Category.h"

namespace feitir {

    class CategoryFactory {
    private:
        const Util util;
        const ImageFactory imageFactory;

    protected:
        const std::string categoryName(const std::string &rootPath, const std::string &categoryPath) const;

    public:
        CategoryFactory();
        const CategoryPtr createCategory(const std::string &root, const std::string &path) const;
        const CategoryPtr createCategory(const std::string &root, const std::string &path, bool findRecursive) const;
    };


}

#endif //FEITIR_CATEGORYFACTORY_H
