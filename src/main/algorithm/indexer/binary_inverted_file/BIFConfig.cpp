//
// Created by Przemek Piórkowski on 13.04.2016.
//

#include "BIFConfig.h"

namespace feitir {

    BIFParameters::BIFParameters(const DatabasePtr database, const int treshold) : database{database},
                                                                                   treshold{treshold} { }

    const DatabasePtr BIFParameters::getDatabase() const {
        return database;
    }

    const int BIFParameters::getTreshold() const {
        return treshold;
    }
}

