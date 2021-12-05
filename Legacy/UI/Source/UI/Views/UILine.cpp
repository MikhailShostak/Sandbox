#include "UILine.h"
#include "MetaObject.h"

namespace UI
{

AStaticRun(LineMetaObject)
{
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<Line>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const Line&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<Line&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<Line, SharedReference<Legacy::Graphics::Texture>>("Image", &Line::getImage, &Line::setImage, false);
    object.registerMetaProperty<Line, UIOffsets>("Border", &Line::getBorder, &Line::setBorder, false);
    manager.registerMetaObject("UI.Line", object);
}

}
