#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationFlowProperties : public UI::ListView, public UI::ItemAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationFlowProperties This;
    typedef UI::ListView Super;
    typedef void Interfaces;
public:
    ApplicationFlowProperties();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    AJSONObject data;
public:

    using Super = UI::ListView;

    ADelegate<void(const String &)> entryPointChanged;
    ADelegate<void(const String &)> entryPointTypeChanged;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        setAdapter(this);
    }

    void setData(const AJSONValue &data)
    {
        this->data = data.toObject();

        notifyUpdateAllItems();
    }

    UI::SizeType getCountItems(const AObject &sender) const override
    {
        return 2;
    }

    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override
    {
        switch (index)
        {
        case 0:
        {
            UI::TextField* textField = CreateShared<UI::TextField>();
            String identifier;
            if (data.read("EntryPoint", identifier))
            {
                textField->setText(identifier);
            }
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                entryPointChanged(event.getText());
            });
            return textField;
        }
        case 1:
        {
            UI::TextField* textField = CreateShared<UI::TextField>();
            String identifier;
            if (data.read("EntryPointType", identifier))
            {
                textField->setText(identifier);
            }
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                entryPointTypeChanged(event.getText());
            });
            return textField;
        }
        }
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
