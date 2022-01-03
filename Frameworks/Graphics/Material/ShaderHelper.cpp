#include "PrivateImplementation.hpp"

namespace Graphics
{

ShaderMetatype::ShaderMetatype() = default;
ShaderMetatype::ShaderMetatype(const ShaderMetatype & other) = default;
ShaderMetatype &ShaderMetatype::operator =(const ShaderMetatype & other) = default;
ShaderMetatype::ShaderMetatype(ShaderMetatype && other) = default;
ShaderMetatype &ShaderMetatype::operator =(ShaderMetatype && other) = default;
ShaderMetatype::~ShaderMetatype() = default;

ShaderMetatype::ShaderMetatype(const char *Metatype, const char *Name, size_t DataSize)
{
    this->Metatype = Metatype;
    this->Name = Name;
    this->DataSize = DataSize;
}



}
