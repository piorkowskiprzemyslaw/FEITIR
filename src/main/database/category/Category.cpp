//
// Created by Przemek Piórkowski on 07.03.2016.
//

#include "Category.h"

namespace feitir {

    Category::Category(const std::string &name, const std::vector<ImagePtr>&& images) : name{name}, images{images} {

    }

}
