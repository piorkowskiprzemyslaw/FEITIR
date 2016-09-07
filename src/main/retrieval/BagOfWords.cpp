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
        return generatePriorityQueue(indexerResult, indexerQuery->getImg());
    }

    float BagOfWords::computeSimilarity(ImagePtr img, IndexerResultMap map, ImagePtr query) {
        if (!description->getMatchingMethod().compare("tfidf")) {
            return tfidfSimilarity(img, map, query);
        } else if (!description->getMatchingMethod().compare("voting")) {
            return votingSimilarity(img, map);
        } else if (!description->getMatchingMethod().compare("dot_product")) {
            return dotProductSimilarity(img, map, query);
        } else if (!description->getMatchingMethod().compare("histogram_intersection")) {
            return histogramIntersectionSimilarity(img, map, query);
        }
        throw std::invalid_argument(description->getMatchingMethod()
                                    + " cannot be recognized as matching method type");
    }

    BagOfWords::RankedList
    BagOfWords::generatePriorityQueue(const IndexerResultPtr indexerResult, const ImagePtr query) {
        RankedList result([](entry a, entry b) { return a.second < b.second; });

        for (const auto & resultEntry : indexerResult->getResultList()) {
            result.push({resultEntry.first, computeSimilarity(resultEntry.first, resultEntry.second, query)});
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
         * in case when train database doesn't include adequate category, or when the category
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
            auto entry = rankedList.top();
            rankedList.pop();
            auto entryCategory = trainDatabase->getImageCategory(entry.first);
            // save result, to perform string comparison once
            bool categoriesEqual = entryCategory->getName().compare(queryCategory->getName()) == 0;
            relevantImages = categoriesEqual ? relevantImages + 1 : relevantImages;
            averagePrecision += categoriesEqual ?
                static_cast<float>(relevantImages) / static_cast<float>(description->getTopQueryResults() - numberOfTopElements) : 0;
        }

        return BOWStats(relevantImages / static_cast<float>(description->getTopQueryResults()),
                        relevantImages / relevantImagesInTrainDatabase,
                        averagePrecision / relevantImagesInTrainDatabase);
    }

    float BagOfWords::tfidfSimilarity(ImagePtr, IndexerResultMap, ImagePtr) {
        throw std::runtime_error("tfidfSimilarity is not implemented");
    }

    float BagOfWords::votingSimilarity(ImagePtr img, IndexerResultMap map) {
        float result = 0;
        for (const auto& e : map) {
            result += static_cast<float>(e.second);
        }
        return result / static_cast<float>(img->getMatches().size());
    }

    float BagOfWords::dotProductSimilarity(ImagePtr, IndexerResultMap , ImagePtr) {
        throw std::runtime_error("dotProductSimilarity is not implemented");
    }

    float BagOfWords::histogramIntersectionSimilarity(ImagePtr img, IndexerResultMap, ImagePtr query) {
        auto imgHistogram = prepareHistogram(img);
        auto queryHistogram = prepareHistogram(query);
        assert (imgHistogram.size() == queryHistogram.size());
        float result = 0;

        for (int i = 0; i < imgHistogram.size(); ++i) {
            result += std::min(imgHistogram[i], queryHistogram[i]);
        }

        assert (result <= 1);

        return result;
    }

    std::vector<float> BagOfWords::prepareHistogram(ImagePtr img) {
        std::vector<float> histogram(vocabularyTypePtr->getVocabularyMatrix().rows, 0.0f);
        auto numberOfDescriptors = img->getMatches().size();

        for (const auto& match : img->getMatches()) {
            histogram[match.trainIdx]++;
        }

        for (int i = 0; i < histogram.size(); ++i) {
            histogram[i] /= static_cast<float>(numberOfDescriptors);
        }

        return histogram;
    }
}