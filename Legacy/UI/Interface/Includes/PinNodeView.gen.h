#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "NamedNodeView.gen.h"

#include "Foundation"
#include "FlexBox.gen.h"
#include "View.gen.h"

//CLASSGEN END REGION
#include "Pin.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class PinNodeAdapter
{
public:
    virtual size_t getCountInputPins() const { return 0; }
    virtual SharedReference<View> getInputPin(size_t index) { return nullptr; }
    virtual size_t getCountOutputPins() const { return 0; }
    virtual SharedReference<View> getOutputPin(size_t index) { return nullptr; }
    virtual SharedReference<View> getContent() { return nullptr; }
};
//CLASSGEN GENERATED REGION: ClassHeader
class PinNodeView : public UI::NamedNodeView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PinNodeView This;
    typedef UI::NamedNodeView Super;
    typedef void Interfaces;
public:
    PinNodeView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::FlexBox> inputPins;
    SharedReference<UI::View> nodeContent;
    SharedReference<UI::FlexBox> outputPins;
    void onHierarchyCreate();
//CLASSGEN END REGION

    PinNodeAdapter *adapter = nullptr;

    using Pin = UI::Pin;

    void updateData()
    {
        size_t s1 = adapter->getCountInputPins();
        for (size_t i = 0; i < s1; ++i)
        {
            inputPins->addView(adapter->getInputPin(i));
        }
        inputPins->setData(Array<FlexBoxData>(s1));

        size_t s2 = adapter->getCountOutputPins();
        for (size_t i = 0; i < s2; ++i)
        {
            outputPins->addView(adapter->getOutputPin(i));
        }
        outputPins->setData(Array<FlexBoxData>(s2));
    }

    SharedReference<View> findSource(const Connection &connection) const override
    {
        const auto &pins = connection.Reversed ? inputPins : outputPins;
        for (const auto &pin : pins->getViews())
        {
            if (StaticCast<Pin>(pin)->label->getText() == connection.Source)
            {
                return pin;
            }
        }

        return nullptr;
    }

    SharedReference<View> findTarget(const Connection &connection) const override
    {
        String target;
        APath path = connection.Target;
        if (path.size() == 2)
        {
            target = path.baseName();
        }
        else if (path.size() != 1)
        {
            return nullptr;
        }

        const auto &pins = connection.Reversed ? outputPins : inputPins;
        for (const auto &pin : pins->getViews())
        {
            if (StaticCast<Pin>(pin)->label->getText() == target)
            {
                return pin;
            }
        }

        return nullptr;
    }

    SharedReference<UI::Line> connect(const SharedReference<UI::NodeView> &sourceNode, const SharedReference<UI::NodeView> &targetNode, const UI::Connection &connection) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
