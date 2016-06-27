//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_IFCONFIG_H
#define FEITIR_IFCONFIG_H

#include <iostream>
#include <vector>
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"
#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/database/Database.h"

namespace feitir {

    class IFParameters {
    public:

    private:
        DatabasePtr database;
        MatchingFunc matchingFunction;

    public:
        IFParameters(const DatabasePtr &database, const MatchingFunc &matchingFunction);
        const DatabasePtr & getDatabase() const;
        MatchingFunc getMatchingFunction() const;
    };

    class IFQuery {
    private:
        ImagePtr img;
    public:
        IFQuery(const ImagePtr &img);
        const ImagePtr getImg() const;
    };

    class IFResult {
    private:
        std::vector<std::pair<ImagePtr, float>> images;
    public:
        IFResult();
        void addResultEntry(std::pair<ImagePtr, float> element);
        const std::vector<std::pair<ImagePtr, float>> & getImages() const;
    };

    typedef std::pair<ImagePtr, float> IFResultEntry;

    typedef std::shared_ptr<IFResult> IFResultPtr;

    typedef std::shared_ptr<IFQuery> IFQueryPtr;

    typedef std::shared_ptr<IFParameters> IFParametersPtr;
}


#endif //FEITIR_IFCONFIG_H
