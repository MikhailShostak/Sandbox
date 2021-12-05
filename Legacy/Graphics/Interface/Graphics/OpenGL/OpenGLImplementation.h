#pragma once
#include "OpenGLPlatform.h"

namespace Legacy::Graphics::API
{

void glCheckErrors(bool skip = false);

template<typename ReturnType, typename ...Types, typename ...Arguments>
ReturnType glGet(ReturnType(*api)(Types ...), Arguments &&...arguments)
{
    ReturnType &&result = api(std::forward<Arguments>(arguments)...);
    glCheckErrors();
    return std::forward<ReturnType>(result);
}

template<typename ...Types, typename ...Arguments>
void glCall(void(*api)(Types ...), Arguments &&...arguments)
{
    api(std::forward<Arguments>(arguments)...);
    glCheckErrors();
}

template<>
struct HardwareObject<Canvas>
{
    GLuint frameBufferID = 0;
    GLuint renderBufferID = 0;

    bool isValid() const
    {
        return frameBufferID != 0 && renderBufferID != 0;
    }

    void load(Canvas &canvas);
    void unload(Canvas &canvas);
    void activate(Canvas &canvas) const;
    void deactivate(Canvas &canvas) const;
};

template<>
struct HardwareObject<Material>
{
    static_assert(sizeof(int32_t) == sizeof(GLint), "Interface could be broken on this platform");

    GLuint shaderProgramID = 0;

    bool isValid() const
    {
        return shaderProgramID != 0;
    }

    void load(Material &material);
    void unload(Material &material);

    void setInt(const char *name, int32_t value) const { glCall(glUniform1i, glGetUniformLocation(shaderProgramID, name), value); }
    void setFloat(const char *name, float value) const { glCall(glUniform1f, glGetUniformLocation(shaderProgramID, name), value); }
    void setIntVector2D(const char *name, const int32_t *data) const { glCall(glUniform2iv, glGetUniformLocation(shaderProgramID, name), 1, data); }
    void setIntVector3D(const char *name, const int32_t *data) const { glCall(glUniform3iv, glGetUniformLocation(shaderProgramID, name), 1, data); }
    void setIntVector4D(const char *name, const int32_t *data) const { glCall(glUniform4iv, glGetUniformLocation(shaderProgramID, name), 1, data); }
    void setFloatVector2D(const char *name, const float *data) const { glCall(glUniform2fv, glGetUniformLocation(shaderProgramID, name), 1, data); }
    void setFloatVector3D(const char *name, const float *data) const { glCall(glUniform3fv, glGetUniformLocation(shaderProgramID, name), 1, data); }
    void setFloatVector4D(const char *name, const float *data) const { glCall(glUniform4fv, glGetUniformLocation(shaderProgramID, name), 1, data); }
    void setMatrix2D(const char *name, const float *data) const { glCall(glUniformMatrix2fv, glGetUniformLocation(shaderProgramID, name), 1, false, data); }
    void setMatrix3D(const char *name, const float *data) const { glCall(glUniformMatrix3fv, glGetUniformLocation(shaderProgramID, name), 1, false, data); }
    void setMatrix4D(const char *name, const float *data) const { glCall(glUniformMatrix4fv, glGetUniformLocation(shaderProgramID, name), 1, false, data); }

    [[deprecated("Need to fix material generator")]]
    void setTexture(const char *name, Graphics::Texture *texture) const { setTexture(name, *texture); }
    void setTexture(const char *name, Graphics::Texture &texture) const;

    void setVector2(const char *name, const Math::IntegerVector &point) const { setIntVector2D(name, &point.x); }
    void setVector3(const char *name, const Math::IntegerVector &point) const { setIntVector3D(name, &point.x); }
    void setVector4(const char *name, const Math::IntegerVector &point) const { setIntVector4D(name, &point.x); }
    void setVector2(const char *name, const Math::Vector &point) const { setFloatVector2D(name, &point.x); }
    void setVector3(const char *name, const Math::Vector &point) const { setFloatVector3D(name, &point.x); }
    void setVector4(const char *name, const Math::Vector &point) const { setFloatVector4D(name, &point.x); }
    void setColor(const char *name, const AColor &color) const { setFloatVector4D(name, color.data()); }
    void setMatrix(const char *name, const Math::Matrix &matrix) const { setMatrix4D(name, &matrix.data[0][0]); }

    constexpr static const GLint InvalidHandle = -1;
    GLint handle(const char *name) const
    {
        //https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml
        //This function returns -1 if name does not correspond to an active uniform variable in program,
        //if name starts with the reserved prefix "gl_",
        //or if name is associated with an atomic counter or a named uniform block.

        GLint uinformLocation = InvalidHandle;
        if (shaderProgramID == GL_INVALID_VALUE)
        {
            ALogMessage("OpenGL", "Couldn't get uniform \"%s\" from invalid program", name);
            return uinformLocation;
        }
        uinformLocation = glGet(glGetUniformLocation, shaderProgramID, name);
        if (uinformLocation == InvalidHandle)
        {
            ALogMessage("OpenGL", "Couldn't find uniform \"%s\" from program %d", name, shaderProgramID);
            return uinformLocation;
        }

        return uinformLocation;
    }
    void activate() const;
};

template<>
struct HardwareObject<Mesh>
{
    GLuint vertexArrayID = 0;
    GLuint vertexBufferID = 0;
    GLuint indexBufferID = 0;

    bool isValid() const
    {
        return vertexBufferID != 0 && indexBufferID != 0;
    }

    void load(Mesh &mesh);
    void unload(Mesh &mesh);

    void bindVerticies(const Mesh &mesh);
    void fillVerticies(const Mesh &mesh);
    void bindIndicies(const Mesh &mesh);
    void fillIndicies(const Mesh &mesh);
    void bindAttributes(const Mesh &mesh);

    void bindMesh(const Mesh &mesh);

    void drawPoints(const Mesh &mesh, const MaterialInterface &material) const;
    void drawLines(const Mesh &mesh, const MaterialInterface &material) const;
    void drawSurface(const Mesh &mesh, const MaterialInterface &material) const;
private:
    void draw(const Mesh &mesh, const MaterialInterface &material) const;
};

template<>
struct HardwareObject<Texture>
{
    GLuint textureID = 0;

    bool isValid() const
    {
        return textureID != 0;
    }

    void load(Texture &texture);
    void unload(Texture &texture);
    void activate(Texture &texture);
    void deactivate(Texture &texture);
};

}
