#pragma once

namespace Graphics
{
template<typename Type>
struct DrawBatch
    : public Graphics::DrawBatchBase
{
    using This = DrawBatch;
    using Super = Graphics::DrawBatchBase;
    Array<Type> Instances;
    size_t MaxSize;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<size_t/*Count*/, void*/*Buffer*/, size_t/*ActualBufferSize*/, size_t/*MaxBufferSize*/> GetLayoutInfo();
};
}
