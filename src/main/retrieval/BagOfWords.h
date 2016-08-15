//
// Created by Przemek Piórkowski on 19.03.2016.
//

#ifndef FEITIR_BAGOFWORDS_H
#define FEITIR_BAGOFWORDS_H

#include <src/main/benchmark/benchmark_description/retrieval/RetrievalBenchmark.h>
#include <src/main/algorithm/indexer/Indexer.h>
#include <src/main/algorithm/BSIFT/BSIFTExtractor.h>

namespace feitir {

    /**
     * Class which serves as BOW query result
     */
    struct BOWResult {
        const float precision;
        const float recall;
        const float avgPrecision;

        BOWResult(float precision, float recall, float avgPrecision) : precision{precision},
                                                                       recall{recall},
                                                                       avgPrecision{avgPrecision} {}
    };

    /**
     * Class which represents Bag of Words retrieval method.
     */
    class BagOfWords {
    public:
        explicit BagOfWords(const RetrievalBenchmarkPtr benchmarkDescription,
                            const BSIFTExtractorPtr extractor, const IndexerPtr indexer);
        BOWResult query(const ImagePtr img);

    private:
        RetrievalBenchmarkPtr description;
        DatabaseFactory databaseFactory;
        BSIFTExtractorPtr extractor;
        IndexerPtr indexer;
        DatabasePtr trainDatabase;
    };

}

#endif //FEITIR_BAGOFWORDS_H
