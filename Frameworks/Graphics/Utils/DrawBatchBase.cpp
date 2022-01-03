#include "PrivateImplementation.hpp"

namespace Graphics
{

DrawBatchBase::DrawBatchBase()
{

}

DrawBatchBase::~DrawBatchBase()
{

}

std::tuple<size_t/*Count*/, void */*Buffer*/, size_t/*ActualBufferSize*/, size_t/*MaxBufferSize*/> DrawBatchBase::GetLayoutInfo()
{
    return { 0, nullptr, 0, 0 };
}

}
