//
// Created by Przemek Piórkowski on 11.03.2016.
//

#ifndef FEITIR_DATABASEFACTORY_H
#define FEITIR_DATABASEFACTORY_H

#include <iostream>
#include <list>
#include <tuple>
#include <functional>
#include <boost/filesystem.hpp>
#include <src/main/database/image/ImageFactory.h>
#include "src/main/database/Database.h"
#include "src/main/database/category/CategoryFactory.h"

namespace feitir {

    class DatabaseFactory {
    private:
        const CategoryFactory categoryFactory;
        const ImageFactory imageFactory;

    protected:
        template <class Predicate>
        std::list<std::string> findInDirectory(const std::string &root, bool findRecursive, Predicate pred) const;
        std::list<std::string> findCategoriesRoots(const std::string &root, bool nestedCategories) const;
        std::list<std::string> findRootImages(const std::string &root) const;

    public:
        explicit DatabaseFactory();
        const DatabasePtr createDatabase(const std::string& rootDir, bool nestedCategories) const;
        const DatabasePtr createDatabase(const std::string& rootDir) const;

    };
}


#endif //FEITIR_DATABASEFACTORY_H
