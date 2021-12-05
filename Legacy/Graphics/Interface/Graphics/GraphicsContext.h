#pragma once

#include "ACamera.h"

namespace Legacy::Graphics
{

class GraphicsContext
{
    struct GraphicsManager : public ASingleton<GraphicsManager>
    {
        Array<GraphicsContext *> contexts;
    };

    static Array<GraphicsContext *> &contexts()
    {
        return GraphicsManager::getInstance().contexts;
    }
    static void updateViewport()
    {
        if(!getCurrent().ApplyViewport)
        {
            return;
        }

        Math::IntegerVector viewport = ACamera::getCurrentCamera()->resolution;
        Graphics::API::setViewport(Math::IntegerRectangle{ { 0, 0 }, { viewport.x, viewport.y }});
    }
public:

    bool ApplyViewport = true;

    static GraphicsContext &getCurrent()
    {
        return *contexts().back();
    }

    static void pushContext(GraphicsContext &context)
    {
        contexts().push_back(&context);
        context.onActive();
        updateViewport();
    }

    static void popContext()
    {
        //AAssert(&getCurrent() == context, "This context should be active");
        getCurrent().onDeactive();
        contexts().pop_back();
        if (!contexts().empty())
        {
            updateViewport();
        }
    }

    virtual Math::IntegerVector getViewport() const = 0;
    virtual void onActive() = 0; //TODO: rename
    virtual void onDeactive() = 0;
    virtual void draw(const ::SharedReference<Mesh> &mesh, const ::SharedReference<MaterialInterface> &material) = 0;
    //virtual void draw(const ::SharedReference<class Mesh3> &mesh, const ::SharedReference<class Material3> &material) {}
};

}
