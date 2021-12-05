#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"
#include "ClassGenLibrary"

#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class EnumerationEditor : public UI::Overlay, public LegacyClassGen::Editor, public UI::ItemAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EnumerationEditor This;
    typedef UI::Overlay Super;
    typedef std::tuple<LegacyClassGen::Editor, UI::ItemAdapter> Interfaces;
public:
    EnumerationEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    SharedReference<UI::ListView> listView = CreateShared<UI::ListView>();
    SharedReference<UI::Button> addButton = CreateShared<UI::Button>();
    Array<String> values;
public:
    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        addView(listView);
        listView->setSizePolicy(UI::SizePolicy::Expanded);
        addView(addButton);
        addButton->setBackgroundImage(PlusButtonSmall);
        addButton->setSize(Math::IntegerVector{ 0, 20 });
        addButton->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::Fixed);
        addData({ UIOffsets{ 0, 0, 20, 0 } });
        addData({ UIOffsets{}, { Core::Alignment::Center, Core::Alignment::End } });
        listView->setAdapter(this);

        addButton->eventChannel.registerDelegate([this](UI::TapGestureEvent &event) {
            values.push_back("NewValue");
            listView->notifyInsertItems(values.size() - 1);
        });

        data.read("Values", values);
        listView->notifyUpdateAllItems();
    }

    void onSave(AJSONObject &data) override
    {
        data.insert("Values", values);
    }

    virtual UI::SizeType getCountItems(const AObject &sender) const { return values.size(); }
    virtual SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType index)
    {
        SharedReference<UI::TextField> textField = CreateShared<UI::TextField>(values[index]);
        WeakReference<UI::TextField> weakTextField = textField;
        textField->eventChannel.registerDelegate([this, weakTextField](UI::TextEditFinishedEvent &event) {
            UI::SizeType index = listView->getIndexForItemView(*weakTextField.lock());
            values[index] = event.getText();
            return AError::getEmptyError();
        });

        auto menu = CreateShared<UI::MenuView>();
        menu->addAction(UI::MenuAction{ "Insert before", [this, weakTextField](UI::TapGestureEvent &event) {
            UI::SizeType index = listView->getIndexForItemView(*weakTextField.lock());
            UIApplication::getOperationDispatcher().addDelegate([this, index]() {
                values.insert(values.begin() + index, "NewValue");
                listView->notifyInsertItems(index);
                return AError::getEmptyError();
            }, true);
        } });
        menu->addAction(UI::MenuAction{ "Insert after", [this, weakTextField](UI::TapGestureEvent &event) {
            UI::SizeType index = listView->getIndexForItemView(*weakTextField.lock()) + 1;
            UIApplication::getOperationDispatcher().addDelegate([this, index]() {
                values.insert(values.begin() + index, "NewValue");
                listView->notifyInsertItems(index);
                return AError::getEmptyError();
            }, true);
        } });
        menu->addAction(UI::MenuAction{ "Remove", [this, weakTextField](UI::TapGestureEvent &event) {
            UI::SizeType index = listView->getIndexForItemView(*weakTextField.lock());
            UIApplication::getOperationDispatcher().addDelegate([this, index, weakTextField]() {
                weakTextField.lock()->getOwner()->getWindow()->removeFocus(*weakTextField.lock());
                values.erase(values.begin() + index);
                listView->notifyRemoveItems(index);
                return AError::getEmptyError();
            }, true);
        } });
        menu->addAction(UI::MenuAction{ "Clear", [this, weakTextField](UI::TapGestureEvent &event) {
            UI::SizeType index = listView->getIndexForItemView(*weakTextField.lock());
            UIApplication::getOperationDispatcher().addDelegate([this, index, weakTextField]() {
                weakTextField.lock()->getOwner()->getWindow()->removeFocus(*weakTextField.lock());
                values.clear();
                listView->notifyUpdateAllItems();
                return AError::getEmptyError();
            }, true);
        } });
        AttachMenuToView(textField, menu);

        return textField;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
