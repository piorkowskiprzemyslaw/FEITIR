//
// Created by Przemek Piórkowski on 11.03.2016.
//

#ifndef FEITIR_DATABASEFACTORY_H
#define FEITIR_DATABASEFACTORY_H

#include <iostream>
#include <list>
#include <tuple>
#include <functional>
#include "src/main/util/Util.h"
#include "src/main/database/image/ImageFactory.h"
#include "src/main/database/Database.h"
#include "src/main/database/category/CategoryFactory.h"

namespace feitir {

    class DatabaseFactory {
    private:
        const CategoryFactory categoryFactory;
        const ImageFactory imageFactory;
        const Util util;

    protected:
        std::list<std::string> findCategoriesRoots(const std::string &root, bool nestedCategories) const;
        std::list<std::string> findRootImages(const std::string &root) const;

    public:
        explicit DatabaseFactory();
        const DatabasePtr createDatabase(const std::string& rootDir, bool nestedCategories) const;
        const DatabasePtr createDatabase(const std::string& rootDir) const;
        const DatabasePtr createDatabase(const DatabasePtr database,
                                         std::vector<CategoryPtr> categories,
                                         std::vector<ImagePtr> images) const;
    };
}


#endif //FEITIR_DATABASEFACTORY_H
