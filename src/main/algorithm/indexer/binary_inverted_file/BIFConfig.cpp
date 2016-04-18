//
// Created by Przemek Piórkowski on 13.04.2016.
//

#include "BIFConfig.h"

namespace feitir {

    BIFParameters::BIFParameters(const DatabasePtr database,
                                 const std::size_t treshold) : database{database},
                                                               treshold{treshold} { }

    const DatabasePtr BIFParameters::getDatabase() const {
        return database;
    }

    const size_t BIFParameters::getTreshold() const {
        return treshold;
    }
}

