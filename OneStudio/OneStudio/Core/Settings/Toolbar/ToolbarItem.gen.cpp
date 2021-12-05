//CLASSGEN GENERATED REGION: Includes
#include "ToolbarItem.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ToolbarItem::ToolbarItem()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ToolbarItem::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ToolbarItem::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Text ToolbarItem::getIdentifier() const
{
    return this->Identifier;
}
void ToolbarItem::setIdentifier(Text const &Identifier)
{
    this->Identifier = Identifier;
}
void ToolbarItem::setIdentifier(Text &&Identifier)
{
    this->Identifier = std::move(Identifier);
}
SharedReference<UI::View> ToolbarItem::getView() const
{
    return this->View;
}
void ToolbarItem::setView(SharedReference<UI::View> const &View)
{
    this->View = View;
}
void ToolbarItem::setView(SharedReference<UI::View> &&View)
{
    this->View = std::move(View);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
