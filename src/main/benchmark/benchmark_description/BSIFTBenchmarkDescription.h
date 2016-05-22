//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BSIFTBENCHMARKDESCRIPTION_H
#define FEITIR_BSIFTBENCHMARKDESCRIPTION_H

#include "src/main/benchmark/BenchmarkDescription.h"

namespace feitir {

    class BSIFTMethodDescription {
    public:
        BSIFTMethodDescription() = default;
        ~BSIFTMethodDescription() = default;
        static std::vector<std::string> getFieldNames();
        void setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap);
        const std::string & getMethod() const;
        int getL() const;
        int getT() const;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        std::string method;
        int L;
        int T;
    };

    class BSIFTBenchmarkDescription : public BenchmarkDescription {
    public:
        BSIFTBenchmarkDescription();
        static std::vector<std::string> getFieldNames();
        static std::map<std::string, std::vector<std::string>> getCompoundFieldsNames();
        virtual void setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap) override;
        virtual void setCompoundPropertiesValues(
                const std::map<std::string, std::map<std::string, std::string>> compoundProperties) override;
        const std::string & getDatabasePath() const;
        const std::string & getVocabularyPath() const;
        bool isMeasureTime() const;
        const std::string & getResultFile() const;
        const std::string & getVocabularyType() const;
        const BSIFTMethodDescription & getMethodDescription() const;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        static const std::map<std::string, std::vector<std::string>> COMPOUND_FIELDS;
        std::string databasePath;
        std::string vocabularyPath;
        std::string vocabularyType;
        bool measureTime;
        std::string resultFile;
        BSIFTMethodDescription methodDescription;
    };

    using BSIFTBenchmarkDescriptionPtr = typename std::shared_ptr<BSIFTBenchmarkDescription>;
}


#endif //FEITIR_BSIFTBENCHMARKDESCRIPTION_H
