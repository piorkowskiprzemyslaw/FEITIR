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
        int p;
        int distanceTreshold;
        int K;
        DatabasePtr transformedDb;
        VocabularyTypePtr vocabulary;

    public:
        SWIFParameters(DatabasePtr transformedDb, VocabularyTypePtr vocabulary, int p, int K, int distanceTreshold);
        int getP() const;
        int getDistanceTreshold() const;
        const DatabasePtr getTransformedDb() const;
        const VocabularyTypePtr getVocabulary() const;
        int getK() const;
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

    using SWIFResultEntry = std::pair<ImageBSIFTPtr, ResultCountT>;

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
