#pragma once

namespace Graphics
{
struct DrawBatchBase
{
    using This = DrawBatchBase;
    InplaceStorage<DrawBatchPrivateData, 8, 8> Data;
    DrawBatchBase();

     ~DrawBatchBase();
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<size_t/*Count*/, void*/*Buffer*/, size_t/*ActualBufferSize*/, size_t/*MaxBufferSize*/> GetLayoutInfo();
};
}
