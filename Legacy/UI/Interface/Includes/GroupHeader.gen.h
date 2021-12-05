#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Overlay.gen.h"

#include "Foundation"
#include "ImageView.gen.h"
#include "FlexBox.gen.h"
#include "Label.gen.h"

//CLASSGEN END REGION
#include "UI/GestureRecognizers/UITouchGestureRecognizer.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GroupHeader : public UI::Overlay
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GroupHeader This;
    typedef UI::Overlay Super;
    typedef void Interfaces;
public:
    GroupHeader();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::ImageView> background;
    SharedReference<UI::FlexBox> content;
    SharedReference<UI::ImageView> expandButton;
    SharedReference<UI::Label> title;
    SharedReference<UI::ImageView> separator;
    void onHierarchyCreate();
//CLASSGEN END REGION
bool isExpanded = true;
void onLoad(ALoadEvent &event) override;
void addCustomButton(const SharedReference<Legacy::Graphics::Texture> &image, ADelegate<void(TapGestureEvent &event)> &&callback);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
