//
// Created by Przemek Piórkowski on 15.08.2016.
//

#ifndef FEITIR_RETRIEVALBENCHMARK_H
#define FEITIR_RETRIEVALBENCHMARK_H

#include <src/main/util/JSON/JSONObject.h>
#include <src/main/benchmark/benchmark_description/indexer/IndexerMethod.h>
#include <src/main/benchmark/benchmark_description/bsift/BSIFTAlgorithm.h>

namespace feitir {

    /**
     * Class which represents description of retrieval benchmark
     */
    class RetrievalBenchmark : public JSONObject {
    public:

        /**
         * Path to database holding test images
         * @return
         */
        const string &getTestDatabasePath() const;

        /**
         * Path and file name of file where results will be stored
         * @return
         */
        const string &getResultFile() const;

        /**
         * Type of matching method used to compute similarity between images
         * @return
         */
        const string &getMatchingMethod() const;

        /**
         * Is time measurement enabled
         * @return
         */
        boolean getTimeMeasure() const;

        /**
         * Inner object, indexer description
         * @return
         */
        const IndexerMethodPtr &getIndexerMethod() const;

        /**
         * Inner object, bsift extractor algorithm description
         * @return
         */
        const BSIFTAlgorithmPtr &getBsiftAlgorithm() const;

    protected:
        virtual FieldNames basicFieldNames() const override;
        virtual void setBasicFields(const ValuesMap &valuesMap) override;
        virtual FieldNames innerObjectFieldNames() const override;
        virtual std::map<FName, JSONObjectPtr> innerObjectTypes() const override;
        virtual void setInnerObjectsField(const InnerObjectsValuesMap &innerObjectsValuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        static const std::vector<std::string> OBJECT_NAMES;

        /**
         * Test database location
         */
        string testDatabasePath;

        /**
         * Result file path
         */
        string resultFile;

        /**
         * method used to compute matching weight between images
         */
        string matchingMethod;

        /**
         * flag which indicates if time measurement is enabled
         */
        boolean timeMeasure;

        /**
         * Indexer method description
         */
        IndexerMethodPtr indexerMethod;

        /**
         * BSIFT algorithm description
         */
        BSIFTAlgorithmPtr bsiftAlgorithm;
    };

    using RetrievalBenchmarkPtr = std::shared_ptr<RetrievalBenchmark>;
}


#endif //FEITIR_RETRIEVALBENCHMARK_H
