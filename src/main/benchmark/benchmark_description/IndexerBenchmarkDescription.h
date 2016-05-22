//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_INDEXERBENCHMARKDESCRIPTION_H
#define FEITIR_INDEXERBENCHMARKDESCRIPTION_H

#include "src/main/benchmark/BenchmarkDescription.h"

namespace feitir {
    class IndexerBenchmarkDescription : public BenchmarkDescription {
    public:

        IndexerBenchmarkDescription();
        static std::vector<std::string> getFieldNames();
        virtual void setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap) override;
        virtual void setCompoundPropertiesValues(
                        const std::map<std::string, std::map<std::string, std::string>> compoundProperties) override;
        const std::string & getMethod() const;
        const std::string & getDatabasePath() const;
        const std::string & getVocabularyPath() const;
        const std::string & getResultFile() const;
        const std::string & getVocabularyType() const;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        std::string method;
        std::string databasePath;
        std::string vocabularyType;
        std::string vocabularyPath;
        std::string resultFile;
    };

    using IndexerBenchmarkDescriptionPtr = typename std::shared_ptr<IndexerBenchmarkDescription>;
}


#endif //FEITIR_INDEXERBENCHMARKDESCRIPTION_H
