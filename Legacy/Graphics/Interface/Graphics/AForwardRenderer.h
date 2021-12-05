#pragma once

#include "ARenderer.h"

#include "AMesh.h"
#include "AMaterial.h"
#include "ACamera.h"
#include "AGraphicsContext.h"
#include "VisualDebug.h"

namespace Legacy::Graphics
{

class AForwardRenderer : public ARenderer
{
    struct ADrawBatch
    {
        ::SharedReference<Mesh> mesh;
        Array<::SharedReference<MaterialInterface>> materials;
    };

    Array<ADrawBatch> opaqueBatches;
    Array<ADrawBatch> translucentBatches;

    bool usingDepth = true;
    bool writingDepth = true;
    Graphics::API::DepthFunction depthFuntion = Graphics::API::DepthFunction::Less;

public:

    AForwardRenderer()
    {
        opaqueBatches.reserve(4048);
        translucentBatches.reserve(4048);
    }

    bool isUsingDepth() const
    {
        return this->usingDepth;
    }

    void setUsingDepth(bool usingDepth)
    {
        this->usingDepth = usingDepth;
    }

    bool isWritingDepth()
    {
        return this->writingDepth;
    }

    void setWritingDepth(bool writingDepth)
    {
        this->writingDepth = writingDepth;
    }

    Graphics::API::DepthFunction getDepthFunction() const
    {
        return this->depthFuntion;
    }

    void setDepthFunction(Graphics::API::DepthFunction depthFuntion)
    {
        this->depthFuntion = depthFuntion;
    }

    void addMesh(const ::SharedReference<Mesh> &mesh, const ::SharedReference<MaterialInterface> &material) override
    {
        AAssert(mesh && mesh->isLoaded(), "Mesh is not loaded");
        AAssert(material && material->isLoaded(), "Material is not loaded");
        auto insert = [&](Array<ADrawBatch> &batches) {
            auto it = std::find_if(batches.begin(), batches.end(), [&mesh](ADrawBatch &batch) {
                return batch.mesh == mesh;
            });
            if (it != batches.end())
            {
                it->materials.push_back(material);
            }
            else
            {
                batches.push_back({ mesh, { material } });
            }
        };

        /*if(material->isOpaque())
        {
            insert(opaqueBatches);
        }
        else*/
        {
            insert(translucentBatches);
        }
    }

    void clear() override
    {
        opaqueBatches.clear();
        translucentBatches.clear();
    }

    void render() override
    {
        if (!opaqueBatches.empty())
        {
            if (isUsingDepth())
            {
                Graphics::API::setUsingDepth(true);
                Graphics::API::setWritingDepth(isWritingDepth());
                Graphics::API::setDepthFunction(getDepthFunction());
            }
            else
            {
                Graphics::API::setUsingDepth(false);
            }

            Graphics::API::setBlending(false);
            std::reverse(opaqueBatches.begin(), opaqueBatches.end());
            for (auto &batch : opaqueBatches)
            {
                std::reverse(batch.materials.begin(), batch.materials.end());
            }
            renderBatch(opaqueBatches);
        }

        if (!translucentBatches.empty())
        {
            Graphics::API::setBlending(true);
            Graphics::API::setDepthFunction(Graphics::API::DepthFunction::Always);
            Graphics::API::setWritingDepth(false);
            renderBatch(translucentBatches);
            Graphics::API::setWritingDepth(true);
        }

        if (debugName)
        {
            VisualDebug(debugName).render();
        }
        Graphics::API::setWritingDepth(true);
    }

private:

    void renderBatch(Array<ADrawBatch> &batches)
    {
        for(auto &batch : batches)
        {
            batch.mesh->drawSurface(batch.materials);
        }
    }
};

}
