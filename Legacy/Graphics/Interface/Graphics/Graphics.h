#pragma once

#include <Foundation>

namespace Legacy::Graphics
{

class Canvas;
class Material;
class MaterialInterface;
class Mesh;
class Texture;

namespace API
{

template<typename Object>
struct HardwareObject;

enum class DepthFunction
{
    Never = 0,
    Less,
    Equal,
    LessOrEqual,
    Greater,
    NotEqual,
    GreaterOrEqual,
    Always,
};

void load();
void unload();

void setViewport(const Math::IntegerRectangle &viewport);
void setBackgroundColor(const AColor &color);
void setBlending(bool blending);
void setCulling(bool culling);
void setUsingDepth(bool usingDepth);
void setWritingDepth(bool writingDepth);
void setDepthFunction(DepthFunction depthFuntion);
void clear();
void flush();

}

}
#if defined(DIRECT_X_API)
#include "Graphics/DirectX/DirectXImplementation.h"
#else
#include "Graphics/OpenGL/OpenGLImplementation.h"
#endif
