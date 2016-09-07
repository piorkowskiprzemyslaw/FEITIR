//
// Created by Przemek Piórkowski on 19.03.2016.
//

#ifndef FEITIR_BAGOFWORDS_H
#define FEITIR_BAGOFWORDS_H

#include <src/main/benchmark/benchmark_description/retrieval/RetrievalBenchmark.h>
#include <src/main/algorithm/indexer/Indexer.h>
#include <src/main/algorithm/BSIFT/BSIFTExtractor.h>
#include <queue>

namespace feitir {

    /**
     * Class which serves as BOW query result statistics
     */
    struct BOWStats {
        const float precision;
        const float recall;
        const float avgPrecision;

        BOWStats(float precision, float recall, float avgPrecision) : precision{precision},
                                                                      recall{recall},
                                                                      avgPrecision{avgPrecision} {}
    };

    /**
     * Class which represents Bag of Words retrieval method.
     */
    class BagOfWords {
    public:
        using entry = std::pair<ImagePtr, float>;
        using cmp = std::function<bool(entry, entry)>;
        using RankedList = std::priority_queue<entry, std::vector<entry>, cmp>;

        explicit BagOfWords(const RetrievalBenchmarkPtr benchmarkDescription);
        RankedList query(const ImagePtr img);
        BOWStats computeResult(const ImagePtr query, const CategoryPtr queryCategory, RankedList &rankedList);

    private:
        float computeSimilarity(ImagePtr img, IndexerResultMap map, ImagePtr query);
        float tfidfSimilarity(ImagePtr img, IndexerResultMap map, ImagePtr query);
        float votingSimilarity(ImagePtr img, IndexerResultMap map);
        float dotProductSimilarity(ImagePtr img, IndexerResultMap map, ImagePtr query);
        float histogramIntersectionSimilarity(ImagePtr img, IndexerResultMap map, ImagePtr query);
        std::vector<float> prepareHistogram(ImagePtr img);
        BagOfWords::RankedList generatePriorityQueue(const IndexerResultPtr indexerResult, const ImagePtr query);

        RetrievalBenchmarkPtr description;
        DatabaseFactory databaseFactory;
        BSIFTExtractorPtr extractor;
        IndexerPtr indexer;
        VocabularyTypePtr vocabularyTypePtr;
        DatabasePtr trainDatabase;
    };

}

#endif //FEITIR_BAGOFWORDS_H
