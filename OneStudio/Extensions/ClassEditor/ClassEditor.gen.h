#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"
#include "ClassGenLibraryDebug"

#include "Foundation"
#include "ClassGenExtensions"
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include <Experimental>
#include <ClassGenLibrary>

#include "LogicEditor.gen.h"
#include "PropertyDetailsView.gen.h"
#include "EventDetailsView.gen.h"
#include "FunctionDetailsView.gen.h"
#include "ObjectEditor.gen.h"

namespace Data
{
    template<typename ContainerType, typename ValueType>
    inline void Serialize(ContainerType &container, const String &key, const ValueType &value)
    {
        container.insert(key, toJSONValue(value), true);
    }

    template<typename ContainerType, typename ValueType>
    inline void Deserialize(const ContainerType &container, const String &key, ValueType &value)
    {
        AJSONValue json;
        container.read(key, json);
        value = ValueType(); //TODO: move inside to fromJSONValue
        fromJSONValue(json, value);
    }
}

//#include "ClassSuggestionsComponent.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ClassEditor : public UI::FlexBox, public LegacyClassGen::Editor, public UI::GroupAdapter
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ClassEditor This;
    typedef UI::FlexBox Super;
    typedef std::tuple<LegacyClassGen::Editor, UI::GroupAdapter> Interfaces;
public:
    ClassEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<LegacyClassGen::LogicEditor> logicEditor;
        SharedReference<UI::FlexBox> contentView;
        SharedReference<UI::GroupPanel> classDetailsPanel;
            SharedReference<UI::GroupView> classDetails;
        SharedReference<UI::GroupPanel> detailsPanel;
            SharedReference<UI::PageView> details;
            SharedReference<LegacyClassGen::PropertyDetailsView> propertyDetails;
            SharedReference<LegacyClassGen::EventDetailsView> eventDetails;
            SharedReference<LegacyClassGen::FunctionDetailsView> functionDetails;
        SharedReference<UI::GroupPanel> dataPanel;
            SharedReference<LegacyClassGen::ObjectEditor> defaultValuesEditor;
    void onHierarchyCreate();
//CLASSGEN END REGION
    String namespaceName;
    Array<String> interfaces;
    Array<String> templateTypes;
    Array<LegacyClassGen::PropertyInfo> properties;
    Array<LegacyClassGen::FunctionInfo> functions;
    Array<LegacyClassGen::EventInfo> events;
