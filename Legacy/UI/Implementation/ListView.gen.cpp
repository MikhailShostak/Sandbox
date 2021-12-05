//CLASSGEN GENERATED REGION: Includes
#include "ListView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*

//CLASSGEN GENERATED REGION: ClassImplementation
ListView::ListView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ListView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Direction", toJSONValue(Direction));
}
void ListView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Direction", value);
    fromJSONValue(value, Direction);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
UI::Direction ListView::getDirection() const
{
    return this->Direction;
}
void ListView::setDirection(UI::Direction const &Direction)
{
    this->Direction = Direction;
}
void ListView::setDirection(UI::Direction &&Direction)
{
    this->Direction = std::move(Direction);
}
//CLASSGEN END REGION
*/
CLASSGEN_GENERATED_REGION_OBJECT
void ListView::serialize(AJSONObject &object) const
{
}
void ListView::deserialize(const AJSONObject &object)
{
    AJSONValue value;
}
CLASSGEN_END_REGION
//CLASSGEN GENERATED REGION: NamespaceEnd

void ListView::onHierarchyCreate()
{
    SharedReference<FlexBox> contentViewOverride = CreateShared<FlexBox>();
    contentViewOverride->setDirection(Direction::Vertical);
    contentViewOverride->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
    contentView = contentViewOverride;

    Super::onHierarchyCreate();
}

}
//CLASSGEN END REGION
