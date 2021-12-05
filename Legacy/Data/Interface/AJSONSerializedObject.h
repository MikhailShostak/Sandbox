#pragma once

class AJSONObject;

class AJSONSerializedObject
{
public:
    virtual ~AJSONSerializedObject() {}
    virtual bool serialize(AJSONObject &object) const = 0;
    virtual bool deserialize(const AJSONObject &object) = 0;
};
