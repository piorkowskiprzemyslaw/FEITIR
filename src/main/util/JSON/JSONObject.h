//
// Created by przemek on 23.05.16.
//

#ifndef FEITIR_JSONOBJECT_H
#define FEITIR_JSONOBJECT_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace feitir {

    /**
     * Abstract JSON object
     */
    class JSONObject {
    public:
        JSONObject() = default;
        ~JSONObject() = default;

        void create(const boost::property_tree::ptree& propertyTree);

    protected:
        using JSONObjectPtr = std::shared_ptr<JSONObject>;

        using FName = std::string;
        using FValue = std::string;
        using ValuesMap = std::map<FName, FValue>;
        using ArrayObjectsValuesMap = std::map<FName, std::vector<JSONObjectPtr>>;
        using InnerObjectsValuesMap = std::map<FName, JSONObjectPtr>;
        using FieldNames = std::vector<FName>;

        virtual FieldNames basicFieldNames() const;
        virtual void setBasicFields(const ValuesMap& valuesMap);
        virtual FieldNames arrayOfObjectsFieldNames() const;
        virtual std::map<FName, JSONObjectPtr> arrayOfObjectTypes() const;
        virtual void setArrayOfObjectsField(const ArrayObjectsValuesMap& arrayObjectsValuesMap);
        virtual FieldNames innerObjectFieldNames() const;
        virtual std::map<FName, JSONObjectPtr> innerObjectTypes() const;
        virtual void setInnerObjectsField(const InnerObjectsValuesMap& innerObjectsValuesMap);
        virtual JSONObjectPtr constructNewObject() const = 0;
    };

    template <class T>
    std::shared_ptr<T> getJSONRootObjectFromFile(const std::string& filename, const std::string& objectName) {
        boost::property_tree::ptree propertyTree;
        boost::property_tree::read_json(filename, propertyTree);
        auto objectPtreeOpt = propertyTree.get_child_optional(objectName);
        if (objectPtreeOpt) {
            auto objPtr = std::make_shared<T>();
            objPtr->create(*objectPtreeOpt);
            return objPtr;
        } else {
            return nullptr;
        }
    }
};


#endif //FEITIR_JSONOBJECT_H
