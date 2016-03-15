//
// Created by Przemek Piórkowski on 14.03.2016.
//

#ifndef FEITIR_CATEGORYFACTORY_H
#define FEITIR_CATEGORYFACTORY_H

#include "Category.h"

namespace feitir {

    class CategoryFactory {
    private:

    protected:

    public:
        CategoryFactory();
        const CategoryPtr createCategory(const std::string &path) const;
        const CategoryPtr createCategory(const std::string &path, bool findRecursive) const;
    };


}

#endif //FEITIR_CATEGORYFACTORY_H
