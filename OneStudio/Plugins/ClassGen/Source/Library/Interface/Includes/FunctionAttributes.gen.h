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

//CLASSGEN GENERATED REGION: FlagsHeader
class FunctionAttributes
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlagsBody
public:
    enum Enum
    {
        Abstract = 0x1,
        Constant = 0x2,
    };
    size_t value = 0;
    FunctionAttributes();
    inline FunctionAttributes(size_t value):value(value) {}
    inline FunctionAttributes(Enum value):value(size_t(value)) {}
    inline explicit operator size_t() const { return size_t(value); }
    inline explicit operator bool() const { return bool(value); }
    static constexpr const char *Names[] =
    {
        "Abstract",
        "Constant",
    };
    inline Array<String> toStrings() const
    {
        Array<String> strings;
        if (value & FunctionAttributes::Abstract) { strings.push_back(Names[0]); }
        if (value & FunctionAttributes::Constant) { strings.push_back(Names[1]); }
        return strings;
    }
    inline FunctionAttributes(const String &flags)
    {
        Array<String> data;
        boost::split(data, flags, boost::is_any_of("|"));
        if (ranges::find(data, "Abstract") != data.end()) { value |= Abstract; }
        if (ranges::find(data, "Constant") != data.end()) { value |= Constant; }
    }
    inline String toString() const { return boost::join(toStrings(), "|"); }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Operators
inline FunctionAttributes operator |(FunctionAttributes::Enum l, FunctionAttributes::Enum r) { return size_t(l) | size_t(r); }
inline FunctionAttributes operator |(FunctionAttributes::Enum l, FunctionAttributes r) { return size_t(l) | r.value; }
inline FunctionAttributes operator |(FunctionAttributes l, FunctionAttributes::Enum r) { return l.value | size_t(r); }
inline FunctionAttributes operator |(FunctionAttributes l, FunctionAttributes r) { return l.value | r.value; }
inline FunctionAttributes &operator |=(FunctionAttributes &l, FunctionAttributes::Enum r) { l.value = l.value | size_t(r); return l; }
inline FunctionAttributes &operator |=(FunctionAttributes &l, FunctionAttributes r) { l.value = l.value | r.value; return l; }
inline FunctionAttributes operator &(FunctionAttributes::Enum l, FunctionAttributes::Enum r) { return size_t(l) & size_t(r); }
inline FunctionAttributes operator &(FunctionAttributes::Enum l, FunctionAttributes r) { return size_t(l) & r.value; }
inline FunctionAttributes operator &(FunctionAttributes l, FunctionAttributes::Enum r) { return l.value & size_t(r); }
inline FunctionAttributes operator &(FunctionAttributes l, FunctionAttributes r) { return l.value & r.value; }
inline FunctionAttributes &operator &=(FunctionAttributes &l, FunctionAttributes::Enum r) { l.value = l.value & size_t(r); return l; }
inline FunctionAttributes &operator &=(FunctionAttributes &l, FunctionAttributes r) { l.value = l.value & r.value; return l; }
inline FunctionAttributes operator ^(FunctionAttributes::Enum l, FunctionAttributes::Enum r) { return size_t(l) ^ size_t(r); }
inline FunctionAttributes operator ^(FunctionAttributes::Enum l, FunctionAttributes r) { return size_t(l) ^ r.value; }
inline FunctionAttributes operator ^(FunctionAttributes l, FunctionAttributes::Enum r) { return l.value ^ size_t(r); }
inline FunctionAttributes operator ^(FunctionAttributes l, FunctionAttributes r) { return l.value ^ r.value; }
inline FunctionAttributes &operator ^=(FunctionAttributes &l, FunctionAttributes::Enum r) { l.value = l.value ^ size_t(r); return l; }
inline FunctionAttributes &operator ^=(FunctionAttributes &l, FunctionAttributes r) { l.value = l.value ^ r.value; return l; }
inline FunctionAttributes operator ~(FunctionAttributes::Enum v) { v = FunctionAttributes::Enum(size_t(~v)); return v; }
inline FunctionAttributes operator ~(FunctionAttributes v) { v.value = ~v.value; return v; }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::FunctionAttributes &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::FunctionAttributes &output) { output = LegacyClassGen::FunctionAttributes(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
