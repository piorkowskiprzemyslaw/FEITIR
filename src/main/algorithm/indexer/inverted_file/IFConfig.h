//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_IFCONFIG_H
#define FEITIR_IFCONFIG_H

#include <iostream>
#include <vector>
#include "src/main/algorithm/indexer/IndexerConfig.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"
#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/database/Database.h"

namespace feitir {

    class IFParameters : public IndexerParameters {
    public:

    private:
        DatabasePtr database;

    public:
        IFParameters(const DatabasePtr &database);
        const DatabasePtr & getDatabase() const;
        virtual ~IFParameters() = default;
    };

    class IFQuery : public IndexerQuery {
    private:
        ImagePtr img;
    public:
        IFQuery(const ImagePtr &img);
        const ImagePtr getImg() const;
        virtual ~IFQuery() = default;
    };

    typedef std::shared_ptr<IFQuery> IFQueryPtr;

    using IFParametersPtr = std::shared_ptr<IFParameters>;
}


#endif //FEITIR_IFCONFIG_H
