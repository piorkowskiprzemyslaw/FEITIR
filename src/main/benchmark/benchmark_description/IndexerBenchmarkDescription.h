//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_INDEXERBENCHMARKDESCRIPTION_H
#define FEITIR_INDEXERBENCHMARKDESCRIPTION_H

#include "src/main/util/JSON/JSONObject.h"

namespace feitir {

    class IndexerBenchmarkDescription : public JSONObject {
    public:
        const std::string & getMethod() const;
        const std::string & getDatabasePath() const;
        const std::string & getVocabularyType() const;
        const std::string & getVocabularyPath() const;
        const std::string & getResultFile() const;

    protected:
        virtual FieldNames basicFieldNames() const override;
        virtual void setBasicFields(const ValuesMap &valuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::vector<std::string> FIELD_NAMES;

        std::string method;
        std::string databasePath;
        std::string vocabularyType;
        std::string vocabularyPath;
        std::string resultFile;
    };

    using IndexerBenchmarkDescriptionPtr = std::shared_ptr<IndexerBenchmarkDescription>;
}


#endif //FEITIR_INDEXERBENCHMARKDESCRIPTION_H
