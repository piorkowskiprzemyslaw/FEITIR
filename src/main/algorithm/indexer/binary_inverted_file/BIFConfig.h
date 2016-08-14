//
// Created by Przemek Piórkowski on 13.04.2016.
//

#ifndef FEITIR_BIFCONFIG_H
#define FEITIR_BIFCONFIG_H

#include <memory>
#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/database/Database.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"

namespace feitir {

    class BIFParameters : public IndexerParameters {
    private:
        const DatabasePtr database;
        const int treshold;

    public:
        BIFParameters(const DatabasePtr database, const int treshold);
        const DatabasePtr getDatabase() const;
        const int getTreshold() const;
        virtual ~BIFParameters() = default;
    };

    class BIFQuery : public IndexerQuery {
    private:
        ImageBSIFTPtr img;
    public:
        BIFQuery(const ImagePtr img) {
            this->img = std::dynamic_pointer_cast<ImageBSIFT>(img);
            if (this->img == nullptr) {
                throw std::invalid_argument("img");
            }
        }

        BIFQuery(const ImageBSIFTPtr img) : img{img} { }

        const ImageBSIFTPtr getImg() const {
            return img;
        }

        virtual ~BIFQuery() = default;
    };

    using BIFResultEntry = std::pair<ImageBSIFTPtr, ResultCountT>;

    class BIFResult : public IndexerResult {
    private:
        std::vector<BIFResultEntry> resultList;
    public:
        BIFResult() { }

        void addResultEntry(BIFResultEntry entry) {
            resultList.push_back(std::move(entry));
        }

        const std::vector<BIFResultEntry>& getResultList() const {
            return resultList;
        }

        virtual ~BIFResult() = default;
    };

    using BIFResultPtr = std::shared_ptr<BIFResult>;

    using BIFQueryPtr = std::shared_ptr<BIFQuery>;

    using BIFParametersPtr = std::shared_ptr<BIFParameters>;
}


#endif //FEITIR_BIFCONFIG_H
