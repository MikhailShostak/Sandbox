#include "Includes/ItemView.gen.h"//TODO:temp include
#include "MetaObject.h"//TODO:temp include

namespace UI
{

/*AStaticRun(ItemViewMetaObject)
{
CLASSGEN_GENERATED_REGION_META_OBJECT
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<ItemView>();
    object.serialize = [](const AObject &object, AJSONObject &data){ static_cast<const ItemView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object){ static_cast<ItemView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<ItemView, SharedReference<Graphics::Texture>>("Image", &ItemView::getImage, &ItemView::setImage, false);
    manager.registerMetaObject("UI.ItemView", object);
CLASSGEN_END_REGION
}
CLASSGEN_GENERATED_REGION_OBJECT
void ItemView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ItemView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
SharedReference<Graphics::Texture> ItemView::getImage() const
{
    return this->image;
}
void ItemView::setImage(SharedReference<Graphics::Texture> const &image)
{
    this->image = image;
}
CLASSGEN_END_REGION
*/
}
