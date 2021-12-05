#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class EventDetailsView : public UI::GroupPanel, public UI::ItemAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EventDetailsView This;
    typedef UI::GroupPanel Super;
    typedef std::tuple<UI::ItemAdapter> Interfaces;
public:
    EventDetailsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::TextField> nameView;
    SharedReference<UI::TextButton> parametersAddButton;
    SharedReference<UI::ListView> parametersView;
    void onHierarchyCreate();
//CLASSGEN END REGION
    LegacyClassGen::EventInfo eventInfo;
public:
    /*SharedReference<UI::Label> nameLabel = CreateShared<UI::Label>();
    SharedReference<UI::TextField> nameView = CreateShared<UI::TextField>();
    SharedReference<UI::Label> parametersLabel = CreateShared<UI::Label>();
    SharedReference<UI::Button> parametersButton = CreateShared<UI::Button>();
    SharedReference<UI::ListView> parametersView = CreateShared<UI::ListView>();*/

    ADelegate<bool(const String &oldName, const String &newName)> onNameChanged;
    ADelegate<void(const LegacyClassGen::EventInfo &eventInfo)> onChanged;

    const LegacyClassGen::EventInfo &getEventInfo() const
    {
        return this->eventInfo;
    }

    void setEventInfo(const LegacyClassGen::EventInfo &eventInfo)
    {
        headerLabel->setText("Event: " + eventInfo.Name);

        this->eventInfo = eventInfo;
        nameView->setText(eventInfo.Name);
        parametersView->notifyUpdateAllItems();
    }

    void onLoad(ALoadEvent &event) override
    {
        if (!parametersView->getAdapter())
        {
            parametersView->setAdapter(this);

            nameView->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                if (onNameChanged(eventInfo.Name, event.getText()))
                {
                    eventInfo.Name = event.getText();
                    onChanged(eventInfo);
                }
            });

            parametersAddButton->eventChannel.registerDelegate([this](UI::TapGestureEvent &event) {
                LegacyClassGen::Parameter p;
                p.Type.Name = "Boolean";
                p.Name = "NewParameter";
                eventInfo.InputArguments.push_back(p);
                parametersView->notifyInsertItems(eventInfo.InputArguments.size() - 1);
                onChanged(eventInfo);
            });
        }

        Super::onLoad(event);
    }

    virtual UI::SizeType getCountItems(const AObject &sender) const { return eventInfo.InputArguments.size(); }
    virtual SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index)
    {
        auto textField = CreateShared<UI::TextField>();
        textField->setText(writeRecursively(eventInfo.InputArguments[index].Type) + " " + eventInfo.InputArguments[index].Name);
        return textField;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
