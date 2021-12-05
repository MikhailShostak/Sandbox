#pragma once

#include "ASingleton.h"

class Serializable;

struct EnumInfo
{
    String name;
    Array<String> values;

    explicit operator bool() const { return !name.empty(); }
};

struct MetaObjectInformation : public ASingleton<MetaObjectInformation>
{
    Map<size_t, EnumInfo> enums;
    Map<size_t, EnumInfo> flags;
    Array<Serializable *> allocatedObjects;

    MetaObjectInformation()
    {
        allocatedObjects.reserve(1024 * 1024); // Allocate space for ~1M objects (4/8mb on 32/64bit system)
    }

    template<typename Type>
    EnumInfo findEnum() const
    {
        auto it = enums.find(AMeta::getStaticTypeHash<Type>());

        if (it != enums.end())
        {
            return it->second;
        }

        return {};
    }

    EnumInfo findEnum(const String &name) const
    {
        auto it = std::find_if(enums.begin(), enums.end(), [&](const auto &v) {
            return v.second.name == name;
        });

        if (it != enums.end())
        {
            return it->second;
        }

        return {};
    }

    template<typename Type>
    EnumInfo findFlags() const
    {
        auto it = flags.find(AMeta::getStaticTypeHash<Type>());

        if (it != flags.end())
        {
            return it->second;
        }

        return {};
    }

    EnumInfo findFlags(const String &name) const
    {
        auto it = std::find_if(flags.begin(), flags.end(), [&](const auto &v) {
            return v.second.name == name;
        });

        if (it != flags.end())
        {
            return it->second;
        }

        return {};
    }
};

class Serializable
{
public:
    Serializable()
    {
        auto &i = MetaObjectInformation::getInstance();
        i.allocatedObjects.push_back(this);
    }
    Serializable(const Serializable &serializable)
    {
        auto &i = MetaObjectInformation::getInstance();
        i.allocatedObjects.push_back(this);
    }
    Serializable(Serializable &&serializable)
    {
        auto &i = MetaObjectInformation::getInstance();
        i.allocatedObjects.push_back(this);
    }

    Serializable &operator =(const Serializable &serializable) = default;
    Serializable &operator =(Serializable &&serializable) = default;

    virtual ~Serializable()
    {
        auto &i = MetaObjectInformation::getInstance();
        auto it = std::find(i.allocatedObjects.begin(), i.allocatedObjects.end(), this);
        if (it != i.allocatedObjects.end())
        {
            *it = i.allocatedObjects[i.allocatedObjects.size() - 1];
            i.allocatedObjects.erase(i.allocatedObjects.end() - 1);
        }
        else
        {
            printf("Warning: Bad pointer 0x%p\r\n", this);
        }
    }
    virtual void serialize(class AJSONObject &object) const {}
    virtual void deserialize(const class AJSONObject &object) {}
};
