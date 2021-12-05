#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Color.gen.h"
#include "Foundation"

//CLASSGEN END REGION
#include "ADelegate.h"
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Window : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Window This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    ADelegate<void()> OnVisibilityChanged;
    ADelegate<void()> OnClosed;
protected:
    UI::Color BackgroundColor;
String Title;
Math::IntegerRectangle Geometry;
public:
    Window();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    UI::Color getBackgroundColor() const;
    void setBackgroundColor(UI::Color const &BackgroundColor);
    void setBackgroundColor(UI::Color &&BackgroundColor);
    String getTitle() const;
    void setTitle(String const &Title);
    void setTitle(String &&Title);
    Math::IntegerRectangle getGeometry() const;
    void setGeometry(Math::IntegerRectangle const &Geometry);
    void setGeometry(Math::IntegerRectangle &&Geometry);
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
