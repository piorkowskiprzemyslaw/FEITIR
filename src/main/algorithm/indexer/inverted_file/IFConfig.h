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
        MatchingFunc matchingFunction;

    public:
        IFParameters(const DatabasePtr &database, const MatchingFunc &matchingFunction);
        const DatabasePtr & getDatabase() const;
        MatchingFunc getMatchingFunction() const;
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

    class IFResult : public IndexerResult {
    private:
        std::vector<std::pair<ImagePtr, float>> images;
    public:
        IFResult();
        void addResultEntry(std::pair<ImagePtr, float> element);
        const std::vector<std::pair<ImagePtr, float>> & getImages() const;
        virtual ~IFResult() = default;
    };

    typedef std::pair<ImagePtr, float> IFResultEntry;

    typedef std::shared_ptr<IFResult> IFResultPtr;

    typedef std::shared_ptr<IFQuery> IFQueryPtr;

    using IFParametersPtr = std::shared_ptr<IFParameters>;
}


#endif //FEITIR_IFCONFIG_H
