#pragma once

#include <Experimental>

#include "Core/BaseCGType.h"
#include "Includes/CGTypeGroup.gen.h"
#include "Includes/TypeInfo.gen.h"

enum FieldEditorLayoutType
{
    Inline,
    Multiline
};

class FieldEditor
{
public:
    AJSONValue defaultValue;
    bool isChanged = false;

    ADelegate<void()> onValueChanged;
    ADelegate<void()> onValueUpdated;
    virtual ~FieldEditor() {}
    virtual void setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo) {}

    void setDefaultValue(const AJSONValue &value)
    {
        defaultValue = value;
        if(!isChanged)
        {
            onSerialize(value);
        }
    }

    void serialize(const AJSONValue &value)
    {
        AAssert(false, "change to serialzeValue");
        if (value)
        {
            isChanged = true;
            onSerialize(value);
        }
        else
        {
            isChanged = false;
        }
    }

    AJSONValue deserialize()
    {
        AAssert(false, "change to deserialzeValue");
        return isChanged ? onDeserialize() : AJSONValue();
    }

    void serializeValue(const AJSONValue &value)
    {
        if (value)
        {
            isChanged = true;
            onSerialize(value);
            if (onValueUpdated)
            {
                onValueUpdated();
            }
        }
        else
        {
            onSerialize(defaultValue);
            isChanged = false;
        }
    }

    AJSONValue deserializeValue()
    {
        return isChanged ? onDeserialize() : AJSONValue();
    }

    void notifyValueChange()
    {
        isChanged = true;
        onValueChanged();
        if (onValueUpdated)
        {
            onValueUpdated();
        }
    }

    void notifyValueReset()
    {
        isChanged = false;
        onValueChanged();
        if (onValueUpdated)
        {
            onValueUpdated();
        }
    }

    virtual FieldEditorLayoutType getLayoutType() const { return Inline; }
protected:
    virtual void onSerialize(const AJSONValue &value) = 0;
    virtual AJSONValue onDeserialize() = 0;
};

//Copied from OneStudioPlatform
template<typename Type>
struct AbstractSingleton2
{
public:
    static Type &getInstance()
    {
        Type *singleton = reinterpret_cast<Type *>(ASingletonStorage::findSingleton(typeid(Type).hash_code()));
        AAssert(singleton, "Singleton is undefined");
        return *singleton;
    }

    template<typename ReturnType>
    static ReturnType &getInstanceAs()
    {
        return static_cast<ReturnType &>(getInstance());
    }

    template<typename DerivedType>
    static DerivedType &createInstance()
    {
        static_assert(std::is_base_of_v<Type, DerivedType>, "DerivedType is not derived class of Type");
        static DerivedType singleton;
        return singleton;
    }

protected:
    AbstractSingleton2()
    {
        AAssert(!ASingletonStorage::findSingleton(typeid(Type).hash_code()), "Singleton already exists");
        ASingletonStorage::registerSingleton(typeid(Type).hash_code(), static_cast<Type *>(this));
    }
};

namespace LegacyClassGen
{

class Context : public AbstractSingleton2<Context>
{
public:
    virtual void registerType(class MetaObject &type, const String &name, CGTypeGroup group) = 0;
    virtual void registerEditor(class MetaObject &editor, class MetaObject &type) = 0;
    [[deprecated("Use registerPropertyTypeEditor instead")]]
    virtual void registerFieldEditorForTypes(class MetaObject &editor, const String &name) = 0;
    [[deprecated("Use registerPropertyTypeEditor instead")]]
    virtual void registerFieldEditorForInstances(class MetaObject &editor, const String &name) = 0;

    virtual bool canCreateEditorForType(const String &name) = 0;
    virtual bool canCreateEditorForInstance(const String &name) = 0;

    virtual SharedReference<FieldEditor> createFieldEditor(const LegacyClassGen::TypeInfo &typeInfo, const SharedReference<LegacyClassGen::BaseCGType> &type) = 0;

    virtual APair<SharedReference<FieldEditor>, SharedReference<UI::View>> createFieldEditorAndView(const String &title, const LegacyClassGen::TypeInfo &typeInfo, const SharedReference<LegacyClassGen::BaseCGType> &type) = 0;

    //TODO: replace names
    virtual void registerPropertyTypeEditor(class MetaObject &editor, const String &name) = 0;
    virtual void registerPropertyInstanceEditor(class MetaObject &editor, const String &name) = 0;
};

class TypeExtension
{
public:
    virtual void load() = 0;
    virtual ~TypeExtension() {}
};

}
