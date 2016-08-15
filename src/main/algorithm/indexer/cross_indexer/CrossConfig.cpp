//
// Created by Przemek Piórkowski on 07.07.2016.
//

#include "CrossConfig.h"

namespace feitir {

    CrossParameters::CrossParameters(const DatabasePtr &database, const VocabularyTypePtr vocabulary, const int N,
                                     const int binaryTreshold, const int R, const int codeWordSize)
            : database{database},
              vocabulary{vocabulary},
              N{N},
              R{R},
              codeWordSize{codeWordSize},
              binaryTreshold{binaryTreshold} { }

    const DatabasePtr &CrossParameters::getDatabase() const {
        return database;
    }

    int CrossParameters::getN() const {
        return N;
    }

    int CrossParameters::getR() const {
        return R;
    }

    VocabularyTypePtr CrossParameters::getVocabulary() const {
        return vocabulary;
    }

    int CrossParameters::getCodeWordSize() const {
        return codeWordSize;
    }

    CrossQuery::CrossQuery(const ImageBSIFTPtr &img) : img{img} { }

    const ImageBSIFTPtr CrossQuery::getImg() const {
        return img;
    }

    int CrossParameters::getBinaryTreshold() const {
        return binaryTreshold;
    }
}




