//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BSIFTBENCHMARKDESCRIPTION_H
#define FEITIR_BSIFTBENCHMARKDESCRIPTION_H

#include "src/main/benchmark/BenchmarkDescription.h"

namespace feitir {
    class BSIFTBenchmarkDescription : public BenchmarkDescription {
    public:
        BSIFTBenchmarkDescription();
        static std::vector<std::string> getFieldNames();
        virtual void setPropertiesValues(const std::map<std::string, std::string> valuesMap) override;
        const std::string & getMethod() const;
        const std::string & getDatabasePath() const;
        const std::string & getVocabularyPath() const;
        bool isMeasureTime() const;
        const std::string & getResultFile() const;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        std::string method;
        std::string databasePath;
        std::string vocabularyPath;
        bool measureTime;
        std::string resultFile;
    };

    using BSIFTBenchmarkDescriptionPtr = typename std::shared_ptr<BSIFTBenchmarkDescription>;
}


#endif //FEITIR_BSIFTBENCHMARKDESCRIPTION_H
