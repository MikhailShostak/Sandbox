#pragma once

namespace Graphics
{
struct PipelineState
{
    using This = PipelineState;
    InplaceStorage<PipelineStatePrivateData, 768, 8, false> Data;
    PipelineState();

     ~PipelineState();
    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
