//
// Created by Przemek Piórkowski on 22.05.2016.
//

#ifndef FEITIR_DATABASEEXTRACTOR_H
#define FEITIR_DATABASEEXTRACTOR_H

#include "src/main/database/Database.h"

namespace feitir {
    class BSIFTDatabaseExtractor {
    public:
        virtual DatabasePtr extractDatabaseBSIFT(const DatabasePtr database) = 0;
    };

    using BSIFTDatabaseExtractorPtr = std::shared_ptr<BSIFTDatabaseExtractor>;
}


#endif //FEITIR_DATABASEEXTRACTOR_H
