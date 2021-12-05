//CLASSGEN GENERATED REGION: Includes
#include "ObjectEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ObjectEditor::ObjectEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ObjectEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ObjectEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
String ObjectEditor::getName() const
{
    return this->Name;
}
void ObjectEditor::setName(String const &Name)
{
    this->Name = Name;
}
void ObjectEditor::setName(String &&Name)
{
    this->Name = std::move(Name);
}
LegacyClassGen::TypeInfo ObjectEditor::getType() const
{
    return this->Type;
}
void ObjectEditor::setType(LegacyClassGen::TypeInfo const &Type)
{
    this->Type = Type;
}
void ObjectEditor::setType(LegacyClassGen::TypeInfo &&Type)
{
    this->Type = std::move(Type);
}
LegacyClassGen::TypeInfo ObjectEditor::getBaseType() const
{
    return this->BaseType;
}
void ObjectEditor::setBaseType(LegacyClassGen::TypeInfo const &BaseType)
{
    this->BaseType = BaseType;
}
void ObjectEditor::setBaseType(LegacyClassGen::TypeInfo &&BaseType)
{
    this->BaseType = std::move(BaseType);
}
void ObjectEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ObjectEditor");
}
//CLASSGEN END REGION
void ObjectEditor::onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type)
{
    if (type)
    {
        readRecursively(type->getDefaultType(), this->Type);
    }

    data.read("Name", this->Name);
    String baseType;
    if(data.read("BaseType", baseType))
    {
        readRecursively(baseType, this->BaseType);
    }
    data.read("Values", this->propertiesData);
    if (AllowBindingEvents)
    {
        this->eventsView->bindings.clear();
        AJSONValue v;
        data.read("Bindings", v);
        fromJSONValue(v, this->eventsView->bindings);
    }

    reloadAll();
}

void ObjectEditor::onSave(AJSONObject &data)
{
    data.insert("Name", this->Name);
    data.insert("BaseType", writeRecursively(this->BaseType));
    data.insert("Values", propertiesTree->deserializeValue());
    if (AllowBindingEvents)
    {
        data.insert("Bindings", toJSONValue(this->eventsView->bindings));
    }
}

void ObjectEditor::reloadType()
{
    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(this->getObjectType().Name);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        typeData = typeIt->second;
    }
}

void ObjectEditor::reloadData()
{
    propertiesTree->setType(this->typeData, {});

    if (AllowBindingEvents)
    {
        if (this->typeData)
        {
            AJSONObject BindingContext;
            typeData->data.read("BindingContext", BindingContext);
            this->eventsView->events.clear();
            for(const auto &pair : BindingContext)
            {
                LegacyClassGen::EventInfo e;
                fromJSONValue(pair.second, e);
                e.Name = pair.first;
                this->eventsView->events.push_back(e);
            }
            //fromJSONValue(events, this->eventsView->events);
            this->eventsView->onBindingChanged = [this](const String &name){
                ALogMessage("", "Object binding \"%s.%s\" is changed", this->Name, name);
                onChanged();
            };
            this->eventsView->notifyUpdateAllItems();
        }
    }

    propertiesTree->onValueChanged = [this]() {
        ALogMessage("", "Object \"%s\" is changed", this->Name);
        onChanged();
    };

    notifyUpdateAllItems();
}

void ObjectEditor::reloadValues()
{
    propertiesTree->serializeValue(this->propertiesData);
}

void ObjectEditor::reloadAll()
{
    reloadType();
    reloadData();
    reloadValues();
}

SharedReference<UI::View> ObjectEditor::provideViewForGroup(const AObject &sender, UI::SizeType groupIndex)
{
    auto header = CreateShared<UI::GroupHeader>();
    header->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
    if (groupIndex == 0)
    {
        header->title->setText("Class Settings");
    }
    else if (groupIndex == 1)
    {
        header->title->setText("Default Properties");
    }
    else
    {
        header->title->setText("Bindings");
    }

    return header;
}

SharedReference<UI::View> ObjectEditor::provideViewForItem(const AObject &sender, UI::SizeType groupIndex, UI::SizeType itemIndex)
{
    if (groupIndex == 0)
    {
        switch (itemIndex)
        {
        case 0:
        {
           auto view = CreateShared<UI::TextField>();
            view->setPlaceholder("Name");
            view->setText(Name);
            view->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                Name = event.getText();
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    onNameChanged(Name);
                    return AError::getEmptyError();
                }, true);
            });
            return view;
        }
        case 1:
        {
            auto view = CreateShared<UI::TextField>();
            view->setPlaceholder("Type");
            view->setText(writeRecursively(BaseType));
            view->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                readRecursively(event.getText(), BaseType);
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    onTypeChanged(writeRecursively(BaseType));
                    return AError::getEmptyError();
                }, true);

            });
            return view;
        }
        }
    }
    else if (groupIndex == 1)
    {
        return propertiesTree;
    }

    return eventsView;
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
