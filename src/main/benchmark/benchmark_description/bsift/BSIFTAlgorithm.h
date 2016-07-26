//
// Created by Przemek Piórkowski on 24.07.2016.
//

#ifndef FEITIR_BSIFTALGORITHM_H
#define FEITIR_BSIFTALGORITHM_H

#include <src/main/util/JSON/JSONObject.h>
#include <src/main/benchmark/benchmark_description/bsift/BSIFTMethod.h>

namespace feitir {
    class BSIFTAlgorithm : public JSONObject {
    public:
        const JSONObject::string &getDatabasePath() const;
        const JSONObject::string &getVocabularyPath() const;
        const JSONObject::string &getVocabularyType() const;
        const BSIFTMethodPtr &getBsiftMethod() const;

    protected:
        virtual JSONObjectPtr constructNewObject() const override;
        virtual FieldNames basicFieldNames() const override;
        virtual void setBasicFields(const ValuesMap &valuesMap) override;
        virtual FieldNames innerObjectFieldNames() const override;
        virtual std::map<FName, JSONObjectPtr> innerObjectTypes() const override;
        virtual void setInnerObjectsField(const InnerObjectsValuesMap &innerObjectsValuesMap) override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        static const std::string BSIFT_METHOD;

        string databasePath;
        string vocabularyPath;
        string vocabularyType;
        BSIFTMethodPtr bsiftMethodDescriptionPtr;
    };

    using BSIFTAlgorithmPtr = std::shared_ptr<BSIFTAlgorithm>;
}


#endif //FEITIR_BSIFTALGORITHM_H
