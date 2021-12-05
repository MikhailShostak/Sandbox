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
class PropertyAttributes
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlagsBody
public:
    enum Enum
    {
        ReadOnly = 0x1,
        Abstract = 0x2,
        Replicated = 0x4,
        Serialized = 0x8,
        Mapped = 0x10,
    };
    size_t value = 0;
    PropertyAttributes();
    inline PropertyAttributes(size_t value):value(value) {}
    inline PropertyAttributes(Enum value):value(size_t(value)) {}
    inline explicit operator size_t() const { return size_t(value); }
    inline explicit operator bool() const { return bool(value); }
    static constexpr const char *Names[] =
    {
        "ReadOnly",
        "Abstract",
        "Replicated",
        "Serialized",
        "Mapped",
    };
    inline Array<String> toStrings() const
    {
        Array<String> strings;
        if (value & PropertyAttributes::ReadOnly) { strings.push_back(Names[0]); }
        if (value & PropertyAttributes::Abstract) { strings.push_back(Names[1]); }
        if (value & PropertyAttributes::Replicated) { strings.push_back(Names[2]); }
        if (value & PropertyAttributes::Serialized) { strings.push_back(Names[3]); }
        if (value & PropertyAttributes::Mapped) { strings.push_back(Names[4]); }
        return strings;
    }
    inline PropertyAttributes(const String &flags)
    {
        Array<String> data;
        boost::split(data, flags, boost::is_any_of("|"));
        if (ranges::find(data, "ReadOnly") != data.end()) { value |= ReadOnly; }
        if (ranges::find(data, "Abstract") != data.end()) { value |= Abstract; }
        if (ranges::find(data, "Replicated") != data.end()) { value |= Replicated; }
        if (ranges::find(data, "Serialized") != data.end()) { value |= Serialized; }
        if (ranges::find(data, "Mapped") != data.end()) { value |= Mapped; }
    }
    inline String toString() const { return boost::join(toStrings(), "|"); }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Operators
inline PropertyAttributes operator |(PropertyAttributes::Enum l, PropertyAttributes::Enum r) { return size_t(l) | size_t(r); }
inline PropertyAttributes operator |(PropertyAttributes::Enum l, PropertyAttributes r) { return size_t(l) | r.value; }
inline PropertyAttributes operator |(PropertyAttributes l, PropertyAttributes::Enum r) { return l.value | size_t(r); }
inline PropertyAttributes operator |(PropertyAttributes l, PropertyAttributes r) { return l.value | r.value; }
inline PropertyAttributes &operator |=(PropertyAttributes &l, PropertyAttributes::Enum r) { l.value = l.value | size_t(r); return l; }
inline PropertyAttributes &operator |=(PropertyAttributes &l, PropertyAttributes r) { l.value = l.value | r.value; return l; }
inline PropertyAttributes operator &(PropertyAttributes::Enum l, PropertyAttributes::Enum r) { return size_t(l) & size_t(r); }
inline PropertyAttributes operator &(PropertyAttributes::Enum l, PropertyAttributes r) { return size_t(l) & r.value; }
inline PropertyAttributes operator &(PropertyAttributes l, PropertyAttributes::Enum r) { return l.value & size_t(r); }
inline PropertyAttributes operator &(PropertyAttributes l, PropertyAttributes r) { return l.value & r.value; }
inline PropertyAttributes &operator &=(PropertyAttributes &l, PropertyAttributes::Enum r) { l.value = l.value & size_t(r); return l; }
inline PropertyAttributes &operator &=(PropertyAttributes &l, PropertyAttributes r) { l.value = l.value & r.value; return l; }
inline PropertyAttributes operator ^(PropertyAttributes::Enum l, PropertyAttributes::Enum r) { return size_t(l) ^ size_t(r); }
inline PropertyAttributes operator ^(PropertyAttributes::Enum l, PropertyAttributes r) { return size_t(l) ^ r.value; }
inline PropertyAttributes operator ^(PropertyAttributes l, PropertyAttributes::Enum r) { return l.value ^ size_t(r); }
inline PropertyAttributes operator ^(PropertyAttributes l, PropertyAttributes r) { return l.value ^ r.value; }
inline PropertyAttributes &operator ^=(PropertyAttributes &l, PropertyAttributes::Enum r) { l.value = l.value ^ size_t(r); return l; }
inline PropertyAttributes &operator ^=(PropertyAttributes &l, PropertyAttributes r) { l.value = l.value ^ r.value; return l; }
inline PropertyAttributes operator ~(PropertyAttributes::Enum v) { v = PropertyAttributes::Enum(size_t(~v)); return v; }
inline PropertyAttributes operator ~(PropertyAttributes v) { v.value = ~v.value; return v; }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::PropertyAttributes &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::PropertyAttributes &output) { output = LegacyClassGen::PropertyAttributes(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
