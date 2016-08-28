//
// Created by Przemek Piórkowski on 19.05.2016.
//

#include <src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h>
#include <src/main/algorithm/vocabulary/hierarchical_kmeans/HKMeansVocabularyBuilder.h>
#include <src/main/algorithm/BSIFT/comparison_array/ComparisonArrayBSIFTExtractor.h>
#include <src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h>
#include <src/main/algorithm/BSIFT/locality_sensitive_hashing/LocalitySensitiveHashingBSIFTExtractor.h>
#include <src/main/algorithm/BSIFT/descriptor_position_median/DescriptorPositionMedianBSIFTExtractor.h>
#include <src/main/algorithm/BSIFT/descriptor_voronoi_position/DescriptorVoronoiPositionBSIFTExtractor.h>
#include <src/main/algorithm/BSIFT/vectors_compare/VectorsCompareBSIFTExtractor.h>
#include <src/main/algorithm/indexer/inverted_file/InvertedFileIndexer.h>
#include <src/main/algorithm/indexer/cross_indexer/CrossIndexer.h>
#include <src/main/algorithm/indexer/binary_inverted_file/BinaryInvertedFileIndexer.h>
#include <src/main/algorithm/indexer/supporting_words_inverted_file/SupportingWordsInvertedFileIndexer.h>
#include "BenchmarkScenario.h"

namespace feitir {

    const std::string BenchmarkScenario::BSIFT_BENCHMARKS = "bsift_benchmarks";
    const std::string BenchmarkScenario::INDEXER_BENCHMARKS = "indexer_benchmarks";
    const std::string BenchmarkScenario::RETRIEVAL_BENCHMARKS = "retrieval_benchmarks";

    const std::vector<BSIFTBenchmarkPtr> &BenchmarkScenario::getBsiftBenchmarkDescriptions() const {
        return bsiftBenchmarkDescriptions;
    }

    const std::vector<IndexerBenchmarkPtr> &BenchmarkScenario::getIndexerBenchmarkDescriptions() const {
        return indexerBenchmarkDescriptions;
    }

    const std::vector<RetrievalBenchmarkPtr> &BenchmarkScenario::getRetrievalBenchmarkDescriptions() const {
        return retrievalBenchmarkDescriptions;
    }

    JSONObject::JSONObjectPtr BenchmarkScenario::constructNewObject() const {
        return std::make_shared<BenchmarkScenario>();
    }

