#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"
#include "Includes/Editor.gen.h"
#include "Foundation"

#include "Foundation"

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "EditableProperty.h"
#include "FieldEditors/EmbeddedObjectFieldEditor.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ObjectEditor : public UI::GroupView, public LegacyClassGen::Editor, public UI::GroupAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ObjectEditor This;
    typedef UI::GroupView Super;
    typedef std::tuple<LegacyClassGen::Editor, UI::GroupAdapter> Interfaces;
protected:
    String Name;
LegacyClassGen::TypeInfo Type;
LegacyClassGen::TypeInfo BaseType;
public:
    ObjectEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    String getName() const;
    void setName(String const &Name);
    void setName(String &&Name);
    LegacyClassGen::TypeInfo getType() const;
    void setType(LegacyClassGen::TypeInfo const &Type);
    void setType(LegacyClassGen::TypeInfo &&Type);
    LegacyClassGen::TypeInfo getBaseType() const;
    void setBaseType(LegacyClassGen::TypeInfo const &BaseType);
    void setBaseType(LegacyClassGen::TypeInfo &&BaseType);
    void onHierarchyCreate();
//CLASSGEN END REGION
protected:
    AJSONObject propertiesData;
    SharedReference<LegacyClassGen::BaseCGType> typeData;

public:
    SharedReference<EmbeddedObjectFieldEditor> propertiesTree = CreateShared<EmbeddedObjectFieldEditor>();

    class EventsView : public ListView, public UI::ItemAdapter
    {
    public:
        ADelegate<void(const String &Name)> onBindingChanged;

        Array<LegacyClassGen::EventInfo> events;
        OrderedDictionary<String, String> bindings;

        void onLoad(ALoadEvent &event)
        {
            Super::onLoad(event);
            setAdapter(this);
        }

        UI::SizeType getCountItems(const AObject &sender) const { return events.size(); }
        SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType index)
        {
            SharedReference<UI::FlexBox> flexBox = CreateShared<UI::FlexBox>();
            flexBox->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);

            const String &name = events[index].Name;

            SharedReference<UI::Label> label = CreateShared<UI::Label>();
            WeakReference<UI::Label> l = label;
            label->setText(name);
            label->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
            flexBox->addView(label);

            /*SharedReference<UI::Button> button = CreateShared<UI::Button>();
            WeakReference<UI::Button> b = button;
            if (bindings.has(label->getText()))
            {
                button->setBackgroundImage(MinusButtonSmall);
            }
            else
            {
                button->setBackgroundImage(PlusButtonSmall);
            }
            button->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
            
            button->eventChannel.registerDelegate([this, l, b](UI::TapGestureEvent &event) {
                if (!bindings.has(l->getText()))
                {
                    bindings.push_back(l->getText());
                    b->setBackgroundImage(MinusButtonSmall);
                }
                else
                {
                    bindings.remove(l->getText());
                    b->setBackgroundImage(PlusButtonSmall);
                }
            });
            flexBox->addView(button);*/

            auto textField = CreateShared<UI::TextField>();
            auto it = bindings.find(name);
            if(it != bindings.end())
            {
                textField->setText(it->second);
            }
            textField->eventChannel.registerDelegate([this, name](UI::TextEditFinishedEvent &event) {
                bindings[name] = event.getText();
                onBindingChanged(name);
            });
            flexBox->addView(textField);

            flexBox->setData({ {}, {} });

            return flexBox;
        }
    };

    SharedReference<EventsView> eventsView = CreateShared<EventsView>();

    bool AllowBindingEvents = true;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        eventsView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);

        setProxyAdapter(this);
    }

    const LegacyClassGen::TypeInfo &getObjectType() const
    {
        return !Type.Name.empty() ? Type : BaseType;
    }

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override;
    void onSave(AJSONObject &data) override;

    virtual void reloadType();
    virtual void reloadData();
    virtual void reloadValues();
    void reloadAll();

    UI::SizeType getCountGroups(const AObject &sender) const override { return 3; }
    UI::SizeType getCountItems(const AObject &sender, UI::SizeType groupIndex) const override { return groupIndex == 0 ? 2 : 1; }
    SharedReference<UI::View> provideViewForGroup(const AObject &sender, UI::SizeType groupIndex) override;
    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType groupIndex, UI::SizeType itemIndex) override;

    bool shouldAddTouchGestureRecognizerToItem(UI::SizeType groupIndex, UI::SizeType itemIndex) const override { return true; }
    bool shouldReceiveInputFromItem(UI::SizeType groupIndex, UI::SizeType itemIndex) const override { return true; }
    void onItemSelected(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType groupIndex, UI::SizeType itemIndex) override {}
    void onItemTapped(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType groupIndex, UI::SizeType itemIndex) override {}

    virtual void onNameChanged(const String &name)
    {

    }

    virtual void onTypeChanged(const String &name)
    {
        reloadAll();
    }

    virtual void onPropertyChanged(const AVariant &variant)
    {

    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
