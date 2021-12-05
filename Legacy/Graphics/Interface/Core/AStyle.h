#pragma once

#include <Foundation>

template<typename ObjectType>
class AStyle : public ASingleton<AStyle<ObjectType>>
{
    Array<ADelegate<void(ObjectType &object)>> valueDelegates;

public:

    void addProperty(const ADelegate<void(ObjectType &object)> &delegate)
    {
        valueDelegates.push_back(delegate);
    }

    void apply(ObjectType &object)
    {
        for (auto &delegate : valueDelegates)
        {
            delegate(object);
        }
    }
};

template<typename ObjectType, typename OtherObjectType, typename ValueType, typename OtherValueType>
inline void AddStyleProperty(void(OtherObjectType::*setter)(const ValueType &value), const OtherValueType &value)
{
    AStyle<ObjectType>::getInstance().addProperty([setter, value](ObjectType &object) {
        (object.*setter)(value);
    });
}

template<typename ObjectType, typename OtherObjectType, typename ValueType, typename OtherValueType>
inline void AddStyleProperty(void(OtherObjectType::*setter)(ValueType value), OtherValueType value)
{
    AStyle<ObjectType>::getInstance().addProperty([setter, value](ObjectType &object) {
        (object.*setter)(value);
    });
}

template<typename ObjectType>
inline void ApplyStyle(ObjectType &object)
{
    AStyle<ObjectType>::getInstance().apply(object);
}
