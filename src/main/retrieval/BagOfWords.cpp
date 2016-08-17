//
// Created by Przemek Piórkowski on 19.03.2016.
//

#include <opencv/cv.hpp>
#include <src/main/benchmark/benchmark_description/BenchmarkScenario.h>
#include "BagOfWords.h"

namespace feitir {

    BagOfWords::BagOfWords(const RetrievalBenchmarkPtr benchmarkDescription) :  description{benchmarkDescription} {
        extractor = buildExtractor(benchmarkDescription->getBsiftAlgorithm());
        indexer = buildIndexer(benchmarkDescription->getIndexerMethod(), extractor);
        vocabularyTypePtr = buildVocabulary(description->getIndexerMethod()->getVocabularyType(),
                                            description->getIndexerMethod()->getVocabularyPath());
        trainDatabase = indexer->getIndexedDatabase();
    }

    BagOfWords::RankedList BagOfWords::query(const ImagePtr img) {
        auto indexerQuery = buildQuery(img, extractor, vocabularyTypePtr,
                                       description->getIndexerMethod()->getMethodName());
        auto indexerResult = indexer->query(indexerQuery);
        return generatePriorityQueue(indexerResult);
    }

    float BagOfWords::computeSimilarity(IndexerResultMap map) {
        // TODO
        return 0.0f;
    }

    BagOfWords::RankedList BagOfWords::generatePriorityQueue(const IndexerResultPtr indexerResult) {
        auto comparator = [](entry a, entry b) { return a.second > b.second; };
        RankedList result(comparator);

        for (const auto & resultEntry : indexerResult->getResultList()) {
            result.push({resultEntry.first, computeSimilarity(resultEntry.second)});
        }

        return result;
    }

    BOWStats BagOfWords::computeResult(const ImagePtr query, const CategoryPtr queryCategory,
                                       BagOfWords::RankedList &rankedList) {
        if (nullptr == query) {
            throw std::invalid_argument("query cannot be null");
        }

        if (nullptr == queryCategory) {
            throw std::invalid_argument("queryCategory cannot be null");
        }

        auto categoryTrainDb = trainDatabase->getCategoryByName(queryCategory->getName());

        /**
         * in case when in train database there is adequate category, or when the category
         * is empty (actually this wont be the case because CategoryFactory prevent creating empty categories)
         */
        if (categoryTrainDb == nullptr || categoryTrainDb->getImages().empty()) {
            return BOWStats(0,0,0);
        }

        int numberOfTopElements = description->getTopQueryResults();
        float relevantImagesInTrainDatabase = static_cast<float>(categoryTrainDb->getImages().size());
        float averagePrecision = 0;
        int relevantImages = 0;

        while (numberOfTopElements-- && !rankedList.empty()) {
            std::cout << "entry" << std::endl;
            auto entry = rankedList.top();
            rankedList.pop();
            auto entryCategory = trainDatabase->getImageCategory(entry.first);
            // to perform string comparison only one, save result.
            bool categoriesEqual = entryCategory->getName() == queryCategory->getName();
            relevantImages = categoriesEqual ? relevantImages + 1 : relevantImages;
            averagePrecision += categoriesEqual ?
                static_cast<float>(relevantImages) / static_cast<float>(description->getTopQueryResults() - numberOfTopElements) : 0;
        }

        return BOWStats(relevantImages / description->getTopQueryResults(),
                        relevantImages / relevantImagesInTrainDatabase,
                        averagePrecision / relevantImagesInTrainDatabase);
    }
}