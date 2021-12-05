#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Panel.gen.h"

#include "Foundation"

//CLASSGEN END REGION
#include "UI/Views/UILine.h"
#include "Includes/Connection.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class NodeView : public UI::Panel
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef NodeView This;
    typedef UI::Panel Super;
    typedef void Interfaces;
public:
    NodeView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
public:
    int32_t gridSize = 20.0f;
    Math::IntegerVector minimalSize = { gridSize, gridSize };

    struct ConnectionInfo
    {
        SharedReference<NodeView> targetNode;
        SharedReference<UI::Line> view;
        Connection data;
    };

    Array<ConnectionInfo> connections;

    String identifier;

    AColor baseColor = AColor::fromHex(0xDDAAAAAA);
    AColor highlightedColor = AColor::fromHex(0xDDFFFFFF);

    virtual void setSelected(bool selected)
    {
        StaticCast<UI::BorderImageView>(background)->setColor(selected ? highlightedColor : baseColor);
    }

    void onLoad(ALoadEvent & event)
    {
        Super::onLoad(event);

        setSelected(false);
    }

    virtual Math::IntegerVector getContentSize() const override
    {
        Math::IntegerVector v = Super::getContentSize();
        return Math::getMax2(v + (Math::IntegerVector{ gridSize, gridSize } - (v - Math::snapToGrid2(v, gridSize))), minimalSize);
    }

    virtual String getIdentifier() const
    {
        return identifier;
    }

    virtual SharedReference<View> findSource(const Connection &connection) const
    {
        return nullptr;
    }

    virtual SharedReference<View> findTarget(const Connection &connection) const
    {
        return nullptr;
    }

    virtual SharedReference<UI::Line> createConnection()
    {
        return SharedReference<UI::Line>(Create<UI::Line>());
    }

    virtual SharedReference<UI::Line> connect(const SharedReference<UI::NodeView> &sourceNode, const SharedReference<UI::NodeView> &targetNode, const Connection &connection)
    {
        SharedReference<UI::Line> view = createConnection();
        connections.emplace_back(ConnectionInfo{
            targetNode,
            view,
            connection,
        });

        return view;
    }

    virtual void disconnect(const Connection &connection)
    {
        connections.erase(ranges::find_if(connections, [&](const auto &c) { return c.data.Source == connection.Source && c.data.Target == connection.Target; }));
    }

    /*virtual void disconnectFrom(const String &source)
    {
        connections.erase(std::find_if(connections.begin(), connections.end(), [&](const auto &c) { return c.Source == source; }));
    }

    virtual void disconnectTo(const String &target)
    {
        connections.erase(std::find_if(connections.begin(), connections.end(), [&](const auto &c) { return c.Target == target; }));
    }*/
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
