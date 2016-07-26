//
// Created by przemek on 24.05.16.
//

#ifndef FEITIR_BSIFTMETHODDESCRIPTION_H
#define FEITIR_BSIFTMETHODDESCRIPTION_H

#include "src/main/util/JSON/JSONObject.h"

namespace feitir {

    class BSIFTMethod : public JSONObject {
    public:
        const string & getMethod() const;
        number getL() const;
        number getT() const;
        number getN() const;

    protected:
        virtual FieldNames basicFieldNames() const override;
        virtual void setBasicFields(const ValuesMap &valuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        string method;
        number L;
        number T;
        number N;
    };

    using BSIFTMethodPtr = std::shared_ptr<BSIFTMethod>;
}


#endif //FEITIR_BSIFTMETHODDESCRIPTION_H
