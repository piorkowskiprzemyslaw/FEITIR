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
        const std::string & getDatabasePath() const;
        const std::string & getVocabularyPath() const;
        const std::string & getVocabularyType() const;
        bool isMeasureTime() const;
        const std::string & getResultFile() const;
        BSIFTMethodDescriptionPtr getMethodDescription() const;

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

        std::string databasePath;
        std::string vocabularyPath;
        std::string vocabularyType;
        bool measureTime;
        std::string resultFile;
        BSIFTMethodDescriptionPtr methodDescription;
    };

    using BSIFTBenchmarkDescriptionPtr = std::shared_ptr<BSIFTBenchmarkDescription>;
}


#endif //FEITIR_BSIFTBENCHMARKDESCRIPTION_H
