//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BENCHMARKDESCRIPTION_H
#define FEITIR_BENCHMARKDESCRIPTION_H

#include <iostream>
#include <memory>
#include <map>
#include <vector>

namespace feitir {

    enum class BenchmarkType {BSIFT, Indexer};

    BenchmarkType fromString(const std::string& str);

    class BenchmarkDescription {
    public:
        BenchmarkDescription(BenchmarkType type) : type{type} {};
        BenchmarkType getType() const;
        static std::string getTypeFieldName();
        virtual void setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap) = 0;
        virtual void setCompoundPropertiesValues(const std::map<std::string, std::map<std::string, std::string>> compoundProperties) = 0;

    private:
        BenchmarkType type;
    };

    using BenchmarkDescriptionPtr = typename std::shared_ptr<BenchmarkDescription>;
}


#endif //FEITIR_BENCHMARKDESCRIPTION_H
