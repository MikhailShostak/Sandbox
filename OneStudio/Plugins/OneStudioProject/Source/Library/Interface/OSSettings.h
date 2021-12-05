#pragma once

#include <Data>

#include "ATableAdapter.h"

/*#define ASingletone(type, identifier) \
static type &identifier() \
{ \
    static type identifier; \
    return identifier; \
}*/

namespace OneStudioProject2
{

class SettingsInstance
{
public:
    virtual ~SettingsInstance() {}
};

}

class OSSettings : public ATableAdapter<String>
{

    OSSettings *parent = nullptr;

public:

    static String processWithEnvironment(const String &string, const StringsHashMap &additionalValues = StringsHashMap::EmptyHashMap());
    String processWithEnvironment(const String &string, SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const;

    OSSettings *getParent() const
    {
        return this->parent;
    }

    void setParent(OSSettings *parent)
    {
        this->parent = parent;
    }

    ItemType getItemPlaceholder(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const
    {
        if(this->parent)
        {
            return this->parent->getItemValue(groupIndex, rowIndex, columnIndex);
        }

        return ItemType();
    }

    ItemType getItemValue(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const
    {
        ItemType value = getItem(groupIndex, rowIndex, columnIndex);
        if(value)
        {
            return processWithEnvironment(value, groupIndex, rowIndex, columnIndex);
        }

        return getItemPlaceholder(groupIndex, rowIndex, columnIndex);
    }

    virtual SharedReference<AFileDataInstance<AJSONDataStorage>> getFileData() const = 0;


    virtual SharedReference<Serializable> getBaseData() const = 0;
};

template<typename DataType>
class OSTemplateSettings : public OSSettings, public OneStudioProject2::SettingsInstance
{

    SharedReference<DataType> data = createNew<DataType>();

public:

    const SharedReference<DataType> &getData() const
    {
        return data;
    }

    SharedReference<AFileDataInstance<AJSONDataStorage>> getFileData() const override
    {
        return data.template as<AFileDataInstance<AJSONDataStorage>>();
    }

    SharedReference<Serializable> getBaseData() const override
    {
        return data.template as<Serializable>();
    }
};
