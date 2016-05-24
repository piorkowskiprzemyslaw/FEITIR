//
// Created by przemek on 24.05.16.
//

#ifndef FEITIR_BSIFTMETHODDESCRIPTION_H
#define FEITIR_BSIFTMETHODDESCRIPTION_H

#include "src/main/util/JSON/JSONObject.h"

namespace feitir {

    class BSIFTMethodDescription : public JSONObject {
    public:
        const std::string & getMethod() const;
        int getL() const;
        int getT() const;

    protected:
        virtual FieldNames basicFieldNames() const override;
        virtual void setBasicFields(const ValuesMap &valuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        std::string method;
        int L;
        int T;
    };

    using BSIFTMethodDescriptionPtr = std::shared_ptr<BSIFTMethodDescription>;
}


#endif //FEITIR_BSIFTMETHODDESCRIPTION_H
