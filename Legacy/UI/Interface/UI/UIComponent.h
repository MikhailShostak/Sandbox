#pragma once

#include "Core/AVisualComponent.h"

#include <Assets>
#include "Graphics/MeshGenerator.h"

#include "Includes/View.gen.h"
#include "Includes/CanvasView.gen.h"

class AWindowTouchEvent;

namespace UI
{

class Component;

using Collision = APair<SharedReference<View>, Math::IntegerVector>;
using CollisionInfo = APair<bool, Collision>;

struct RaycastReport
{
    Array<CollisionInfo> results;

    Array<Collision> getFilteredCollisions(bool hit) const
    {
        Array<Collision> filteredCollisions;
        for (const CollisionInfo &info : results)
        {
            if (info.first == hit)
            {
                filteredCollisions.push_back(info.second);
            }
        }
        return filteredCollisions;
    }
};

class Raycast
{
    RaycastReport report;
public:
    const RaycastReport &getReport() const { return report; }

    bool cast(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<View> &view);

    bool worldCast(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<View> &view);
    bool screenCast(const Math::IntegerVector &screenPoint, const SharedReference<View> &view);

    void clear() { report.results.clear(); }
private:
    void castInternal(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<View> &view);
};

class Component : public AVisualComponent
{
    SharedReference<CanvasView> view = SharedReference<CanvasView>(Create<CanvasView>());
    struct ComponentManager : public ASingleton<ComponentManager>
    {
        SharedReference<Legacy::Graphics::Mesh> sprite = Legacy::Graphics::generateRectangle();
    };
public:
    using This = Component;
    using Super = AVisualComponent;
    //TODO: Implement style system
    static void loadDefaultStyle();

    static const SharedReference<Legacy::Graphics::Mesh> &getSprite()
    {
        return ComponentManager::getInstance().sprite;
    }

    static const SharedReference<Legacy::Graphics::Texture> &getPlaceholderImage()
    {
        static SharedReference<Legacy::Graphics::Texture> t;
        if (!t)
        {
            Math::IntegerVector size{ 256, 256 };
            Array<uint8_t> data;
            data.resize(size.getArea2() * 4);
            for (size_t j = 0; j < size.y; ++j)
            {
                for (size_t i = 0; i < size.x; ++i)
                {
                    data[(j * size.x + i) * 4 + 0] = 255;
                    data[(j * size.x + i) * 4 + 1] = 255;
                    data[(j * size.x + i) * 4 + 2] = 255;
                    data[(j * size.x + i) * 4 + 3] = 255;
                }
            }
            APixmap pixmap;
             
            pixmap.setBuffer(data, size, APixmapDataFormat::RGBA);
            t = std::make_shared<Legacy::Graphics::Texture>(pixmap);//(APixmapLoader::getInstance().decompress(getAsset("placeholder")));
        }
        return t;
    }

    Component(AEntity &owner, bool createRootView = false):
        AVisualComponent(owner)
    {
        view->updateOwners(this);
        if (createRootView)
        {
            setView(std::make_shared<View>());
        }

        ARegisterEventCallback(onTouchDown);
        ARegisterEventCallback(onTouchMove);
        ARegisterEventCallback(onTouchUp);
        ARegisterEventCallback(onTouchWheel);
    }

    ~Component()
    {
        AUnregisterEventCallback(onTouchWheel);
        AUnregisterEventCallback(onTouchUp);
        AUnregisterEventCallback(onTouchMove);
        AUnregisterEventCallback(onTouchDown);
    }

    Math::IntegerVector size;

    const SharedReference<View> &getView() const
    {
        return view->getViews().front();
    }

    void setView(const SharedReference<View> &view)
    {
        //AAssert(this->view != view, "View is already set to %s", AMeta::getObjectDescription(*view).toUtf8().data());
        if (!this->view->getViews().empty())
        {
            //this->view->getViews().first()->updateOwners(nullptr);
        }
        this->view->removeAllViews();
        if (view)
        {
            this->view->addView(view);
            //this->view->getViews().first()->updateOwners(this);
        }
    }

    void onLoad(ALoadEvent &event) override;
    void onUnload(AUnloadEvent &event) override;
    void onDraw(AUpdateEvent &event) override;

private:

    void onTouchDown(AWindowTouchDownEvent &event);
    void onTouchMove(AWindowTouchMoveEvent &event);
    void onTouchUp(AWindowTouchUpEvent &event);
    void onTouchWheel(AWindowTouchWheelEvent &event);
    void registerInput();
    void unregisterInput();

};
}
