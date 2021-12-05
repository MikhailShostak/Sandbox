#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: FlagsHeader
class KeyModifier
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlagsBody
public:
    enum Enum
    {
        Alt = 0x1,
        Ctrl = 0x2,
        Shift = 0x4,
        Win = 0x8,
    };
    size_t value = 0;
    KeyModifier();
    inline KeyModifier(size_t value):value(value) {}
    inline KeyModifier(Enum value):value(size_t(value)) {}
    inline explicit operator size_t() const { return size_t(value); }
    inline explicit operator bool() const { return bool(value); }
    static constexpr const char *Names[] =
    {
        "Alt",
        "Ctrl",
        "Shift",
        "Win",
    };
    inline Array<String> toStrings() const
    {
        Array<String> strings;
        if (value & KeyModifier::Alt) { strings.push_back(Names[0]); }
        if (value & KeyModifier::Ctrl) { strings.push_back(Names[1]); }
        if (value & KeyModifier::Shift) { strings.push_back(Names[2]); }
        if (value & KeyModifier::Win) { strings.push_back(Names[3]); }
        return strings;
    }
    inline KeyModifier(const String &flags)
    {
        Array<String> data;
        boost::split(data, flags, boost::is_any_of("|"));
        if (ranges::find(data, "Alt") != data.end()) { value |= Alt; }
        if (ranges::find(data, "Ctrl") != data.end()) { value |= Ctrl; }
        if (ranges::find(data, "Shift") != data.end()) { value |= Shift; }
        if (ranges::find(data, "Win") != data.end()) { value |= Win; }
    }
    inline String toString() const { return boost::join(toStrings(), "|"); }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Operators
inline KeyModifier operator |(KeyModifier::Enum l, KeyModifier::Enum r) { return size_t(l) | size_t(r); }
inline KeyModifier operator |(KeyModifier::Enum l, KeyModifier r) { return size_t(l) | r.value; }
inline KeyModifier operator |(KeyModifier l, KeyModifier::Enum r) { return l.value | size_t(r); }
inline KeyModifier operator |(KeyModifier l, KeyModifier r) { return l.value | r.value; }
inline KeyModifier &operator |=(KeyModifier &l, KeyModifier::Enum r) { l.value = l.value | size_t(r); return l; }
inline KeyModifier &operator |=(KeyModifier &l, KeyModifier r) { l.value = l.value | r.value; return l; }
inline KeyModifier operator &(KeyModifier::Enum l, KeyModifier::Enum r) { return size_t(l) & size_t(r); }
inline KeyModifier operator &(KeyModifier::Enum l, KeyModifier r) { return size_t(l) & r.value; }
inline KeyModifier operator &(KeyModifier l, KeyModifier::Enum r) { return l.value & size_t(r); }
inline KeyModifier operator &(KeyModifier l, KeyModifier r) { return l.value & r.value; }
inline KeyModifier &operator &=(KeyModifier &l, KeyModifier::Enum r) { l.value = l.value & size_t(r); return l; }
inline KeyModifier &operator &=(KeyModifier &l, KeyModifier r) { l.value = l.value & r.value; return l; }
inline KeyModifier operator ^(KeyModifier::Enum l, KeyModifier::Enum r) { return size_t(l) ^ size_t(r); }
inline KeyModifier operator ^(KeyModifier::Enum l, KeyModifier r) { return size_t(l) ^ r.value; }
inline KeyModifier operator ^(KeyModifier l, KeyModifier::Enum r) { return l.value ^ size_t(r); }
inline KeyModifier operator ^(KeyModifier l, KeyModifier r) { return l.value ^ r.value; }
inline KeyModifier &operator ^=(KeyModifier &l, KeyModifier::Enum r) { l.value = l.value ^ size_t(r); return l; }
inline KeyModifier &operator ^=(KeyModifier &l, KeyModifier r) { l.value = l.value ^ r.value; return l; }
inline KeyModifier operator ~(KeyModifier::Enum v) { v = KeyModifier::Enum(size_t(~v)); return v; }
inline KeyModifier operator ~(KeyModifier v) { v.value = ~v.value; return v; }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const Core::KeyModifier &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Core::KeyModifier &output) { output = Core::KeyModifier(value.toString()); }
namespace Core {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
