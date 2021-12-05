#include "OpenGLParticleEmitterHandle.h"

void AOpenGLParticleEmitterHandle::draw() const
{
        glEnable(GL_BLEND);
        glDepthMask(false);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POINT_SPRITE);
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        auto emitter = this->emitter.lock();
        glBufferSubData(GL_ARRAY_BUFFER, 0, emitter->getSize() * AParticle::getSize(), emitter->getData());

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, AParticle::getSize(), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, false, AParticle::getSize(), (void*)12);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, AParticle::getSize(), (void*)16);

        glDrawArrays(GL_POINTS, 0, emitter->getSize());
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_BLEND);
        glDepthMask(true);
}

void AOpenGLParticleEmitterHandle::load(const WeakReference<AParticleEmitter> &e)
{
        emitter = e;

        auto emitter = this->emitter.lock();
        glGenBuffers(1, &vertexBuffer);
        printf("Bind vertext buffer %d\n", vertexBuffer);
        if(emitter->getSize() > 0)
        {
                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, emitter->getSize() * sizeof(float[8]), emitter->getData(), GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
}

void AOpenGLParticleEmitterHandle::unload()
{
        printf("Unbind vertext buffer %d\n", vertexBuffer);
        if(vertexBuffer)
        {
                glDeleteBuffers(1, &vertexBuffer);
                vertexBuffer = 0;
        }
}
