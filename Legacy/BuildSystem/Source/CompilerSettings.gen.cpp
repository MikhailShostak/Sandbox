//CLASSGEN GENERATED REGION: Includes
#include "CompilerSettings.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
CompilerSettings::CompilerSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void CompilerSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Compiler", toJSONValue(Compiler));
    object.insert("DefineFlag", toJSONValue(DefineFlag));
    object.insert("IncludeFlag", toJSONValue(IncludeFlag));
    object.insert("IncludePathFlag", toJSONValue(IncludePathFlag));
    object.insert("OutputFileFlag", toJSONValue(OutputFileFlag));
    object.insert("CompilationFlag", toJSONValue(CompilationFlag));
    object.insert("Flags", toJSONValue(Flags));
}
void CompilerSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Compiler", value);
    fromJSONValue(value, Compiler);
    value = AJSONValue();
    object.read("DefineFlag", value);
    fromJSONValue(value, DefineFlag);
    value = AJSONValue();
    object.read("IncludeFlag", value);
    fromJSONValue(value, IncludeFlag);
    value = AJSONValue();
    object.read("IncludePathFlag", value);
    fromJSONValue(value, IncludePathFlag);
    value = AJSONValue();
    object.read("OutputFileFlag", value);
    fromJSONValue(value, OutputFileFlag);
    value = AJSONValue();
    object.read("CompilationFlag", value);
    fromJSONValue(value, CompilationFlag);
    value = AJSONValue();
    object.read("Flags", value);
    fromJSONValue(value, Flags);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
