//
// Created by Przemek Piórkowski on 15.04.2016.
//

#ifndef FEITIR_SWIFCONFIG_H
#define FEITIR_SWIFCONFIG_H

#include <iostream>
#include <memory>
#include <src/main/algorithm/indexer/IndexerConfig.h>
#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"
#include "src/main/database/Database.h"

namespace feitir {

    class SWIFParameters : public IndexerParameters {
    private:
        std::size_t p;
        std::size_t distanceTreshold;
        std::size_t K;
        DatabasePtr transformedDb;
        VocabularyTypePtr vocabulary;
        MatchingFunc matchingFunc;

    public:
        SWIFParameters(size_t p, size_t distanceTreshold, size_t K, DatabasePtr transformedDb,
                       VocabularyTypePtr vocabulary, const MatchingFunc& matchingFunc);
        size_t getP() const;
        size_t getDistanceTreshold() const;
        const DatabasePtr getTransformedDb() const;
        const VocabularyTypePtr getVocabulary() const;
        size_t getK() const;
        const MatchingFunc & getMatchingFunc() const;
    };

    class SWIFQuery : public IndexerQuery {
    private:
        ImagePtr originalImage;
        ImageBSIFTPtr transformedImage;
    public:
        SWIFQuery(const ImagePtr originalImage, const ImageBSIFTPtr transformedImage)
                : originalImage{originalImage},
                  transformedImage{transformedImage} { }

        const ImageBSIFTPtr getTransformedImage() const {
            return transformedImage;
        }

        const ImagePtr getOriginalImage() const {
            return originalImage;
        }
    };

    using SWIFResultEntry = std::pair<ImageBSIFTPtr, std::size_t>;

    class SWIFResult : public IndexerResult {
    private:
        std::vector<SWIFResultEntry> resultList;

    public:
        SWIFResult() { }

        void addResultEntry(SWIFResultEntry resultEntry) {
            resultList.emplace_back(std::move(resultEntry));
        }

        const std::vector<SWIFResultEntry> &getResultList() const {
            return resultList;
        }
    };

    using SWIFParametersPtr = std::shared_ptr<SWIFParameters>;

    using SWIFQueryPtr = std::shared_ptr<SWIFQuery>;

    using SWIFResultPtr = std::shared_ptr<SWIFResult>;
}


#endif //FEITIR_SWIFCONFIG_H
