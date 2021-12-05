#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//#include "ClassSuggestionsComponent.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class PropertyDetailsView : public UI::ListView, public UI::ItemAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PropertyDetailsView This;
    typedef UI::ListView Super;
    typedef std::tuple<UI::ItemAdapter> Interfaces;
public:
    PropertyDetailsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    LegacyClassGen::PropertyInfo data;

    SharedReference<LegacyClassGen::BaseCGType> typeData;

    Array<APair<String, SharedReference<UI::View>>> properties = {
        { "Name", CreateShared<UI::TextField>() },
        { "Template", CreateShared<UI::TextField>() },
        { "Type", CreateShared<UI::TextField>() },
        { "Visibility", CreateShared<UI::DropDownList>() },
        { "PreCallbacks", CreateShared<UI::TextField>() },
        { "PostCallbacks", CreateShared<UI::TextField>() },
        { "Attributes", CreateShared<UI::ListView>() },
        //{ "Mutable", Create<Switch>() },
    };

    //UI::ClassSuggestionsComponent typesSuggestionsComponent;
    //UI::ClassSuggestionsComponent templatesSuggestionsComponent;
public:

    ADelegate<bool(const String &oldName, const String &newName)> onNameChanged;
    ADelegate<void(const String &type, const Array<String> &parameters)> onTypeChanged;
    ADelegate<void(const LegacyClassGen::PropertyInfo &data)> onChanged;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        //templatesSuggestionsComponent.findTemplates = true;
        setAdapter(this);
    }

    const LegacyClassGen::PropertyInfo &getData() const
    {
        return data;
    }

    void setData(const LegacyClassGen::PropertyInfo &data)
    {
        this->data = data;

        updateTypeData();

        notifyUpdateAllItems();
    }

    void updateTypeData()
    {
        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(data.Type);
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            typeData = typeIt->second;
        }
    }

    void updateType(const String &type, const Array<String> &parameters)
    {
        data.Type = type;
        data.Parameters = parameters;

        updateTypeData();

        if (onTypeChanged)
        {
            onTypeChanged(data.Type, data.Parameters);
        }
        if (onChanged)
        {
            onChanged(data);
        }
    }

    virtual UI::SizeType getCountItems(const AObject &sender) const { return properties.size(); }
    virtual SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType index)
    {
        SharedReference<UI::Overlay> overlay = CreateShared<UI::Overlay>();
        auto label = CreateShared<UI::Label>();
        label->setText(properties[index].first);
        label->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::Expanded);
        overlay->addView(label);

        SharedReference<UI::View> view;
        switch (index)
        {
        case 0: //Name
        {
            SharedReference<UI::TextField> textField = CreateShared<UI::TextField>();
            textField->setText(data.Name);
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                String oldName = data.Name;
                String newName = event.getText();
                if (onNameChanged)
                {
                    if (onNameChanged(oldName, newName))
                    {
                        data.Name = newName;
                        if (onChanged)
                        {
                            onChanged(data);
                            return;
                        }
                    }
                }

                static_cast<UI::TextField &>(event.getView()).setText(oldName);
            });
            view = textField;
            break;
        }
        case 1: //Template
        {
            SharedReference<UI::TextField> textField = CreateShared<UI::TextField>();
            textField->setPlaceholder("Value");
            if (!data.Parameters.empty())
            {
                textField->setText(Str::Join(data.Parameters, ";"));
            }
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                if (!event.getText().empty())
                {
                    updateType(data.Type, Str::Split(event.getText(), String(";")));
                }
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    notifyUpdateItems(2);
                    return AError();
                }, true);
            });

            //templatesSuggestionsComponent.addView(*textField);

            /*SharedReference<DropDownList> list = Create<DropDownList>();

            if (EnumInfo enumInfo = MetaObjectInformation::getInstance().findEnum("ClassGen.PropertyValueType"))
            {
                list->setElements(enumInfo.values);
                list->setCurrentIndex(data.ValueType);
            }

            list->eventChannel.registerDelegate([this](CurrentIndexChangedEvent &event) {
                data.ValueType = LegacyClassGen::PropertyValueType(LegacyClassGen::PropertyValueType::Enum(event.getValue()));
                if (onTypeChanged)
                {
                    onTypeChanged(data.Type, data.ValueType);
                }
                if (onChanged)
                {
                    onChanged(data);
                }
            });*/
            view = textField;
            break;
        }
        case 2: //Type
        {
            if (typeData)
            {
                Array<String> templateTypes;
                if (typeData->data.read("TemplateTypes", templateTypes))
                {
                    data.Parameters.resize(templateTypes.size());

                    label->setText("Parameters");
                    SharedReference<UI::Overlay> templateTypesOverlay = CreateShared<UI::Overlay>();
                    size_t i = 0;
                    for (const String &templateType : templateTypes)
                    {
                        SharedReference<UI::Label> parameterName = CreateShared<UI::Label>();
                        parameterName->setText(templateType);
                        templateTypesOverlay->addView(parameterName);
                        auto layoutData = templateTypesOverlay->getData();
                        layoutData.push_back(UI::OverlayData{ UIOffsets{ 40 * int32_t(i) } });

                        SharedReference<UI::TextField> parameterTextField = CreateShared<UI::TextField>();
                        parameterTextField->setText(data.Parameters[i]);
                        parameterTextField->eventChannel.registerDelegate([this, i](UI::TextEditFinishedEvent &event) {
                            data.Parameters[i] = event.getText();
                            updateType(data.Type, data.Parameters);
                        });
                        templateTypesOverlay->addView(parameterTextField);
                        layoutData.push_back(UI::OverlayData{ UIOffsets{ 40 * int32_t(i) + 20 } });
                        templateTypesOverlay->setData(layoutData);

                        ++i;
                    }
                    view = templateTypesOverlay;
                    break;
                }
            }

            SharedReference<UI::TextField> textField = CreateShared<UI::TextField>();
            textField->setText(data.Type);
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                updateType(event.getText(), {});
            });
            view = textField;
            break;
        }
        case 3: //Visibility
        {
            SharedReference<UI::DropDownList> list = CreateShared<UI::DropDownList>();

            if (EnumInfo enumInfo = MetaObjectInformation::getInstance().findEnum("ClassGen.VisibilityType"))
            {
                list->setElements(enumInfo.values);
                list->setCurrentIndex(data.Visibility);
            }

            list->eventChannel.registerDelegate([this](UI::CurrentIndexChangedEvent &event) {
                data.Visibility = LegacyClassGen::VisibilityType(LegacyClassGen::VisibilityType::Enum(event.getValue()));
                if (onChanged)
                {
                    onChanged(data);
                }
            });
            view = list;
            break;
        }
        case 4: //PreCallbacks
        {
            SharedReference<UI::TextField> textField = CreateShared<UI::TextField>();
            textField->setText(Str::Join(data.PreCallbacks, ";"));
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                data.PreCallbacks = Str::Split(event.getText(), ";");
                if (onChanged)
                {
                    onChanged(data);
                }
            });
            view = textField;
            break;
        }
        case 5: //PostCallbacks
        {
            SharedReference<UI::TextField> textField = CreateShared<UI::TextField>();
            textField->setText(Str::Join(data.PostCallbacks, ";"));
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                data.PostCallbacks = Str::Split(event.getText(), ";");
                if (onChanged)
                {
                    onChanged(data);
                }
            });
            view = textField;
            break;
        }
        case 6: //Attributes
        {
            LegacyClassGen::TypeInfo info;
            info.Name = "ClassGen.PropertyAttributes";
            auto it = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(info.Name);
            if (it != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                SharedReference<FieldEditor> editor = LegacyClassGen::Context::getInstance().createFieldEditor(info, it->second);
                auto editorPtr = editor.get();
                editor->onValueChanged = [this, editorPtr]() {
                    fromJSONValue(editorPtr->deserializeValue(), data.Attributes);
                    if (onChanged)
                    {
                        onChanged(data);
                    }
                };
                editor->serializeValue(toJSONValue(data.Attributes));
                view = DynamicCast<UI::View>(editor);
            }
            else
            {
                view = CreateShared<UI::Label>("Not Implemented");
            }
            /*SharedReference<DropDownList> list = Create<DropDownList>();

            if (EnumInfo enumInfo = MetaObjectInformation::getInstance().findEnum("ClassGen.PropertyAttributes"))
            {
                list->setElements(enumInfo.values);
                list->setCurrentIndex(data.Attributes);
            }

            list->eventChannel.registerDelegate([this](CurrentIndexChangedEvent &event) {
                data.Attributes = LegacyClassGen::PropertyAttributes(LegacyClassGen::PropertyAttributes::Enum(event.getValue()));
                if (onChanged)
                {
                    onChanged(data);
                }
            });*/
            break;
        }
        default:
            view = CreateShared<UI::Label>("Not Implemented");
        }

        view->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        overlay->addView(view);

        auto layoutData = overlay->getData();
        layoutData.push_back(UI::OverlayData{ UIOffsets{ 0, 200, 0, 0 }, { Core::Alignment::Start, Core::Alignment::Start } });
        layoutData.push_back(UI::OverlayData{ UIOffsets{ 0, 0, 0, 100 }, { Core::Alignment::Start, Core::Alignment::Start } });
        overlay->setData(layoutData);
        overlay->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);


        return overlay;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
