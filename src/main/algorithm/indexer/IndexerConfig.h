//
// Created by Przemek Piórkowski on 26.07.2016.
//

#ifndef FEITIR_INDEXERCONFIG_H
#define FEITIR_INDEXERCONFIG_H

#include <memory>

namespace feitir {
    class IndexerParameters {
    public:
        virtual ~IndexerParameters() = 0;
    };

    inline IndexerParameters::~IndexerParameters() { }

    using IndexerParametersPtr = std::shared_ptr<IndexerParameters>;

    class IndexerQuery {
    public:
        virtual ~IndexerQuery() = 0;
    };

    inline IndexerQuery::~IndexerQuery() { }

    using IndexerQueryPtr = std::shared_ptr<IndexerQuery>;

    class IndexerResult {
    public:
        virtual ~IndexerResult() = 0;
    };

    inline IndexerResult::~IndexerResult() { }

    using ResultCountT = u_int64_t;

    using IndexerResultPtr = std::shared_ptr<IndexerResult>;
}

#endif //FEITIR_INDEXERCONFIG_H
