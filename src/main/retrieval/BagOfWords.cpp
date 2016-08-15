//
// Created by Przemek Piórkowski on 19.03.2016.
//

#include <opencv/cv.hpp>
#include <src/main/benchmark/benchmark_description/BenchmarkScenario.h>
#include "BagOfWords.h"

namespace feitir {

    BagOfWords::BagOfWords(const RetrievalBenchmarkPtr benchmarkDescription,
                           const BSIFTExtractorPtr extractor,
                           const IndexerPtr indexer) : extractor{extractor},
                                                       indexer{indexer},
                                                       description{benchmarkDescription} {
        trainDatabase = databaseFactory.createDatabase(benchmarkDescription->getTestDatabasePath());
    }

    BOWResult BagOfWords::query(const ImagePtr img) {
        BOWResult result(0,0,0);

        auto idxResult = indexer->query(buildQuery(img, extractor, description->getIndexerMethod()->getMethodName()));

        return result;
    }
}