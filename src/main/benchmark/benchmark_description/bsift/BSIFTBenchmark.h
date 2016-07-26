//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BSIFTBENCHMARKDESCRIPTION_H
#define FEITIR_BSIFTBENCHMARKDESCRIPTION_H

#include "src/main/util/JSON/JSONObject.h"
#include "BSIFTMethod.h"
#include "BSIFTAlgorithm.h"

namespace feitir {

    class BSIFTBenchmark : public JSONObject {
    public:
        const string & getDatabasePath() const;
        boolean isMeasureTime() const;

        const BSIFTAlgorithmPtr &getAlgorithm() const;

        const string & getResultFile() const;
        const std::vector<number> & getASet() const;
        const std::vector<number> & getBSet() const;

    protected:
        virtual FieldNames basicFieldNames() const override;
        virtual void setBasicFields(const ValuesMap &valuesMap) override;
        virtual FieldNames innerObjectFieldNames() const override;
        virtual std::map<FName, JSONObjectPtr> innerObjectTypes() const override;
        virtual void setInnerObjectsField(const InnerObjectsValuesMap &innerObjectsValuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        static const std::string BSIFT_ALGORITHM;

        string databasePath;
        boolean measureTime;
        string resultFile;
        BSIFTAlgorithmPtr algorithm;
        std::vector<number> aSet;
        std::vector<number> bSet;
    };

    using BSIFTBenchmarkPtr = std::shared_ptr<BSIFTBenchmark>;
}


#endif //FEITIR_BSIFTBENCHMARKDESCRIPTION_H
