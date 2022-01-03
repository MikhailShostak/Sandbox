#include "PrivateImplementation.hpp"

namespace Graphics
{

RenderBuffer::RenderBuffer() = default;
RenderBuffer::RenderBuffer(const RenderBuffer &value) = default;
RenderBuffer &RenderBuffer::operator =(const RenderBuffer &value) = default;
RenderBuffer::RenderBuffer(RenderBuffer &&value) = default;
RenderBuffer &RenderBuffer::operator =(RenderBuffer &&value) = default;
RenderBuffer::~RenderBuffer() = default;

}
