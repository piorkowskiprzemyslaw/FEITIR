//
// Created by Przemek Piórkowski on 25.03.2016.
//

#ifndef FEITIR_BSIFTEXTRACTOR_H
#define FEITIR_BSIFTEXTRACTOR_H

#include <iostream>
#include <vector>
#include "src/main/database/Database.h"
#include "src/main/database/image/Image.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/database/category/Category.h"

namespace feitir {

    class BSIFTExtractor {
    public:
        virtual ~BSIFTExtractor();
        virtual ImageBSIFTPtr extractImageBSIFT(const ImagePtr image) = 0;
        virtual CategoryPtr extractCategoryBSIFT(const CategoryPtr category);
        virtual DatabasePtr extractDatabaseBSIFT(const DatabasePtr database);
    };

}


#endif //FEITIR_BSIFTEXTRACTOR_H
