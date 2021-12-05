#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class TextureCompilation
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        RelativePath,
        AbsolutePath,
        Embedded,
    };
    Enum value = RelativePath;
    TextureCompilation();
    inline TextureCompilation(Enum value):value(value) {}
    inline TextureCompilation(const TextureCompilation &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "RelativePath",
        "AbsolutePath",
        "Embedded",
    };
    inline TextureCompilation(const String &name)
    {
        if (name == "RelativePath") { value = RelativePath; return; }
        if (name == "AbsolutePath") { value = AbsolutePath; return; }
        if (name == "Embedded") { value = Embedded; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TextureCompilation::RelativePath:
        {
            return Names[0];
        }
        case TextureCompilation::AbsolutePath:
        {
            return Names[1];
        }
        case TextureCompilation::Embedded:
        {
            return Names[2];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::TextureCompilation &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::TextureCompilation &output) { output = LegacyClassGen::TextureCompilation(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
