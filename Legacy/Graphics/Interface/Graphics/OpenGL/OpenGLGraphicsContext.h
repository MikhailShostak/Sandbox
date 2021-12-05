#pragma once

#include <Foundation>

#include "Graphics/AGraphicsEvents.h"

class AMesh;
namespace Core
{
    class Material;
}
class AParticleEmitter;

class AOpenGLGraphicsContext : public AObject
{
    AObject &owner;
public:
    AOpenGLGraphicsContext(AObject &owner);
};
