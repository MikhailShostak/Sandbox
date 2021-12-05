#pragma once

#include <Foundation>
#include "Includes/Texture.gen.h"
#include "HardwareHandle.h"

class AGraphicsContext;

class AViewObject;

namespace Legacy::Graphics
{

class MaterialInterface
{
public:
    virtual ~MaterialInterface() {}
    virtual bool isOpaque() const = 0;
    virtual void apply() const = 0;
    virtual bool isLoaded() const = 0;
};

struct MaterialData
{

};

class Material : public HardwareHandle<Material>, public MaterialInterface
{
    friend class AViewObject;
    bool opaque = true;
public:

    virtual ~Material() {}

    void onActivate() {}
    void onDeactivate() {}

    bool isOpaque() const;
    void setOpaque(bool opaque);

    bool isLoaded() const { return HardwareHandle<Material>::isLoaded(); } //TODO: prevent this

    virtual Array<String> getVertexShaderAttributes() const { return {" vec3 Position", "vec3 Normal", "vec2 UV" }; }
    virtual Array<String> getVertexShaderOutputs() const { return { " vec3 vPosition", "vec3 vNormal", "vec2 vUV" }; }

    virtual String generateVertexShaderInputs() const
    {
        String result;
        Array<String> attributes = getVertexShaderAttributes();
        for (const String &v : attributes)
        {
            result.append(String("in ") + v + ";\n");
        }
        return result;
    }

    virtual String generateVertexShaderOutputs() const
    {
        String result;
        Array<String> outputs = getVertexShaderOutputs();
        for (const String &v : outputs)
        {
            result.append(String("out ") + v + ";\n");
        }
        return result;
    }

    virtual String generateFragmentShaderInputs() const
    {
        String result;
        Array<String> outputs = getVertexShaderOutputs();
        for (const String &v : outputs)
        {
            result.append(String("in ") + v + ";\n");
        }
        return result;
    }

    virtual String generateFragmentShaderOutputs() const
    {
        return String();
    }

    virtual const Array<const char *> &getMeshLayout() const { return Memory::Empty<Array<const char *>>; }
    virtual String generateProperties() const { return String(); }

    virtual String generateVertexPosition() const
    {
        /*"vPosition = position;"
        "vNormal = normalize(normal);"
        "vTexel = texture;"
        "return mvpMatrix * vec4(position, 1.0);\n"*/
        return "return vec4(position, 1.0);";
    }

    virtual String generateFragmentColor() const
    {
        /* "return texture2D(colorMap, vTexel) * color;"*/
        return "return vec4(1.0, 1.0, 1.0, 1.0);";
    }

    virtual String generateVertexShader() const;
    virtual String generateFragmentShader() const;

    [[deprecated("This function is needed for material polymorphisms. Need to do it with a less expensive way")]]
    virtual void apply() const
    {
        hardwareObject.activate();
    }
    [[deprecated("This function is needed for material generator. Need to do fix the generator and to cut this function")]]
    virtual auto getHandle() const -> decltype(&const_cast<Material *>(this)->hardwareObject)
    {
        return &const_cast<Material *>(this)->hardwareObject;
    }
};

#define DeclareDynamicMaterial(name, structure) \
 class Dynamic ## name : public Legacy::Graphics::MaterialInterface \
{ \
    struct Dynamic ## name ## Manager : public ASingleton<Dynamic ## name ## Manager> \
    { \
        name material; \
    }; \
    bool opaque = true; \
public: \
 \
    structure data; \
    static name &getMaterial() { return Dynamic ## name ## Manager::getInstance().material; } \
    bool isLoaded() const { return getMaterial().isLoaded(); } \
    virtual void load() \
    { \
        if (!getMaterial().isLoaded()) \
        { \
            getMaterial().load(); \
        } \
    } \
 \
    virtual bool isOpaque() const { return opaque; } \
    virtual void setOpaque(bool opaque) { this->opaque = opaque; } \
    virtual void apply() const; \
}; \
inline void Dynamic ## name ::apply() const

DeclareDynamicMaterial(Material, MaterialData)
{
    getMaterial().apply();
}

inline bool Material::isOpaque() const
{
    return this->opaque;
}

inline void Material::setOpaque(bool opaque)
{
    this->opaque = opaque;
}

inline String Material::generateVertexShader() const
{
    return
        "#version 330\n"
        "#ifdef GL_ES\n"
        "precision highp float;\n"
        "#endif\n" +
        generateVertexShaderInputs() +
        generateVertexShaderOutputs() +
        generateProperties() +
        /*"attribute vec3 position;"
        "attribute vec3 normal;"
        "attribute vec2 texture;"

        "uniform mat4 mvMatrix;"
        "uniform mat4 mvpMatrix;"
        "varying vec3 vPosition;"
        "varying vec3 vNormal;"
        "varying vec2 vTexel;"*/

        "vec4 getVertexPosition()"
        "{"
        + generateVertexPosition() +
        "}"

        "void main()"
        "{"
        "    gl_Position = getVertexPosition();"
        "}";
}

inline String Material::generateFragmentShader() const
{
    return
        "#version 330\n"
        "#ifdef GL_ES\n"
        "precision highp float;\n"
        "#endif\n" +
        generateFragmentShaderInputs() +
        generateFragmentShaderOutputs() +
        generateProperties() +
        /*"uniform sampler2D colorMap;"
        "uniform vec4 color;"
        "varying vec3 vPosition;"
        "varying vec3 vNormal;"
        "varying vec2 vTexel;"*/

        "vec4 getFragmentColor()"
        "{"
        + generateFragmentColor() +
        "}"

        "void main()"
        "{"
        "    gl_FragColor = getFragmentColor();"
        "}";
}

}
