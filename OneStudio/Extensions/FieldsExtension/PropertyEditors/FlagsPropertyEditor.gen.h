#pragma once

//CLASSGEN GENERATED REGION: Includes
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
class FlagsPropertyEditor : public UI::ListView, public FieldEditor
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FlagsPropertyEditor This;
    typedef UI::ListView Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    FlagsPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    Array<String> flags;
    Array<SharedReference<UI::Switch>> views;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        setAdapter(this);
    }

    void setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo) override
    {
        type->data.read("Values", flags);
        for (const String &flag : flags)
        {
            SharedReference<UI::Switch> view = CreateShared<UI::Switch>();
            view->setName(type->getDefaultType(true) + "_" + flag + "_ValueView");
            views.push_back(view);

            view->eventChannel.registerDelegate([this](UI::UserSwitchEvent &event) {
                notifyValueChange();
            });
        }
        notifyUpdateAllItems();
    }

    void clearFlags()
    {
        for (const auto &view : views)
        {
            view->setOn(false);
        }
    }

    void onSerialize(const AJSONValue &value) override
    {
        clearFlags();

        Array<String> checkedFlags = Str::Split(value.toString(), "|");
        for (size_t i = 0; i < flags.size(); ++i)
        {
            views[i]->setOn(ArrayUtils::Contains(checkedFlags, flags[i]));
        }
    }

    AJSONValue onDeserialize() override
    {
        Array<String> checkedFlags;
        for (size_t i = 0; i < views.size(); ++i)
        {
            if (views[i]->isOn())
            {
                checkedFlags.push_back(flags[i]);
            }
        }

        return Str::Join(checkedFlags, "|");
    }

    virtual UI::SizeType getCountItems(const AObject &sender) const { return views.size(); }
    virtual SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index)
    {
        SharedReference<UI::FlexBox> flexBox = CreateShared<UI::FlexBox>();
        flexBox->setSizePolicy(UI::SizePolicy::ContentWrapped);
        flexBox->addView(views[index]);
        flexBox->addData({});

        SharedReference<UI::Label> label = CreateShared<UI::Label>();
        label->setText(flags[index]);
        flexBox->addView(label);
        flexBox->addData({});

        return flexBox;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
