//
// Created by przemek on 24.05.16.
//

#ifndef FEITIR_BSIFTMETHODDESCRIPTION_H
#define FEITIR_BSIFTMETHODDESCRIPTION_H

#include "src/main/util/JSON/JSONObject.h"

namespace feitir {

    /**
     * Class which represents BSIFT method description.
     *
     * Currently supported methods:
     *  - comparison_array
     *  - descriptor_median
     *  - descriptor_position_median
     *  - descriptor_voronoi_position
     *  - locality_sensitive_hashing
     *  - vectors_compare
     *
     */
    class BSIFTMethod : public JSONObject {
    public:

        /**
         * String holding method name
         * @return method
         */
        const string & getMethod() const;

        /**
         * Number holding L parameter value used in comparison_array
         * @return L
         */
        number getL() const;

        /**
         * Number holding T parameter value used in comparison_array
         * @return T
         */
        number getT() const;

        /**
         * Number holding N parameter value used in comparison_array and locality_sensitive_hashing
         * @return
         */
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
