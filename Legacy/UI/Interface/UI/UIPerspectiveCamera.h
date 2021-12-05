#pragma once

#include "Graphics/APerspectiveCamera.h"

namespace UI
{

class PerspectiveCamera : public APerspectiveCamera
{
public:
    Math::Matrix getViewMatrix() const override;
    Math::Matrix getProjectionMatrix() const override;
};

}
