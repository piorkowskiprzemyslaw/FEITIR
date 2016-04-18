//
// Created by Przemek Piórkowski on 13.04.2016.
//

#ifndef FEITIR_BIFCONFIG_H
#define FEITIR_BIFCONFIG_H

#include <memory>
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/database/Database.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"

namespace feitir {

    class BIFParameters {
    private:
        const DatabasePtr database;
        const std::size_t treshold;

    public:
        BIFParameters(const DatabasePtr database, const std::size_t treshold);
        const DatabasePtr getDatabase() const;
        const size_t getTreshold() const;
    };

    template <std::size_t N>
    class BIFQuery {
    private:
        ImageBSIFTPtr<N> img;
    public:
        BIFQuery(const ImagePtr img) {
            this->img = std::dynamic_pointer_cast<ImageBSIFT<N>>(img);
            if (this->img == nullptr) {
                throw std::invalid_argument("img");
            }
        }

        BIFQuery(const ImageBSIFTPtr<N> img) : img{img} { }

        const ImageBSIFTPtr<N> getImg() const {
            return img;
        }
    };

    template <std::size_t N> using BIFResultEntry = std::pair<ImageBSIFTPtr<N>, std::size_t>;

    template <std::size_t N>
    class BIFResult {
    private:
        std::vector<BIFResultEntry<N> > resultList;
    public:
        BIFResult() { }

        void addResultEntry(BIFResultEntry<N> entry) {
            resultList.push_back(std::move(entry));
        }

        const std::vector<BIFResultEntry<N>>& getResultList() const {
            return resultList;
        }
    };

    template <std::size_t N> using BIFResultPtr = std::shared_ptr<BIFResult<N>>;

    template <std::size_t N> using BIFQueryPtr = std::shared_ptr<BIFQuery<N>>;

    using BIFParametersPtr = std::shared_ptr<BIFParameters>;
}


#endif //FEITIR_BIFCONFIG_H
