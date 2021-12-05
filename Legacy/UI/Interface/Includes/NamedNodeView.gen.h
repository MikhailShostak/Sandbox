#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "NodeView.gen.h"

#include "Foundation"
#include "BorderImageView.gen.h"
#include "Label.gen.h"
#include "View.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class NamedNodeView : public UI::NodeView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef NamedNodeView This;
    typedef UI::NodeView Super;
    typedef void Interfaces;
public:
    NamedNodeView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::BorderImageView> headerBackground;
    SharedReference<UI::Label> title;
    SharedReference<UI::View> content;
    void onHierarchyCreate();
//CLASSGEN END REGION
public:
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        headerBackground->setImage(Legacy::Graphics::Texture::getWhiteTexture());
        headerBackground->setColor(AColor::BlackColor() * 0.2f);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
