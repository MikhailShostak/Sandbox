#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
#include <Data>
//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct CompilerSettings : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef CompilerSettings This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Compiler;
    String DefineFlag;
    String IncludeFlag;
    String IncludePathFlag;
    String OutputFileFlag;
    String CompilationFlag;
    String Flags;
public:
    CompilerSettings();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
