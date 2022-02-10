#pragma once

namespace Graphics
{
struct RenderBuffer
{
    using This = RenderBuffer;
    InplaceStorage<RenderBufferPrivateData, 88, 8> Data;
    RenderBuffer();
    RenderBuffer(const RenderBuffer &other);
    RenderBuffer &operator =(const RenderBuffer &other);
    RenderBuffer(RenderBuffer &&other);
    RenderBuffer &operator =(RenderBuffer &&other);

     ~RenderBuffer();
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
}
