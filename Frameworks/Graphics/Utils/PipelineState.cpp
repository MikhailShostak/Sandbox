#include "PrivateImplementation.hpp"

namespace Graphics
{

PipelineState::PipelineState() = default;
PipelineState::PipelineState(PipelineState&& other) = default;
PipelineState& PipelineState::operator =(PipelineState&& other) = default;
PipelineState::~PipelineState() = default;

}
