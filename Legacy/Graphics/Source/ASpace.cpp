#include "ASpace.h"
#include "AWindow.h"
#include "ARenderer.h"
#include "ACamera.h"
#include "AEntity.h"
#include "AComponent.h"
#include "ACommonEvents.h"
#include "AWindowEvents.h"
#include "ASpaceEvents.h"
#include "AGraphicsContext.h"
#include "VisualDebug.h"

#include "MetaObject.h"

AStaticRun(SpaceMetaObject)
{
CLASSGEN_GENERATED_REGION_META_OBJECT
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<ASpace>();
    object.serialize = [](const AObject &object, AJSONObject &data){ static_cast<const ASpace&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object){ static_cast<ASpace&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<AObject>();
    object.registerMetaProperty<ASpace, AWindow *>("Window", &ASpace::getWindow, static_cast<void(ASpace::*)(AWindow * const &)>(nullptr), false);
    object.registerMetaProperty<ASpace, ACamera *>("Camera", &ASpace::getCamera, static_cast<void(ASpace::*)(ACamera * const &)>(nullptr), false);
    object.registerMetaProperty<ASpace, Legacy::Graphics::ARenderer *>("Renderer", &ASpace::getRenderer, static_cast<void(ASpace::*)(Legacy::Graphics::ARenderer * const &)>(nullptr), false);
    manager.registerMetaObject("ASpace", object);
CLASSGEN_END_REGION
}

CLASSGEN_GENERATED_REGION_OBJECT
void ASpace::serialize(AJSONObject &object) const
{
}
void ASpace::deserialize(const AJSONObject &object)
{
    AJSONValue value;
}
AWindow * ASpace::getWindow() const
{
    return this->window;
}
ACamera * ASpace::getCamera() const
{
    return this->camera;
}
Legacy::Graphics::ARenderer * ASpace::getRenderer() const
{
    return this->renderer;
}
CLASSGEN_END_REGION

ASpace::ASpace()
{
    ARegisterEventCallback(onAddToWindow);
    ARegisterEventCallback(onRemoveFromWindow);
}

ASpace::ASpace(Legacy::Graphics::ARenderer &renderer, ACamera &camera):
    renderer(&renderer),
    camera(&camera)
{
    ARegisterEventCallback(onAddToWindow);
    ARegisterEventCallback(onRemoveFromWindow);
}

ASpace::~ASpace()
{
    AUnregisterEventCallback(onRemoveFromWindow);
    AUnregisterEventCallback(onAddToWindow);
}

void ASpace::onAddToWindow(AAddToWindowEvent &event)
{
    this->window = &event.getWindow();
    eventChannel.sendEvent(event);
}

void ASpace::onRemoveFromWindow(ARemoveFromWindowEvent &event)
{
    eventChannel.sendEvent(event);
    this->window = nullptr;
}

void ASpace::onActive()
{
    ACamera::pushCamera(*camera);
    renderer->clear();
}

void ASpace::onDeactive()
{
    renderer->render();
    ACamera::popCamera();
}

void ASpace::update(AUpdateEvent &event)
{
    Legacy::Graphics::GraphicsContext::pushContext(*this);
    AUpdateEvent e(*this);
    eventChannel.sendEvent(e);
    //VisualDebug::getInstance().drawSphereWireframe(Math::Vector{}, 0.5f, AColor(AColorName::Red));
    Legacy::Graphics::GraphicsContext::popContext();
}

const Array<::SharedReference<AEntity>> &ASpace::getEntities() const
{
    return this->entities;
}

void ASpace::setEntities(const Array<::SharedReference<AEntity>> &entities)
{
    notifyRemovedEntities(this->entities);
    this->entities = entities;
    notifyAddedEntities(this->entities);
}

void ASpace::setEntities(Array<::SharedReference<AEntity>> &&entities)
{
    notifyRemovedEntities(this->entities);
    this->entities = std::move(entities);
    notifyAddedEntities(this->entities);
}

void ASpace::addEntity(const ::SharedReference<AEntity> &entity)
{
    AAssert(entity, "Entity should be set");
    this->entities.push_back(entity);
    notifyAddedEntity(*entity);
}

void ASpace::addEntities(const Array<::SharedReference<AEntity>> &entities)
{
    ArrayUtils::Add(this->entities, entities);
    notifyAddedEntities(entities);
}

void ASpace::addEntities(Array<::SharedReference<AEntity>> &&entities)
{
    ArrayUtils::Add(this->entities, std::move(entities));
    notifyAddedEntities(entities);
}

void ASpace::removeEntity(const ::SharedReference<AEntity> &entity)
{
    AAssert(entity, "Entity should be set");
    notifyRemovedEntity(*entity);
    ArrayUtils::Remove(this->entities, entity);
}

void ASpace::removeEntities(const Array<::SharedReference<AEntity>> &entities)
{
    notifyRemovedEntities(this->entities);
    ArrayUtils::Remove(this->entities, entities);
}

void ASpace::removeAllEntities()
{
    notifyRemovedEntities(this->entities);
    this->entities.clear();
}

void ASpace::notifyAddedEntities(const Array<::SharedReference<AEntity>> &entities)
{
    for (auto &entity : entities)
    {
        notifyAddedEntity(*entity);
    }
}

void ASpace::notifyRemovedEntities(const Array<::SharedReference<AEntity>> &entities)
{
    for (auto &entity : entities)
    {
        notifyAddedEntity(*entity);
    }
}

void ASpace::notifyAddedEntity(AEntity &entity)
{
    AAddToSpaceEvent e(*this);
    entity.sendEvent(e);
}

void ASpace::notifyRemovedEntity(AEntity &entity)
{
    ARemoveFromSpaceEvent e(*this);
    entity.sendEvent(e);
}
