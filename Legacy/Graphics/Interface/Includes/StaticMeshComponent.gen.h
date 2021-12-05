#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "VisualComponent.gen.h"
#include "Foundation"
#include "Mesh2.gen.h"
#include "Material2.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Legacy::Graphics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class StaticMeshComponent : public Graphics::VisualComponent
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef StaticMeshComponent This;
    typedef Graphics::VisualComponent Super;
    typedef void Interfaces;
protected:
    ::SharedReference<Graphics::Mesh2> Mesh;
::SharedReference<Graphics::Material2> Material;
public:
    StaticMeshComponent();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    ::SharedReference<Graphics::Mesh2> getMesh() const;
    void setMesh(::SharedReference<Graphics::Mesh2> const &Mesh);
    void setMesh(::SharedReference<Graphics::Mesh2> &&Mesh);
    ::SharedReference<Graphics::Material2> getMaterial() const;
    void setMaterial(::SharedReference<Graphics::Material2> const &Material);
    void setMaterial(::SharedReference<Graphics::Material2> &&Material);
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
