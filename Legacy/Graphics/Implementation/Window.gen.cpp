//CLASSGEN GENERATED REGION: Includes
#include "Window.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "MetaObjectSerializationHelper.h"
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Window::Window()
{
    UI::Color backgroundColor_0;
    backgroundColor_0.Red = 0.000000;
    backgroundColor_0.Green = 0.000000;
    backgroundColor_0.Blue = 0.000000;
    backgroundColor_0.Alpha = 0.000000;
    (*this).setBackgroundColor(backgroundColor_0);
    Math::IntegerRectangle geometry_5;
    Math::IntegerVector position_6;
    position_6.X = 0.000000;
    position_6.Y = 0.000000;
    position_6.Z = 0.000000;
    position_6.W = 0.000000;
    geometry_5.Position = position_6;
    Math::IntegerVector size_11;
    size_11.X = 0.000000;
    size_11.Y = 0.000000;
    size_11.Z = 0.000000;
    size_11.W = 0.000000;
    geometry_5.Size = size_11;
    (*this).setGeometry(geometry_5);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Window::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("BackgroundColor", toJSONValue(BackgroundColor));
    object.insert("Title", toJSONValue(Title));
    object.insert("Geometry", toJSONValue(Geometry));
}
void Window::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("BackgroundColor", value);
    fromJSONValue(value, BackgroundColor);
    value = AJSONValue();
    object.read("Title", value);
    fromJSONValue(value, Title);
    value = AJSONValue();
    object.read("Geometry", value);
    fromJSONValue(value, Geometry);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
UI::Color Window::getBackgroundColor() const
{
    return this->BackgroundColor;
}
void Window::setBackgroundColor(UI::Color const &BackgroundColor)
{
    this->BackgroundColor = BackgroundColor;
}
void Window::setBackgroundColor(UI::Color &&BackgroundColor)
{
    this->BackgroundColor = std::move(BackgroundColor);
}
String Window::getTitle() const
{
    return this->Title;
}
void Window::setTitle(String const &Title)
{
    this->Title = Title;
}
void Window::setTitle(String &&Title)
{
    this->Title = std::move(Title);
}
Math::IntegerRectangle Window::getGeometry() const
{
    return this->Geometry;
}
void Window::setGeometry(Math::IntegerRectangle const &Geometry)
{
    this->Geometry = Geometry;
}
void Window::setGeometry(Math::IntegerRectangle &&Geometry)
{
    this->Geometry = std::move(Geometry);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
