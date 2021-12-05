#pragma once

#include <Math>

struct AVertex
{
    Math::Vector position;
    Math::Vector normal;
    Math::Vector texture;
    float otherX;
    float otherY;
    float otherZ;
    float otherW;

    AVertex(float x = 0.0f, float y = 0.0f, float z = 0.0f,
    float normalX = 0.0f, float normalY = 0.0f, float normalZ = 0.0f,
    float textureX = 0.0f, float textureY = 0.0f,
    float otherX = 0.0f, float otherY = 0.0f, float otherZ = 0.0f, float otherW = 0.0f):
    position({ x, y, z }),
    normal({ normalX, normalY, normalZ }),
    texture({ textureX, textureY }),
    otherX(otherX), otherY(otherY), otherZ(otherZ), otherW(otherW) {}

    void setPosition(float x, float y, float z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void setNormal(float x, float y, float z)
    {
        normal.x = x;
        normal.y = y;
        normal.z = z;
    }

    void setTexture(float x, float y)
    {
        texture.x = x;
        texture.y = y;
    }

    void setOther(float x, float y)
    {
        otherX = x;
        otherY = y;
    }

    void setOther(float x, float y, float z)
    {
        otherX = x;
        otherY = y;
        otherZ = z;
    }

    void setOther(float x, float y, float z, float w)
    {
        otherX = x;
        otherY = y;
        otherZ = z;
        otherW = w;
    }

    float *data() { return &position.x; }
    const float *data() const { return &position.x; }
    float &operator[](size_t index) { return (&position.x)[index]; }
    const float &operator[](size_t index) const { return (&position.x)[index]; }
};