public:

    void onLoad(ALoadEvent &event)
    {
        if (isLoaded())
        {
            return;
        }

        classDetailsPanel->headerLabel->setText("Class Details");
        dataPanel->headerLabel->setText("Data");
        contentView->setSpacing(8);

        functionDetails->setAffectsParentLayout(true);
        eventDetails->setAffectsParentLayout(true);
        propertyDetails->setAffectsParentLayout(true);
        defaultValuesEditor->setAffectsParentLayout(true);

        //HACK: setName of class gen objects conflicts with setName of AObject.
        //onHierarchyCreate sets a bad name for object, so, let's clear it...
        defaultValuesEditor->setName("");

        Super::onLoad(event);

        defaultValuesEditor->onChanged = [this]() {
            ALogMessage("", "Class is changed (Default values)");
            onChanged();
        };

        propertyDetails->onNameChanged = [this](const String &oldName, const String &newName) {
            if (std::find_if(properties.begin(), properties.end(), [&](const auto &item) {
                return item.Name == newName;
            }) != properties.end())
            {
                return false; //Already exists with this name
            }

            LegacyClassGen::PropertyInfo &p = defaultValuesEditor->propertiesTree->overrideProperty(propertyDetails->getData(), oldName);
            p.Name = newName;

            auto it = std::find_if(properties.begin(), properties.end(), [&](const auto &item) {
                return item.Name == oldName;
            });

            it->Name = newName;

            UIApplication::getOperationDispatcher().addDelegate([this, it]()
            {
                classDetails->notifyUpdateItemsInGroup(3, std::distance(properties.begin(), it));
                return AError();
            }, true);

            return true;
        };
        propertyDetails->onTypeChanged = [this](const String &type, const Array<String> &parameters) {
            LegacyClassGen::PropertyInfo &p = defaultValuesEditor->propertiesTree->overrideProperty(propertyDetails->getData(), propertyDetails->getData().Name);
            p.Type = type;
            p.Parameters = parameters;
        };
        propertyDetails->onChanged = [this](const LegacyClassGen::PropertyInfo &data) {
            auto it = std::find_if(properties.begin(), properties.end(), [&](const auto &item) {
                return item.Name == data.Name;
            });
            *it = data;

            UIApplication::getOperationDispatcher().addDelegate([this]() {
                defaultValuesEditor->reloadAll();
                ALogMessage("", "Class is changed (Properties)");
                this->onChanged();
                return AError();
            }, true);
        };

        functionDetails->onNameChanged = [this](const String &oldIdentifier, const String &newIdentifier) {
            if (std::find_if(functions.begin(), functions.end(), [&](const auto &item) {
                return item.Identifier == newIdentifier;
            }) != functions.end())
            {
                return false; //Already exists with this name
            }

            auto it = std::find_if(functions.begin(), functions.end(), [&](const auto &item) {
                return item.Identifier == oldIdentifier;
            });

            it->Identifier = newIdentifier;

            UIApplication::getOperationDispatcher().addDelegate([this, it]()
            {
                classDetails->notifyUpdateItemsInGroup(4, std::distance(functions.begin(), it));
                return AError();
            }, true);

            return true;
        };
        functionDetails->onChanged = [this](const LegacyClassGen::FunctionInfo &data) {
            auto it = std::find_if(functions.begin(), functions.end(), [&](const auto &item) {
                return item.Identifier == data.Identifier;
            });
            *it = data;
            this->onChanged();
        };

        eventDetails->onNameChanged = [this](const String &oldName, const String &newName) {
            if (std::find_if(events.begin(), events.end(), [&](const auto &item) {
                return item.Name == newName;
            }) != events.end())
            {
                return false; //Already exists with this name
            }

            auto it = std::find_if(events.begin(), events.end(), [&](const auto &item) {
                return item.Name == oldName;
            });

            it->Name = newName;

            UIApplication::getOperationDispatcher().addDelegate([this, it]() {
                classDetails->notifyUpdateItemsInGroup(5, std::distance(events.begin(), it));
                return AError();
            }, true);

            return true;
        };

        eventDetails->onChanged = [this](const LegacyClassGen::EventInfo &data) {
            auto it = std::find_if(events.begin(), events.end(), [&](const auto &item) {
                return item.Name == data.Name;
            });

            if (it == events.end())
            {
                return;
            }

            *it = data;
            this->onChanged();
        };

        classDetails->setProxyAdapter(this);
    }

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        data.read("Namespace", namespaceName);
        data.read("Interfaces", interfaces);
        data.read("TemplateTypes", templateTypes);

        Data::Deserialize(data, "Properties", properties);
        Data::Deserialize(data, "Functions", functions);
        
        AJSONObject BindingContext;
        Data::Deserialize(data, "BindingContext", BindingContext);
        events.clear();
        for(const auto &pair : BindingContext)
        {
            LegacyClassGen::EventInfo e;
            fromJSONValue(pair.second, e);
            e.Name = pair.first;
            events.push_back(e);
        }

        defaultValuesEditor->onLoad(data, type);

        classDetails->notifyUpdateAllItems();
    }

    void onSave(AJSONObject &data) override
    {
        defaultValuesEditor->onSave(data);

        data.insert("Namespace", namespaceName, true);
        data.insert("Interfaces", interfaces, true);
        data.insert("TemplateTypes", templateTypes, true);
        data.insert("Properties", toJSONValue(this->properties), true);
        data.insert("Functions", toJSONValue(this->functions), true);
        
        AJSONObject BindingContext;
        for(const LegacyClassGen::EventInfo &e : events)
        {
            BindingContext.insert(e.Name, toJSONValue(e), true);
        }
        data.insert("BindingContext", BindingContext);
    }