    JSONObject::FieldNames BenchmarkScenario::arrayOfObjectsFieldNames() const {
        return {BSIFT_BENCHMARKS, INDEXER_BENCHMARKS, RETRIEVAL_BENCHMARKS};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> BenchmarkScenario::arrayOfObjectTypes() const {
        return {
                {BSIFT_BENCHMARKS, std::make_shared<BSIFTBenchmark>()},
                {INDEXER_BENCHMARKS, std::make_shared<IndexerBenchmark>()},
                {RETRIEVAL_BENCHMARKS, std::make_shared<RetrievalBenchmark>()}};
    }

    void BenchmarkScenario::setArrayOfObjectsField(const JSONObject::ArrayObjectsValuesMap &arrayObjectsValuesMap) {
        if (arrayObjectsValuesMap.count(BSIFT_BENCHMARKS)) {
            bsiftBenchmarkDescriptions.clear();
            auto bsiftVector = arrayObjectsValuesMap.at(BSIFT_BENCHMARKS);
            std::transform(bsiftVector.begin(), bsiftVector.end(), back_inserter(bsiftBenchmarkDescriptions),
                           [] (const JSONObjectPtr &objectPtr) {
                               return std::dynamic_pointer_cast<BSIFTBenchmark>(objectPtr);
                           });
        }

        if (arrayObjectsValuesMap.count(INDEXER_BENCHMARKS)) {
            indexerBenchmarkDescriptions.clear();
            auto indexerVector = arrayObjectsValuesMap.at(INDEXER_BENCHMARKS);
            std::transform(indexerVector.begin(), indexerVector.end(), back_inserter(indexerBenchmarkDescriptions),
                           [] (const JSONObjectPtr &objectPtr) {
                               return std::dynamic_pointer_cast<IndexerBenchmark>(objectPtr);
                           });
        }

        if (arrayObjectsValuesMap.count(RETRIEVAL_BENCHMARKS)) {
            retrievalBenchmarkDescriptions.clear();
            auto retrievalVector = arrayObjectsValuesMap.at(RETRIEVAL_BENCHMARKS);
            std::transform(retrievalVector.begin(), retrievalVector.end(),
                           back_inserter(retrievalBenchmarkDescriptions),
                           [] (const JSONObjectPtr & objectPtr) {
                               return std::dynamic_pointer_cast<RetrievalBenchmark>(objectPtr);
                           });
        }
    }

    VocabularyTypePtr buildVocabulary(const std::string &type, const std::string &path) {
        if (!type.compare("kmeans")) {
            KMeansVocabularyBuilder kMeansVocabularyBuilder;
            return kMeansVocabularyBuilder.readFromFile(path);
        } else if (!type.compare("hkmeans")) {
            HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
            return hkMeansVocabularyBuilder.readFromFile(path);
        }
        throw std::invalid_argument(type + " has no meaning as vocabulary type");
    }

    BSIFTExtractorPtr buildExtractor(const BSIFTAlgorithmPtr description) {
        DatabaseFactory databaseFactory;

        std::string methodName = description->getBsiftMethod()->getMethod();
        if (!methodName.compare("comparison_array")) {
            return std::make_shared<ComparisonArrayBSIFTExtractor<>>(description->getBsiftMethod()->getN(),
                                                                     description->getBsiftMethod()->getL(),
                                                                     description->getBsiftMethod()->getT());
        } else if (!methodName.compare("descriptor_median")) {
            return std::make_shared<DescriptorMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_position_median")) {
            auto trainDatabase = databaseFactory.createDatabase(description->getDatabasePath());
            return std::make_shared<DescriptorPositionMedianBSIFTExtractor>(trainDatabase);
        } else if (!methodName.compare("descriptor_voronoi_position")) {
            auto trainDatabase = databaseFactory.createDatabase(description->getDatabasePath());
            auto vocabulary = buildVocabulary(description->getVocabularyType(), description->getVocabularyPath());
            return std::make_shared<DescriptorVoronoiPositionBSIFTExtractor>(
                    description->getBsiftMethod()->getN(), vocabulary, trainDatabase);
        } else if (!methodName.compare("locality_sensitive_hashing")) {
            auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor::generateRandomHashFunctions(
                    description->getBsiftMethod()->getN());
            return std::make_shared<LocalitySensitiveHashingBSIFTExtractor>(description->getBsiftMethod()->getN(),
                                                                            hashFunctions);
        } else if (!methodName.compare("vectors_compare")) {
            return std::make_shared<VectorsCompareBSIFTExtractor>();
        } else if (!methodName.compare("no_extractor")) {
            return nullptr;
        }

        throw std::invalid_argument(methodName + " has no meaning as bsift extractor method");
    }

    IndexerPtr buildIndexer(const IndexerMethodPtr description, const BSIFTExtractorPtr extractor) {
        DatabaseFactory databaseFactory;
        auto vocabulary = buildVocabulary(description->getVocabularyType(), description->getVocabularyPath());
        auto database = databaseFactory.createDatabase(description->getDatabasePath());
        auto translatedDatabase = extractor->getDatabaseTranslatorPtr()
                ->transformDatabase(vocabulary, extractor->extractDatabaseBSIFT(database));
        const auto & methodName = description->getMethodName();

        if (!methodName.compare("inverted_file")) {
            return std::make_shared<InvertedFileIndexer>(std::make_shared<IFParameters>(database));
        } else if (!methodName.compare("cross_indexer")) {
            return std::make_shared<CrossIndexer>(translatedDatabase, vocabulary, description->getN(),
                                                  description->getThreshold(), description->getR(),
                                                  description->getCodeWordSize());
        } else if (!methodName.compare("binary_inverted_file")) {
            return std::make_shared<BinaryInvertedFileIndexer>(
                    std::make_shared<BIFParameters>(translatedDatabase, description->getThreshold()));
        } else if (!methodName.compare("supporting_words_inverted_file")) {
            return std::make_shared<SupportingWordsInvertedFileIndexer>(
                    std::make_shared<SWIFParameters>(translatedDatabase, vocabulary, description->getP(),
                                                     description->getK(), description->getThreshold()));
        }

        throw std::invalid_argument(methodName + " does not cast to any available indexer type");
    }

    IndexerQueryPtr buildQuery(const ImagePtr img, const BSIFTExtractorPtr extractor,
                               const VocabularyTypePtr vocabulary, const std::string &method) {
        if (!method.compare("inverted_file")) {
            return std::make_shared<IFQuery>(img);
        } else if (!method.compare("cross_indexer")) {
            return std::make_shared<CrossQuery>(extractor->getDatabaseTranslatorPtr()->transformImage(
                    vocabulary, extractor->extractImageBSIFT(img)));
        } else if (!method.compare("binary_inverted_file")) {
            return std::make_shared<BIFQuery>(extractor->getDatabaseTranslatorPtr()->transformImage(
                    vocabulary, extractor->extractImageBSIFT(img)));
        } else if (!method.compare("supporting_words_inverted_file")) {
            return std::make_shared<SWIFQuery>(img, extractor->getDatabaseTranslatorPtr()->transformImage(
                    vocabulary, extractor->extractImageBSIFT(img)));
        }

        throw std::invalid_argument(method + " does not cast to any available indexer type");
    }
}