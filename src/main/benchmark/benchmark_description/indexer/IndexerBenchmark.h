//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_INDEXERBENCHMARKDESCRIPTION_H
#define FEITIR_INDEXERBENCHMARKDESCRIPTION_H

#include <src/main/algorithm/indexer/Indexer.h>
#include "src/main/util/JSON/JSONObject.h"
#include "IndexerMethod.h"
#include "src/main/benchmark/benchmark_description/bsift/BSIFTAlgorithm.h"

namespace feitir {

    /**
     * Class which represents description of indexer benchmark
     */
    class IndexerBenchmark : public JSONObject {
    public:

        /**
         * Inner object, describes indexer method
         * @return shared pointer to IndexerMethod object
         */
        IndexerMethodPtr getMethod() const;

        /**
         * Path to database usead as test database in test phase
         * @return path to database
         */
        const JSONObject::string & getDatabasePath() const;

        /**
         * Path to file holding test results
         * @return
         */
        const JSONObject::string & getResultFile() const;

        /**
         * Inner object, describes BSIFT algorithm
         * @return shared pointer to BSIFTAlgorithm object
         */
        BSIFTAlgorithmPtr getBsiftAlgorithm() const;

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
         * Indexer method description
         */
        IndexerMethodPtr method;

        /**
         * BSIFT algorithm description
         */
        BSIFTAlgorithmPtr bsiftAlgorithm;

        /**
         * Test database path, each image in this database will be used as query during test run
         */
        string databasePath;

        /**
         * Path to file where results will be stored
         */
        string resultFile;
    };

    using IndexerBenchmarkPtr = std::shared_ptr<IndexerBenchmark>;
}


#endif //FEITIR_INDEXERBENCHMARKDESCRIPTION_H
