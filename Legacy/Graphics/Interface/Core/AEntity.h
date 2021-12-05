#pragma once

#include <Foundation>

#include "ACommonEvents.h"

class ASpace;
class AWindow;
class AComponent;
class AAddToSpaceEvent;
class ARemoveFromSpaceEvent;
class AAddToWindowEvent;
class ARemoveFromWindowEvent;

class AEntity : public AObject
{
    Array<::SharedReference<AComponent>> components;
    Math::Transform transform;

    ASpace *space = nullptr;

    AEventChannel eventChannel;

    bool isLoaded = false;
    bool hasCachedMatrix = false;
    mutable Math::Matrix cachedMatrix;

public:

    AEntity();
    virtual ~AEntity();

    AEventChannel &getEventChannel();
    const AEventChannel &getEventChannel() const;

    const Math::Vector &getPosition() const;
    void setPosition(const Math::Vector &transform);

    const Math::Quaternion &getRotation() const;
    void setRotation(const Math::Quaternion &rotation);

    const Math::Transform &getTransform() const;
    void setTransform(const Math::Transform &transform);

    const Math::Matrix &getMatrix() const;

    ASpace *getSpace() const;
    AWindow *getWindow() const;

    const Array<::SharedReference<AComponent>> &getComponents() const;
    void setComponents(const Array<::SharedReference<AComponent>> &components);

    void addComponent(const ::SharedReference<AComponent> &component);
    void insertComponent(size_t index, const ::SharedReference<AComponent> &component);
    void removeComponent(const ::SharedReference<AComponent> &component);
    void removeComponent(size_t index);

protected:

    virtual void onAddToSpace(AAddToSpaceEvent &event);
    virtual void onRemoveFromSpace(ARemoveFromSpaceEvent &event);
    virtual void onAddToWindow(AAddToWindowEvent &event);
    virtual void onRemoveFromWindow(ARemoveFromWindowEvent &event);

private:
    void loadComponents();
    void unloadComponents();
};
