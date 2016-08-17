//
// Created by Przemek Piórkowski on 26.07.2016.
//

#ifndef FEITIR_INDEXERCONFIG_H
#define FEITIR_INDEXERCONFIG_H

#include <memory>
#include <src/main/database/Database.h>
#include <src/main/database/image/Image.h>
#include <unordered_map>

namespace feitir {
    class IndexerParameters {
    public:
        virtual DatabasePtr getDatabase() = 0;
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

    using ResultCountT = u_int64_t;
    using IndexerResultMap = std::unordered_map<int, ResultCountT>;
    using IndexerResultEntry = std::pair<ImagePtr, IndexerResultMap>;

    class IndexerResult final {
    private:
        std::vector<IndexerResultEntry> result;
    public:
        void addResultEntry(IndexerResultEntry entry) {
            result.push_back(std::move(entry));
        }

        const std::vector<IndexerResultEntry>& getResultList() const {
            return result;
        }
    };

    using IndexerResultPtr = std::shared_ptr<IndexerResult>;
}

#endif //FEITIR_INDEXERCONFIG_H
