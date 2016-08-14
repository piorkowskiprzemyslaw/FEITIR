//
// Created by Przemek Piórkowski on 03.04.2016.
//

#ifndef FEITIR_INDEXER_H
#define FEITIR_INDEXER_H

#include <functional>
#include <boost/uuid/uuid.hpp>
#include "IndexerConfig.h"

namespace feitir {

    class Indexer {
    public:
        explicit Indexer(const IndexerParametersPtr parameters) { };
        virtual IndexerResultPtr query(IndexerQueryPtr query) = 0;
        virtual ~Indexer() = default;
    };

    using IndexerPtr = std::shared_ptr<Indexer>;
}

#endif //FEITIR_INDEXER_H
