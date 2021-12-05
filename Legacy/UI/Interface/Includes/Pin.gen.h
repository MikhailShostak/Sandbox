#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "FlexBox.gen.h"
#include "PinType.gen.h"
#include "Math"

#include "Foundation"
#include "ImageView.gen.h"
#include "Label.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Pin : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Pin This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
protected:
    UI::PinType Type;
Boolean ConnectionSource;
public:
    Pin();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    UI::PinType getType() const;
    void setType(UI::PinType const &Type);
    void setType(UI::PinType &&Type);
    Boolean getConnectionSource() const;
    void setConnectionSource(Boolean const &ConnectionSource);
    void setConnectionSource(Boolean &&ConnectionSource);
    SharedReference<UI::ImageView> socket;
    SharedReference<UI::Label> label;
    void onHierarchyCreate();
//CLASSGEN END REGION
    String getIdentifier() const;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
