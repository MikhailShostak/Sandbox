#pragma once

#include "Includes/CanvasView.gen.h"

namespace UI
{

class Viewport : public CanvasView
{
public:

    using Super = CanvasView;

    Array<SharedReference<ASpace>> spaces;

    void onDrawContent(AUpdateEvent &event) override
    {
        Super::onDrawContent(event);

        for (auto &space : spaces)
        {
            space->getCamera()->resolution = getSize();
            space->update(event);
        }
    }
};

}
