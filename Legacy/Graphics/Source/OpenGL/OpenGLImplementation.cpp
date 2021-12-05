#pragma once
#include "Graphics.h"
#include "OpenGLPlatform.h"

#include "Canvas.h"
#include "AMesh.h"
#include "AMaterial.h"
#include "Includes/Texture.gen.h"

namespace Legacy::Graphics::API
{

void GLAPIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    ALogMessage("OpenGL", "%s type = 0x%x, severity = 0x%x, message = %s", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void glCheckErrors(bool skip)
{
    const auto error = glGetError();
    if (error == GL_NO_ERROR)
    {
        return;
    }

    ALogMessage("OpenGL", [&error]() -> const char * {
        switch (error)
        {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.  ";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.  ";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.  ";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return
                "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete."
                "The offending command is ignored and has no other side effect than to set the error flag.";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded. . ";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow. ";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow. ";
        default:
            return "Unspecified error";
        }
    }());

    if (!skip)
    {
        triggerBreak();
    }
}

static bool loaded = false;

void load()
{
    if (!loaded)
    {
        //glCall(glEnable, GL_DEBUG_OUTPUT_SYNCHRONOUS);
        //glCall(glDebugMessageCallback, glErrorCallback, 0);
        //glDebugMessageCallback(glErrorCallback, 0);

        loaded = true;
    }
}

void unload()
{
    if (loaded)
    {
        loaded = false;
    }
}

void setViewport(const Math::IntegerRectangle &viewport)
{
    glCall(glViewport, viewport.position.x, viewport.position.y, viewport.size.x, viewport.size.y);
}

void setBackgroundColor(const AColor &color)
{
    glCall(glClearColor, color.red(), color.green(), color.blue(), color.alpha());
}

void setBlending(bool blending)
{
    glCall(blending ? glEnable : glDisable, GL_BLEND);

    glCall(glBlendFunc, GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //Pre-multiplied Alpha

    //glCall(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glCall(glBlendFuncSeparate, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void setCulling(bool culling)
{
    glCall(culling ? glEnable : glDisable, GL_CULL_FACE);
}

void setUsingDepth(bool usingDepth)
{
    glCall(usingDepth ? glEnable : glDisable, GL_DEPTH_TEST);
}

void setWritingDepth(bool writingDepth)
{
    glCall(glDepthMask, writingDepth ? GL_TRUE : GL_FALSE);
}

void setDepthFunction(DepthFunction depthFuntion)
{
    glCall(glDepthFunc, GL_NEVER + uint8_t(depthFuntion));
}

void clear()
{
    glCall(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void flush()
{
    glCall(glFlush);
}

void HardwareObject<Canvas>::load(Canvas &canvas)
{
    AAssert(!isValid(), "Canvas is already loaded");
    glCall(glGenFramebuffers, 1, &frameBufferID);
    glCall(glGenRenderbuffers, 1, &renderBufferID);

    glCall(glBindRenderbuffer, GL_RENDERBUFFER, renderBufferID);
    glCall(glRenderbufferStorage, GL_RENDERBUFFER, GL_DEPTH_COMPONENT, canvas.getSize().x, canvas.getSize().y);
    glCall(glBindRenderbuffer, GL_RENDERBUFFER, 0);

    glCall(glBindFramebuffer, GL_FRAMEBUFFER, frameBufferID);
    bool hasColorMap = false;
    for (uint8_t i = 0; i <= Canvas::ColorAttachment15; ++i)
    {
        auto &texture = canvas.attachments[i];
        if (texture)
        {
            hasColorMap = true;
            if (texture->isLoaded())
            {
                glCall(glFramebufferTexture2D, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture->hardwareObject.textureID, 0);
            }
            else
            {
                ALogMessage("OpenGL", "Couldn't attach color target [%d], texture has invalid handle", i);
            }
        }
    }
    if (hasColorMap || (canvas.attachments[Canvas::DepthAttachment] && canvas.useDepth))
    {
        if (auto &texture = canvas.attachments[Canvas::DepthAttachment])
        {
            glCall(glFramebufferTexture2D, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->hardwareObject.textureID, 0);
        }
        else
        {
            if (canvas.useDepth)
            {
                glCall(glFramebufferRenderbuffer, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);
            }
            GLenum status = glGet(glCheckFramebufferStatus, GL_FRAMEBUFFER);
            if (status != GL_FRAMEBUFFER_COMPLETE)
            {
                switch (status)
                {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    ALogMessage("OpenGL", "Frame buffer incomplete attachment buffer");
                    return;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    ALogMessage("OpenGL", "Frame buffer incomplete missing buffer");
                    return;
#ifndef __ANDROID__
                case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                    ALogMessage("OpenGL", "Frame buffer incomplete dimensions buffer");
                    return;
                case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
                    ALogMessage("OpenGL", "Frame buffer incomplete formats buffer");
                    return;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                    ALogMessage("OpenGL", "Frame buffer incomplete draw buffer");
                    return;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                    ALogMessage("OpenGL", "Frame buffer incomplete read buffer");
                    return;
#endif
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    ALogMessage("OpenGL", "Frame buffer unsupported");
                    return;
                default:
                    ALogMessage("OpenGL", "Frame buffer unknown error");
                    return;
                }
            }
        }
    }
    glCall(glBindFramebuffer, GL_FRAMEBUFFER, 0);
}

void HardwareObject<Canvas>::unload(Canvas &canvas)
{
    if (renderBufferID != 0)
    {
        glCall(glDeleteRenderbuffers, 1, &renderBufferID);
        renderBufferID = 0;
    }
    if (frameBufferID != 0)
    {
        glCall(glDeleteFramebuffers, 1, &frameBufferID);
        frameBufferID = 0;
    }
}

void HardwareObject<Canvas>::activate(Canvas &canvas) const
{
    glCall(glBindFramebuffer, GL_FRAMEBUFFER, frameBufferID);
}

void HardwareObject<Canvas>::deactivate(Canvas &canvas) const
{
    glCall(glBindFramebuffer, GL_FRAMEBUFFER, 0);
}

GLuint CurrentTextureSlot = 0;

void HardwareObject<Material>::setTexture(const char *name, Legacy::Graphics::Texture &texture) const
{
    glCall(glActiveTexture, GL_TEXTURE0 + CurrentTextureSlot);
    texture.activate();
    glCall(glUniform1i, glGetUniformLocation(shaderProgramID, name), CurrentTextureSlot);
    ++CurrentTextureSlot;
}

void HardwareObject<Material>::activate() const
{
    glCall(glUseProgram, shaderProgramID);
    CurrentTextureSlot = 0;
}

template<GLenum ShaderType>
GLuint compileShaderSource(const char *source)
{
    GLuint handle = glGet(glCreateShader, ShaderType);
    glCall(glShaderSource, handle, 1, &source, nullptr);
    glCall(glCompileShader, handle);

    GLint resultCode = 0;
    glCall(glGetShaderiv, handle, GL_COMPILE_STATUS, &resultCode);
    if (!resultCode)
    {
        GLint errorLenght = 0;
        glCall(glGetShaderiv, handle, GL_INFO_LOG_LENGTH, &errorLenght);
        Array<GLchar> errorData(errorLenght);
        glCall(glGetShaderInfoLog, handle, errorLenght, &errorLenght, errorData.data());
        ALogMessage("OpenGL", "Failed to compile a shader:\r\n\r\n%s\r\n\r\n%s\r\n", source, errorData.data());
        glCall(glDeleteShader, handle);
        return 0;
    }

    return handle;
}

void HardwareObject<Material>::load(Legacy::Graphics::Material &material)
{
    AAssert(!isValid(), "Material is already loaded");
    GLuint vertexHandle = compileShaderSource<GL_VERTEX_SHADER>(material.generateVertexShader().data());
    GLuint fragmentHandle = compileShaderSource<GL_FRAGMENT_SHADER>(material.generateFragmentShader().data());

    if (!vertexHandle && !fragmentHandle)
    {
        return;
    }

    shaderProgramID = glGet(glCreateProgram);

    glCall(glAttachShader, shaderProgramID, vertexHandle);
    glCall(glAttachShader, shaderProgramID, fragmentHandle);

    glCall(glDeleteShader, vertexHandle);
    glCall(glDeleteShader, fragmentHandle);

    const Array<const char*> &meshLayout = material.getMeshLayout();
    for (GLint i = 0; i < meshLayout.size(); ++i)
    {
        glCall(glBindAttribLocation, shaderProgramID, i, meshLayout[i]);
    }

    glCall(glLinkProgram, shaderProgramID);

    GLint resultCode = 0;
    glCall(glGetProgramiv, shaderProgramID, GL_LINK_STATUS, &resultCode);
    if (!resultCode)
    {
        GLint errorLenght;
        glCall(glGetProgramiv, shaderProgramID, GL_INFO_LOG_LENGTH, &errorLenght);
        Array<GLchar> errorData(errorLenght);
        glCall(glGetProgramInfoLog, shaderProgramID, errorLenght, &errorLenght, errorData.data());
		ALogMessage("OpenGL", "Failed to link a shader program:\r\n\r\n%s\r\n\r\n%s\r\n\r\n%s\r\n", material.generateVertexShader(), material.generateFragmentShader(), errorData.data());
        return;
    }
    //debug("Shader", "Vertex %d, Fragment %d, Program %d", vertexHandle, fragmentHandle, shaderProgramID);
    /*#ifndef GL_ES_VERSION_2_0
    if (attachMatrix) {
    glUseProgram(shaderProgramID);
    Renderer::matrixHandler = glGetUniformBlockIndex(shaderProgramID, "transform");
    //Renderer::matrixData = new ubyte[sizeof (float[32])];
    glGenBuffers(1, &Renderer::matrixBuffer);

    glBindBuffer(GL_UNIFORM_BUFFER, Renderer::matrixBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glUseProgram(0);
    }
    #endif*/
}

void HardwareObject<Material>::unload(Legacy::Graphics::Material &material)
{
    if (shaderProgramID != 0)
    {
        glCall(glDeleteProgram, shaderProgramID);
        shaderProgramID = 0;
    }
}


void HardwareObject<Mesh>::drawPoints(const Mesh &mesh, const Legacy::Graphics::MaterialInterface &material) const
{
    glCall(glPolygonMode, GL_FRONT_AND_BACK, GL_POINT);
    draw(mesh, material);
}

void HardwareObject<Mesh>::drawLines(const Mesh &mesh, const Legacy::Graphics::MaterialInterface &material) const
{
    glCall(glPolygonMode, GL_FRONT_AND_BACK, GL_LINE);
    draw(mesh, material);
}

void HardwareObject<Mesh>::drawSurface(const Mesh &mesh, const Legacy::Graphics::MaterialInterface &material) const
{
    glCall(glPolygonMode, GL_FRONT_AND_BACK, GL_FILL);
    draw(mesh, material);
}

void HardwareObject<Mesh>::bindVerticies(const Mesh &mesh)
{
    glCall(glBindBuffer, GL_ARRAY_BUFFER, vertexBufferID);
}

void HardwareObject<Mesh>::fillVerticies(const Mesh &mesh)
{
    bindVerticies(mesh);
    glCall(glBufferData, GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(AVertex), mesh.getVertices().data(), GL_STATIC_DRAW);
}

void HardwareObject<Mesh>::bindIndicies(const Mesh &mesh)
{
    glCall(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
}


void HardwareObject<Mesh>::fillIndicies(const Mesh &mesh)
{
    bindIndicies(mesh);
    glCall(glBufferData, GL_ELEMENT_ARRAY_BUFFER, mesh.getFaces().size() * sizeof(AFace), mesh.getFaces().data(), GL_STATIC_DRAW);
}

void HardwareObject<Mesh>::bindAttributes(const Mesh &mesh)
{
    glCall(glEnableVertexAttribArray, 0);
    glCall(glVertexAttribPointer, 0, 3, GL_FLOAT, false, sizeof(AVertex), (void *)offsetof(AVertex, position));

    glCall(glEnableVertexAttribArray, 1);
    glCall(glVertexAttribPointer, 1, 3, GL_FLOAT, false, sizeof(AVertex), (void *)offsetof(AVertex, normal));

    glCall(glEnableVertexAttribArray, 2);
    glCall(glVertexAttribPointer, 2, 2, GL_FLOAT, false, sizeof(AVertex), (void *)offsetof(AVertex, texture));

    glCall(glEnableVertexAttribArray, 3);
    glCall(glVertexAttribPointer, 3, 1, GL_FLOAT, false, sizeof(AVertex), (void *)offsetof(AVertex, otherX));
}

void HardwareObject<Mesh>::bindMesh(const Mesh &mesh)
{
    bindVerticies(mesh);
    bindAttributes(mesh);
    bindIndicies(mesh);
}

void HardwareObject<Mesh>::draw(const Mesh &mesh, const Legacy::Graphics::MaterialInterface &material) const
{
    material.apply();
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    glCall(glEnable, GL_MULTISAMPLE);
    
    glCall(glBindVertexArray, vertexArrayID);
    glCall(glDrawElements, GL_TRIANGLES, mesh.getFaces().size() * 3, GL_UNSIGNED_SHORT, nullptr);
    glCall(glBindVertexArray, 0);
}

extern void onMeshLoad(Mesh &mesh);
extern void onMeshUnload(Mesh &mesh);

void HardwareObject<Mesh>::load(Mesh &mesh)
{
    AAssert(!isValid(), "Mesh is already loaded");
    if (mesh.getVertices().empty() || mesh.getFaces().empty())
    {
        return;
    }

    onMeshLoad(mesh);

    glCall(glGenVertexArrays, 1, &vertexArrayID);
    glCall(glBindVertexArray, vertexArrayID);

    glCall(glGenBuffers, 1, &vertexBufferID);
    fillVerticies(mesh);

    bindAttributes(mesh);

    glCall(glGenBuffers, 1, &indexBufferID);
    fillIndicies(mesh);

    glCall(glBindVertexArray, 0);

    glCall(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
    glCall(glBindBuffer, GL_ARRAY_BUFFER, 0);

    //ALogMessage("OpenGL", "Bind vertext buffer %d, indices buffer %d\n", vertexBufferID, indexBufferID);
}

void HardwareObject<Mesh>::unload(Mesh &mesh)
{
    onMeshUnload(mesh);
    //ALogMessage("OpenGL", "Unbind vertext buffer %d, indices buffer %d\n", vertexBufferID, indexBufferID);
    if (vertexBufferID != 0)
    {
        glCall(glDeleteBuffers, 1, &vertexBufferID);
        vertexBufferID = 0;
    }
    if (indexBufferID != 0)
    {
        glCall(glDeleteBuffers, 1, &indexBufferID);
        indexBufferID = 0;
    }
    if (vertexArrayID != 0)
    {
        glCall(glDeleteVertexArrays, 1, &vertexArrayID);
        vertexArrayID = 0;
    }
}

void HardwareObject<Texture>::load(Texture &texture)
{
    AAssert(!isValid(), "Texture is already loaded");
    if (texture.getSize().isEmpty())
    {
        ALogMessage("OpenGL", "Could bind texture, invalid size");
        triggerBreak();
        return;
    }

    GLint format;
    switch (texture.getFormat())
    {
    case APixmapDataFormat::Undefined:
        return;
    case APixmapDataFormat::Gray:
        //format = GL_LUMINANCE;
        format = GL_RED;
        break;
    case APixmapDataFormat::GrayAlpha:
        //format = GL_LUMINANCE_ALPHA;
        format = GL_RG;
        break;
    case APixmapDataFormat::RGB:
        format = GL_RGB;
        break;
    case APixmapDataFormat::RGBA:
        format = GL_RGBA;
        break;
    }

    glCall(glGenTextures, 1, &textureID);

#ifdef OPENGL_ES_3
    if (_depth > 1)
    {
        glCall(glBindTexture, GL_TEXTURE_3D, textureID);
        switch (texture.getFiltration())
        {
        case Nearest:
            glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case Bilinear:
            glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case Trilinear:
            glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        }
        glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glCall(glTexParameteri, GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glCall(glTexImage3D, GL_TEXTURE_3D, 0, format, texture.getSize().x, texture.getSize().y, _layer, 0, format, GL_UNSIGNED_BYTE, texture.getData());
    }
    else
    {
#endif
        glCall(glBindTexture, GL_TEXTURE_2D, textureID);
        switch (texture.getFiltration())
        {
        case TextureFiltration::Nearest:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case TextureFiltration::Bilinear:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        default:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        }
        switch (texture.getWrapping())
        {
        case TextureWrapping::TiledWrapping:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case TextureWrapping::HorizontalTiledWrapping:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case TextureWrapping::VerticalTiledWrapping:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case TextureWrapping::MirroredTiledWrapping:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        case TextureWrapping::HorizontalMirroredTiledWrapping:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case TextureWrapping::VerticalMirroredTiledWrapping:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        case TextureWrapping::WrapToBorder:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            break;
        case TextureWrapping::WrapToEdge:
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        }

        GLint const Swizzle[] = { GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA };
        if (texture.getFormat() == APixmapDataFormat::Gray)
        {
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);
        }
        else if (texture.getFormat() == APixmapDataFormat::GrayAlpha)
        {
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
            glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_GREEN);
        }

        glCall(glPixelStorei, GL_UNPACK_ALIGNMENT, 1);

        //https://www.khronos.org/opengl/wiki/Common_Mistakes#Automatic_mipmap_generation
        //glCall(glTexParameteri, GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glCall(glTexImage2D, GL_TEXTURE_2D, 0, format, texture.getSize().x, texture.getSize().y, 0, format, GL_UNSIGNED_BYTE, texture.getData());
#ifdef OPENGL_ES_3
    }
#endif
}

void HardwareObject<Texture>::unload(Texture &texture)
{
    if (textureID != 0)
    {
        glCall(glDeleteTextures, 1, &textureID);
        textureID = 0;
    }
}

void HardwareObject<Texture>::activate(Texture &texture)
{
    glCall(glBindTexture, GL_TEXTURE_2D, textureID);
}

void HardwareObject<Texture>::deactivate(Texture &texture)
{
    glCall(glBindTexture, GL_TEXTURE_2D, 0);
}

}
