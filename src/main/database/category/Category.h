//
// Created by Przemek Piórkowski on 07.03.2016.
//

#ifndef FEITIR_CATEGORY_H
#define FEITIR_CATEGORY_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <src/main/database/image/Image.h>

namespace feitir {

    class Category {
    private:
        const std::string name;
        const std::vector<ImagePtr> images;

    protected:

    public:
        Category(const std::string &name, const std::vector<ImagePtr>&& images);
    };

    typedef std::shared_ptr<Category> CategoryPtr;

}


#endif //FEITIR_CATEGORY_H
