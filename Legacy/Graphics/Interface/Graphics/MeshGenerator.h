#pragma once

#include "AMesh.h"

namespace Legacy::Graphics
{

inline ::SharedReference<Mesh> generateGrid()
{
    ::SharedReference<Mesh> mesh = std::make_shared<Mesh>();
    return mesh;
}

inline ::SharedReference<Mesh> generateRectangle()
{
    ::SharedReference<Mesh> mesh = std::make_shared<Mesh>();
    // 0 +-------+ 1   | y
    //   |     / |     |
    //   |   /   |     +---- x
    //   | /     |    /
    // 2 +-------+ 3 z

    mesh->setVertices({
        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
    });
    mesh->setFaces({
        { 0, 2, 1 },
        { 1, 2, 3 },
    });
    return mesh;
}

inline ::SharedReference<Mesh> generateBox()
{
    ::SharedReference<Mesh> mesh = std::make_shared<Mesh>();
    return mesh;
}

inline ::SharedReference<Mesh> generateCapsule()
{
    ::SharedReference<Mesh> mesh = std::make_shared<Mesh>();
    return mesh;
}

inline ::SharedReference<Mesh> generateSphere()
{
    ::SharedReference<Mesh> mesh = std::make_shared<Mesh>();
    // 0 +-------+ 1   | y
    //   |     / |     |
    //   |   /   |     +---- x
    //   | /     |    /
    // 2 +-------+ 3 z

    /*Array<AVertex> vertices;
    for ()
    {

    }*/

    mesh->setVertices({
        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
    });
    mesh->setFaces({
        { 0, 2, 1 },
        { 1, 2, 3 },
    });
    return mesh;
}

};
