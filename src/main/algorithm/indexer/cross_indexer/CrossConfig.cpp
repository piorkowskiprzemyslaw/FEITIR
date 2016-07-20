//
// Created by Przemek Piórkowski on 07.07.2016.
//

#include "CrossConfig.h"

namespace feitir {

    CrossParameters::CrossParameters(const DatabasePtr &database, const VocabularyTypePtr vocabulary, const MatchingFunc &matchingFunc,
                                         const int N, const size_t binaryTreshold, const size_t R, const size_t codeWordSize)
            : database{database},
              vocabulary{vocabulary},
              N{N},
              R{R},
              codeWordSize{codeWordSize},
              matchingFunc{matchingFunc},
              binaryTreshold{binaryTreshold} { }

    const DatabasePtr &CrossParameters::getDatabase() const {
        return database;
    }

    int CrossParameters::getN() const {
        return N;
    }

    size_t CrossParameters::getR() const {
        return R;
    }

    VocabularyTypePtr CrossParameters::getVocabulary() const {
        return vocabulary;
    }

    size_t CrossParameters::getCodeWordSize() const {
        return codeWordSize;
    }

    const MatchingFunc &CrossParameters::getMatchingFunc() const {
        return matchingFunc;
    }

    CrossQuery::CrossQuery(const ImageBSIFTPtr &img) : img{img} { }

    const ImageBSIFTPtr CrossQuery::getImg() const {
        return img;
    }

    void CrossResult::addResultEntry(CrossResultEntry element) {
        images.push_back(element);
    }

    const std::vector<std::pair<ImagePtr, float>> & CrossResult::getImages() const {
        return images;
    }

    size_t CrossParameters::getBinaryTreshold() const {
        return binaryTreshold;
    }
}




