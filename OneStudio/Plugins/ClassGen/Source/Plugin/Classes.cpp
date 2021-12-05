#include <Experimental>

AStaticRun(Classes)
{

MetaObjectManager &manager = MetaObjectManager::getInstance();
{
    {
        MetaObject & object = manager.getMetaObject<UI::Overlay>();
        object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::Overlay&>(object).serialize(data); };
        object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::Overlay&>(object).deserialize(data); };
        object.baseObject = &manager.getMetaObject<UI::View>();
        manager.registerMetaObject("UI.Overlay", object);
    }

    {
        MetaObject & object = manager.getMetaObject<UI::FlexBox>();
        object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::FlexBox&>(object).serialize(data); };
        object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::FlexBox&>(object).deserialize(data); };
        object.baseObject = &manager.getMetaObject<UI::FlexBox>();
        manager.registerMetaObject("UI.FlexBox", object);
    }
}

}
