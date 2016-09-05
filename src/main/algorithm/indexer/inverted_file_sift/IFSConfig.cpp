//
// Created by Przemek Piórkowski on 05.09.2016.
//

#include "IFSConfig.h"

namespace feitir {

    IFSParameters::IFSParameters(const DatabasePtr database, const int threshold)
            : databaseWithOriginalValues{database}, threshold{threshold} {
        for (auto img : *databaseWithOriginalValues) {
            assert (img->getMatches().size() > 0);
            assert (img->getDescriptors().rows > 0);
        }
    }

    DatabasePtr IFSParameters::getDatabase() {
        return databaseWithOriginalValues;
    }

    const int IFSParameters::getThreshold() const {
        return threshold;
    }
}