#pragma once

#include <Foundation>
#include <Data>

class MetaObject
{
public:
    
    struct Property
    {
        size_t typeHash = 0;

        bool isPersistent : 1;
        bool isBoolean : 1;
        bool isInteger : 1;
        bool isFloat : 1;
        bool isEnum : 1;
        bool isClass : 1;
        bool isEmbedded : 1;

        ADelegate<AVariant(AObject *object)> getter;
        ADelegate<void(AObject *object, const AVariant &)> setter;
    };

    size_t hash = 0;
    Meta::ConstructorPointer<AObject> constructor;
    ADelegate<void(const AObject &object, AJSONObject &data)> serialize;
    ADelegate<void(const AJSONObject &data, AObject &object)> deserialize;
    Map<String, Property> properties;
    MetaObject *baseObject = nullptr;

    Map<String, Property> getAllProperties() const
    {
        Map<String, Property> result = properties;
        if (baseObject)
        {
            auto baseProperties = baseObject->getAllProperties();
            result.insert(baseProperties.begin(), baseProperties.end());
        }
        return result;
    }

    bool hasProperty(const String &name) const
    {
        auto it = properties.find(name);
        return it != properties.end();
    }

    bool hasPropertyGetter(const String &name) const
    {
        auto it = properties.find(name);
        return it != properties.end() && it->second.getter;
    }

    bool hasPropertySetter(const String &name) const
    {
        auto it = properties.find(name);
        return it != properties.end() && it->second.setter;
    }

    AVariant getProperty(AObject *object, const String &name) const
    {
        auto allProperties = getAllProperties();
        auto it = allProperties.find(name);
        if (it == allProperties.end())
        {
            return AVariant();
        }
        if (!it->second.getter)
        {
            return AVariant();
        }
        return it->second.getter(object);
    }

    void setProperty(AObject *object, const String &name, const AVariant &value) const
    {
        auto allProperties = getAllProperties();
        auto it = allProperties.find(name);
        if (it == allProperties.end())
        {
            return;
        }
        if (!it->second.setter)
        {
            return;
        }
        it->second.setter(object, value);
    }

    template<typename OwnerType, typename ValueType, typename GetterType, typename SetterType>
    void registerMetaProperty(const String &name, GetterType &&getter, SetterType &&setter, bool persistent = false)
    {
        using PropertyType = typename std::remove_reference<typename std::invoke_result<GetterType, OwnerType>::type>::type;
        using ResolvedType = typename std::conditional<std::is_enum<PropertyType>::value, size_t, ValueType>::type;
        properties[name] = Property{
            AMeta::getStaticTypeHash<PropertyType>(),
            persistent,
            std::is_same<PropertyType, bool>::value,
            std::is_integral<PropertyType>::value,
            std::is_floating_point<PropertyType>::value,
            std::is_enum<PropertyType>::value,
            std::is_class<PropertyType>::value,
            std::is_object<PropertyType>::value,
            getter ? ADelegate<AVariant(AObject *object)>([getter](AObject *object) { return AVariant((static_cast<OwnerType *>(object)->*getter)()); }) : nullptr,
            setter ? ADelegate<void(AObject *object, const AVariant &)>([setter](AObject *object, const AVariant &value) { if (value.isValue<ResolvedType>()) { (static_cast<OwnerType *>(object)->*setter)(ValueType(value.asValue<ResolvedType>())); } }) : nullptr,
        };
    }
};

class MetaObjectManager : public ASingleton<MetaObjectManager>
{
    Map<String, MetaObject *> namedMetaObjects;
public:

    Map<size_t, Array<String>> enums;
    mutable Map<size_t, MetaObject *> metaObjects;

    template<typename Type>
    MetaObject &getMetaObject() const
    {
        static MetaObject object;
        static bool loaded = false;
        if (!loaded)
        {
            if constexpr (!std::is_abstract_v<Type>)
            {
                object.hash = AMeta::getStaticTypeHash<Type>();
                object.constructor = &CreateAs<Type, AObject>;
            }
            metaObjects.insert({ AMeta::getStaticTypeHash<Type>(), &object });
            loaded = true;
        }
        return object;
    }

    void registerMetaObject(const String &name, MetaObject &object)
    {
        namedMetaObjects.insert({ name, &object });
    }

    void unregisterMetaObject(const String &name)
    {
        namedMetaObjects.erase(name);
    }

    MetaObject *findMetaObject(const String &name) const
    {
        auto it = namedMetaObjects.find(name);
        if (it == namedMetaObjects.end())
        {
            return nullptr;
        }

        return it->second;
    }
};

//TODO: remove this hack
#include "MetaObjectSerializationHelper.h"
