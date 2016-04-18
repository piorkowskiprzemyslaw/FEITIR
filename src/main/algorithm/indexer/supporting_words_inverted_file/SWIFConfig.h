//
// Created by Przemek Piórkowski on 15.04.2016.
//

#ifndef FEITIR_SWIFCONFIG_H
#define FEITIR_SWIFCONFIG_H

#include <iostream>
#include <memory>
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"
#include "src/main/database/Database.h"

namespace feitir {

    class SWIFParameters {
    private:
        std::size_t p;
        std::size_t distanceTreshold;
        std::size_t K;
        DatabasePtr transformedDb;
        VocabularyTypePtr vocabulary;

    public:
        SWIFParameters(size_t p, size_t distanceTreshold, size_t K, DatabasePtr transformedDb,
                               VocabularyTypePtr vocabulary);
        size_t getP() const;
        size_t getDistanceTreshold() const;
        const DatabasePtr getTransformedDb() const;
        const VocabularyTypePtr getVocabulary() const;
        size_t getK() const;
    };

    template <std::size_t N>
    class SWIFQuery {
    private:
        ImagePtr originalImage;
        ImageBSIFTPtr<N> transformedImage;
    public:
        SWIFQuery(const ImagePtr originalImage, const ImageBSIFTPtr<N> transformedImage)
                : originalImage{originalImage},
                  transformedImage{transformedImage} { }

        const ImageBSIFTPtr<N> getTransformedImage() const {
            return transformedImage;
        }

        const ImagePtr getOriginalImage() const {
            return originalImage;
        }
    };

    template <std::size_t N> using SWIFResultEntry = std::pair<ImageBSIFTPtr<N>, std::size_t>;

    template <std::size_t N>
    class SWIFResult {
    private:
        std::vector<SWIFResultEntry<N>> resultList;

    public:
        SWIFResult() { }

        void addResultEntry(SWIFResultEntry<N> resultEntry) {
            resultList.emplace_back(std::move(resultEntry));
        }

        const std::vector<SWIFResultEntry<N>> &getResultList() const {
            return resultList;
        }
    };

    using SWIFParametersPtr = std::shared_ptr<SWIFParameters>;

    template <std::size_t N> using SWIFQueryPtr = std::shared_ptr<SWIFQuery<N>>;

    template <std::size_t N> using SWIFResultPtr = std::shared_ptr<SWIFResult<N>>;
}


#endif //FEITIR_SWIFCONFIG_H
