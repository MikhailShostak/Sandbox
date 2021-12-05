#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ObjectEditor.gen.h"

//CLASSGEN END REGION
#include "ViewNode.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ViewPropertiesEditor : public LegacyClassGen::ObjectEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ViewPropertiesEditor This;
    typedef LegacyClassGen::ObjectEditor Super;
    typedef void Interfaces;
public:
    ViewPropertiesEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
protected:
    ViewNode *node = nullptr;
public:

    const ViewNode *getNode() const
    {
        return this->node;
    }

    void setNode(ViewNode *node)
    {
        this->node = node;
        reloadInstance();
    }

    void reloadData() override
    {
        Super::reloadData();
        reloadInstance();
    }

    void reloadInstance()
    {
        if (node && node->View && propertiesData)
        {
            node->View->deserialize(propertiesData);
        }
    }

    void setValue(const String &propertyName, const AJSONValue &value)
    {
        auto it = std::find_if(propertiesTree->properties.begin(), propertiesTree->properties.end(), [&](const auto &value){
            return value->propertyName == propertyName;
        });
        if (it != propertiesTree->properties.end())
        {
            if ((*it)->editor)
            {
                (*it)->editor->serialize(value);
            }
            else if (!(*it)->embeddedProperties.empty())
            {
                propertiesTree->serializeInternal(value.toObject(), (*it)->embeddedProperties);
            }
            else
            {
                AAssert(false, "Property doesn't have editor and embedded properties");
            }
        }
    }

    void onNameChanged(const String &name)
    {
        node->Name = name;
        
        Super::onNameChanged(name);
    }
    void onTypeChanged(const String &type)
    {
        readRecursively(type, node->Type);
        node->updateInstance();

        Super::onTypeChanged(type);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