protected:

    UI::SizeType getCountGroups(const AObject &sender) const override { return 6; }
    UI::SizeType getCountItems(const AObject &sender, UI::SizeType groupIndex) const override
    {
        switch (groupIndex)
        {
        case 0:
            return 1;
        case 1:
            return interfaces.size();
        case 2:
            return templateTypes.size();
        case 3:
            return properties.size();
        case 4:
            return functions.size();
        case 5:
            return events.size();
        }
        return 0;
    }

    SharedReference<View> provideViewForGroup(const AObject &sender, UI::SizeType groupIndex) override
    {
        SharedReference<View> view;

        switch (groupIndex)
        {
        case 0:
        {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Namespace");
            view = header;
            break;
        }
        case 1:
        {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Interfaces");
            header->addCustomButton(::PlusButtonSmall, [this](UI::TapGestureEvent &event) {
                interfaces.push_back(Str::GetNextAvailableName("NewInterface", interfaces, [](auto &&item, auto &&name) { return item != name; }));
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    classDetails->notifyInsertItemsInGroup(1, interfaces.size() - 1);
                    ALogMessage("", "Class is changed (Interfaces)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            view = header;
            break;
        }
        case 2:
        {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Template Types");
            header->addCustomButton(::PlusButtonSmall, [this](UI::TapGestureEvent &event) {
                templateTypes.push_back(Str::GetNextAvailableName("NewType", templateTypes, [](auto &&item, auto &&name) { return item != name; }));
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    classDetails->notifyInsertItemsInGroup(2, templateTypes.size() - 1);
                    ALogMessage("", "Class is changed (TemplateTypes)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            view = header;
            break;
        }
        case 3:
        {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Properties");
            header->addCustomButton(::PlusButtonSmall, [this](UI::TapGestureEvent &event) {
                LegacyClassGen::PropertyInfo p;
                p.Name = Str::GetNextAvailableName("NewProperty", properties, [](auto &&item, auto &&name) { return item.Name != name; });
                p.Type = "Boolean";
                properties.push_back(p);
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    classDetails->notifyInsertItemsInGroup(3, properties.size() - 1);
                    ALogMessage("", "Class is changed (Properties)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            view = header;
            break;
        }
        case 4:
        {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Functions");
            header->addCustomButton(::PlusButtonSmall, [this](UI::TapGestureEvent &event) {
                LegacyClassGen::FunctionInfo f;
                f.Identifier = Str::GetNextAvailableName("NewFunction", functions, [](auto &&item, auto &&name) { return item.Identifier != name; });
                f.Callable = true;
                functions.push_back(f);
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    classDetails->notifyInsertItemsInGroup(4, functions.size() - 1);
                    ALogMessage("", "Class is changed (Functions)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            view = header;
			break;
        }
        case 5:
        {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Events");
            header->addCustomButton(::PlusButtonSmall, [this](UI::TapGestureEvent &event) {
                LegacyClassGen::EventInfo eventInfo;
                eventInfo.Name = Str::GetNextAvailableName("NewEvent", events, [](auto &&item, auto &&name) { return item.Name != name; });
                events.push_back(eventInfo);
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    classDetails->notifyInsertItemsInGroup(5, events.size() - 1);
                    ALogMessage("", "Class is changed (Events)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            view = header;
            break;
        }
        }

        if (view)
        {
            view->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        }

        return view;
    }

    SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType groupIndex, UI::SizeType itemIndex) override
    {
        switch (groupIndex)
        {
        case 0:
        {
            auto textField = CreateShared<UI::TextField>();
            textField->setText(namespaceName);
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                namespaceName = event.getText();
                ALogMessage("", "Class is changed (Namespace - %s)", namespaceName);
                this->onChanged();
            });
            return textField;
        }
        case 1:
        {
            auto textField = CreateShared<UI::TextField>();
            textField->setText(interfaces[itemIndex]);
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                size_t index = classDetails->getGroupItemIndexForItemView(event.getView());
                interfaces[classDetails->getGroupItemIndexForItemView(event.getView())] = event.getText();
                ALogMessage("", "Class is changed (Interface - %s)", event.getText());
                this->onChanged();
            });
            return textField;
        }
        case 2:
        {
            auto textField = CreateShared<UI::TextField>();
            textField->setText(templateTypes[itemIndex]);
            textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                size_t index = classDetails->getGroupItemIndexForItemView(event.getView());
                templateTypes[classDetails->getGroupItemIndexForItemView(event.getView())] = event.getText();
                ALogMessage("", "Class is changed (Event - %s)", event.getText());
                this->onChanged();
            });
            return textField;
        }
        case 3:
        {
            auto label = CreateShared<UI::DefaultTextItemView>();
            UI::DefaultTextItemView *labelPtr = label.get();
            label->setText(properties[itemIndex].Name);
            label->addGestureRecognizer(CreateShared<UI::TouchGestureRecognizer>());
            label->eventChannel.registerDelegate([this, labelPtr](UI::TapGestureEvent &event) {
                event.getView().getOwner()->getWindow()->removeFocus();
                size_t index = classDetails->getGroupItemIndexForItemView(event.getView());
                detailsPanel->headerLabel->setText("Property Details - " + labelPtr->getText());
                detailsPanel->show();
                details->setCurrentView(*propertyDetails);
                propertyDetails->setData(properties[index]);
                return AError();
            });

            /*MenuView *menu = new MenuView();
            menu->addAction({ "Insert before", [](TapGestureEvent &event) {

            } });
            menu->addAction({ "Insert after", [](TapGestureEvent &event) {

            } });
            menu->addAction({ "Remove", [](TapGestureEvent &event) {

            } });
            AttachMenuToView(label, menu);*/

            return label;
        }
        case 4:
        {
            auto label = CreateShared<UI::DefaultTextItemView>();
            UI::DefaultTextItemView * labelPtr = label.get();
            label->setText(functions[itemIndex].Identifier);
            label->addGestureRecognizer(CreateShared<UI::TouchGestureRecognizer>());
            label->eventChannel.registerDelegate([this, labelPtr](UI::TapGestureEvent &event) {
                event.getView().getOwner()->getWindow()->removeFocus();
                size_t index = classDetails->getGroupItemIndexForItemView(event.getView());
                detailsPanel->headerLabel->setText("Function Details - " + labelPtr->getText());
                detailsPanel->show();
                details->setCurrentView(*functionDetails);
                functionDetails->setFunctionInfo(functions[index]);
                return AError();
            });
            return label;
        }
        case 5:
        {
            auto label = CreateShared<UI::DefaultTextItemView>();
            UI::DefaultTextItemView *labelPtr = label.get();
            label->setText(events[itemIndex].Name);
            label->addGestureRecognizer(CreateShared<UI::TouchGestureRecognizer>());
            label->eventChannel.registerDelegate([this, labelPtr](UI::TapGestureEvent &event) {
                event.getView().getOwner()->getWindow()->removeFocus();
                size_t index = classDetails->getGroupItemIndexForItemView(event.getView());
                detailsPanel->headerLabel->setText("Event Details - " + labelPtr->getText());
                detailsPanel->show();
                details->setCurrentView(*eventDetails);
                eventDetails->setEventInfo(events[index]);
                return AError();
            });
            return label;
        }
        }

        return nullptr;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
