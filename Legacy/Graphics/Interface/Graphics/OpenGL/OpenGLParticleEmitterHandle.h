#pragma once

#include "Graphics/AParticleEmitter.h"

#include "OpenGLPlatform.h"

class AOpenGLParticleEmitterHandle final : public AParticleEmitterHandle
{
    WeakReference<AParticleEmitter> emitter;
    GLuint vertexBuffer = 0;
public:
    virtual ~AOpenGLParticleEmitterHandle() { unload(); }
    virtual void draw() const;
    void load(const WeakReference<AParticleEmitter> &emitter);
    void unload();
};
