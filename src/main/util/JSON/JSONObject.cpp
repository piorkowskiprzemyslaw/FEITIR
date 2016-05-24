//
// Created by przemek on 23.05.16.
//

#include "JSONObject.h"

namespace feitir {
    void JSONObject::create(const boost::property_tree::ptree &propertyTree) {
        ValuesMap valuesMap;

        // basic fields setup
        for (const auto& field : basicFieldNames()) {
            boost::optional<std::string> valueOptional = propertyTree.get_optional<std::string>(field);
            if (valueOptional) {
                valuesMap.insert({field, *valueOptional});
            }
        }
        setBasicFields(valuesMap);

        // arrays of objects setup
        ArrayObjectsValuesMap arrayObjects;
        auto arrayOfObjTypes = arrayOfObjectTypes();
        for (const auto& field : arrayOfObjectsFieldNames()) {
            std::vector<JSONObjectPtr> fieldObjects;
            boost::optional<const boost::property_tree::ptree &> childOptional = propertyTree.get_child_optional(field);
            if (childOptional) {
                for (const auto& arrayObject : *childOptional) {
                    auto obj = arrayOfObjTypes.at(field)->constructNewObject();
                    obj->create(arrayObject.second);
                    fieldObjects.push_back(obj);
                }
            }
            arrayObjects.insert({field, fieldObjects});
        }
        setArrayOfObjectsField(arrayObjects);

        // inner objects setup
        InnerObjectsValuesMap innerObjects;
        auto innerObjTypes = innerObjectTypes();
        for (const auto& field : innerObjectFieldNames()) {
            boost::optional<const boost::property_tree::ptree &> innerOptional = propertyTree.get_child_optional(field);
            if (innerOptional) {
                auto obj = innerObjTypes.at(field)->constructNewObject();
                obj->create(*innerOptional);
                innerObjects.insert({field, obj});
            }
        }
        setInnerObjectsField(innerObjects);
    }

    JSONObject::FieldNames JSONObject::basicFieldNames() const {
        return {};
    }

    void JSONObject::setBasicFields(const ValuesMap& valuesMap) { }

    JSONObject::FieldNames JSONObject::arrayOfObjectsFieldNames() const {
        return {};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> JSONObject::arrayOfObjectTypes() const {
        return {};
    }

    void JSONObject::setArrayOfObjectsField(const ArrayObjectsValuesMap& arrayObjectsValuesMap) { }

    JSONObject::FieldNames JSONObject::innerObjectFieldNames() const {
        return {};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> JSONObject::innerObjectTypes() const {
        return {};
    }

    void JSONObject::setInnerObjectsField(const InnerObjectsValuesMap& innerObjectsValuesMap) { }
}

