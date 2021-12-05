//CLASSGEN GENERATED REGION: Includes
#include "StaticMeshComponent.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Legacy::Graphics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
StaticMeshComponent::StaticMeshComponent()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void StaticMeshComponent::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void StaticMeshComponent::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
::SharedReference<Legacy::Graphics::Mesh2> StaticMeshComponent::getMesh() const
{
    return this->Mesh;
}
void StaticMeshComponent::setMesh(::SharedReference<Legacy::Graphics::Mesh2> const &Mesh)
{
    this->Mesh = Mesh;
}
void StaticMeshComponent::setMesh(::SharedReference<Legacy::Graphics::Mesh2> &&Mesh)
{
    this->Mesh = std::move(Mesh);
}
::SharedReference<Legacy::Graphics::Material2> StaticMeshComponent::getMaterial() const
{
    return this->Material;
}
void StaticMeshComponent::setMaterial(::SharedReference<Legacy::Graphics::Material2> const &Material)
{
    this->Material = Material;
}
void StaticMeshComponent::setMaterial(::SharedReference<Legacy::Graphics::Material2> &&Material)
{
    this->Material = std::move(Material);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
