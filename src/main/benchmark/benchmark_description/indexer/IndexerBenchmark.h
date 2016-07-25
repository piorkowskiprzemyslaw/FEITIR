//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_INDEXERBENCHMARKDESCRIPTION_H
#define FEITIR_INDEXERBENCHMARKDESCRIPTION_H

#include <src/main/algorithm/indexer/Indexer.h>
#include "src/main/util/JSON/JSONObject.h"
#include "IndexerMethod.h"
#include "BSIFTAlgorithm.h"

namespace feitir {

    class IndexerBenchmark : public JSONObject {
    public:
        IndexerMethodPtr getMethod() const;
        const JSONObject::string & getDatabasePath() const;
        const JSONObject::string & getResultFile() const;
        const JSONObject::string & getMatchingFunc() const;
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

        IndexerMethodPtr method;
        BSIFTAlgorithmPtr bsiftAlgorithm;
        JSONObject::string databasePath;
        JSONObject::string resultFile;
        JSONObject::string matchingFunc;
    };

    using IndexerBenchmarkPtr = std::shared_ptr<IndexerBenchmark>;
}


#endif //FEITIR_INDEXERBENCHMARKDESCRIPTION_H
