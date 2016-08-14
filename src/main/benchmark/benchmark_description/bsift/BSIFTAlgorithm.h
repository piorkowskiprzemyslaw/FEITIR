//
// Created by Przemek Piórkowski on 24.07.2016.
//

#ifndef FEITIR_BSIFTALGORITHM_H
#define FEITIR_BSIFTALGORITHM_H

#include <src/main/util/JSON/JSONObject.h>
#include <src/main/benchmark/benchmark_description/bsift/BSIFTMethod.h>

namespace feitir {

    /**
     * Class which represents BSIFT algorithm description.
     * This class holds all parameteres required for correct setup of any BSIFT extractor algorithm object.
     */
    class BSIFTAlgorithm : public JSONObject {
    public:
        /**
         * String holding path to train dataset
         * @return databasePath
         */
        const string &getDatabasePath() const;

        /**
         * String holding path to vocabulary created on train dataset
         * @return vocabularyPath
         */
        const string &getVocabularyPath() const;

        /**
         * String holding vocabulary type name
         * @return vocabularyType
         */
        const string &getVocabularyType() const;

        /**
         * Inner object, holds additional methods parameters, method name, etc.
         * @return BSIFTMethodPtr
         */
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
