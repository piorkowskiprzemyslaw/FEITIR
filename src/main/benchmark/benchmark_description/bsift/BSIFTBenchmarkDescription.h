//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BSIFTBENCHMARKDESCRIPTION_H
#define FEITIR_BSIFTBENCHMARKDESCRIPTION_H

#include "src/main/util/JSON/JSONObject.h"
#include "BSIFTMethodDescription.h"

namespace feitir {

    class BSIFTBenchmarkDescription : public JSONObject {
    public:
        const string & getDatabasePath() const;
        const string & getVocabularyPath() const;
        const string & getVocabularyType() const;
        boolean isMeasureTime() const;
        const string & getResultFile() const;
        BSIFTMethodDescriptionPtr getMethodDescription() const;
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
        static const std::string BSIFT_METHOD;

        string databasePath;
        string vocabularyPath;
        string vocabularyType;
        boolean measureTime;
        string resultFile;
        BSIFTMethodDescriptionPtr methodDescription;
        std::vector<number> aSet;
        std::vector<number> bSet;
    };

    using BSIFTBenchmarkDescriptionPtr = std::shared_ptr<BSIFTBenchmarkDescription>;
}


#endif //FEITIR_BSIFTBENCHMARKDESCRIPTION_H
