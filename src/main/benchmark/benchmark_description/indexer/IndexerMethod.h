//
// Created by Przemek Piórkowski on 21.07.2016.
//

#ifndef FEITIR_INDEXERMETHODDESCRIPTION_H
#define FEITIR_INDEXERMETHODDESCRIPTION_H

#include <src/main/util/JSON/JSONObject.h>

namespace feitir {
    class IndexerMethod : public JSONObject  {
    public:
        const string &getMethodName() const;
        const string &getVocabularyPath() const;
        const string &getVocabularyType() const;
        number getTreshold() const;
        number getK() const;
        number getN() const;
        number getR() const;
        number getCodeWordSize() const;

    protected:
        virtual JSONObjectPtr constructNewObject() const override;

        virtual FieldNames basicFieldNames() const override;

        virtual void setBasicFields(const ValuesMap &valuesMap) override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        string methodName;
        string vocabularyPath;
        string vocabularyType;
        number treshold;
        number K;
        number N;
        number R;
        number codeWordSize;

    };

    using IndexerMethodPtr = std::shared_ptr<IndexerMethod>;
}


#endif //FEITIR_INDEXERMETHODDESCRIPTION_H
