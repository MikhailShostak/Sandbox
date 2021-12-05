#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include "ObjectEditor.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationStateProperties : public LegacyClassGen::ObjectEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationStateProperties This;
    typedef UI::ListView Super;
    typedef void Interfaces;
public:
    ApplicationStateProperties();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    LegacyClassGen::NodeData data;
public:

    ADelegate<void(const String &)> identifierChanged;

    void setData(const LegacyClassGen::NodeData &data)
    {
        this->data = data;
        onLoad(data.Data);

        //notifyUpdateAllItems();
    }

    /*ApplicationStateProperties()
    {
        setAdapter(this);
    }


    SizeType getCountItems(const AObject &sender) const override
    {
        return 2;
    }

    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override
    {
        switch (index)
        {
        case 0:
        {
            Label* label = Create<Label>();
            label->setText(data.Type);
            return label;
        }
        case 1:
        {
            TextField* textField = Create<TextField>();
            textField->setText(data.Identifier);
            textField->eventChannel.registerDelegate([this](TextEditFinishedEvent &event) {
                identifierChanged(event.getText());
            });
            return textField;
        }
        }
    }*/
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
