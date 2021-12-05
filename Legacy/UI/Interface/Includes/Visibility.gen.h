#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <AData>

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: FlagsHeader
class Visibility
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlagsBody
public:
    enum Enum
    {
        SelfHidden = 0x1,
        ChildrenHidden = 0x2,
        SelfInactive = 0x4,
        ChildrenInactive = 0x8,
        SelfDisabled = 0x10,
        ChildrenDisabled = 0x20,
        SelfCollapsed = 0x40,
        ChildrenCollapsed = 0x80,
    };
    size_t value = 0;
    Visibility();
    inline Visibility(size_t value):value(value) {}
    inline Visibility(Enum value):value(size_t(value)) {}
    inline explicit operator size_t() const { return size_t(value); }
    inline explicit operator bool() const { return bool(value); }
    static constexpr const char *Names[] =
    {
        "SelfHidden",
        "ChildrenHidden",
        "SelfInactive",
        "ChildrenInactive",
        "SelfDisabled",
        "ChildrenDisabled",
        "SelfCollapsed",
        "ChildrenCollapsed",
    };
    inline Array<String> toStrings() const
    {
        Array<String> strings;
        if (value & Visibility::SelfHidden) { strings.push_back(Names[0]); }
        if (value & Visibility::ChildrenHidden) { strings.push_back(Names[1]); }
        if (value & Visibility::SelfInactive) { strings.push_back(Names[2]); }
        if (value & Visibility::ChildrenInactive) { strings.push_back(Names[3]); }
        if (value & Visibility::SelfDisabled) { strings.push_back(Names[4]); }
        if (value & Visibility::ChildrenDisabled) { strings.push_back(Names[5]); }
        if (value & Visibility::SelfCollapsed) { strings.push_back(Names[6]); }
        if (value & Visibility::ChildrenCollapsed) { strings.push_back(Names[7]); }
        return strings;
    }
    inline Visibility(const String &flags)
    {
        Array<String> data;
        boost::split(data, flags, boost::is_any_of("|"));
        if (ranges::find(data, "SelfHidden") != data.end()) { value |= SelfHidden; }
        if (ranges::find(data, "ChildrenHidden") != data.end()) { value |= ChildrenHidden; }
        if (ranges::find(data, "SelfInactive") != data.end()) { value |= SelfInactive; }
        if (ranges::find(data, "ChildrenInactive") != data.end()) { value |= ChildrenInactive; }
        if (ranges::find(data, "SelfDisabled") != data.end()) { value |= SelfDisabled; }
        if (ranges::find(data, "ChildrenDisabled") != data.end()) { value |= ChildrenDisabled; }
        if (ranges::find(data, "SelfCollapsed") != data.end()) { value |= SelfCollapsed; }
        if (ranges::find(data, "ChildrenCollapsed") != data.end()) { value |= ChildrenCollapsed; }
    }
    inline String toString() const { return boost::join(toStrings(), "|"); }
//CLASSGEN END REGION
    constexpr static Enum Hidden = Enum(size_t(SelfHidden) | size_t(ChildrenHidden));
    constexpr static Enum Inactive = Enum(size_t(SelfInactive) | size_t(ChildrenInactive));
    constexpr static Enum Disabled = Enum(size_t(SelfDisabled) | size_t(ChildrenDisabled));
    constexpr static Enum Collapsed = Enum(size_t(SelfCollapsed) | size_t(ChildrenCollapsed));
};
//CLASSGEN GENERATED REGION: Operators
inline Visibility operator |(Visibility::Enum l, Visibility::Enum r) { return size_t(l) | size_t(r); }
inline Visibility operator |(Visibility::Enum l, Visibility r) { return size_t(l) | r.value; }
inline Visibility operator |(Visibility l, Visibility::Enum r) { return l.value | size_t(r); }
inline Visibility operator |(Visibility l, Visibility r) { return l.value | r.value; }
inline Visibility &operator |=(Visibility &l, Visibility::Enum r) { l.value = l.value | size_t(r); return l; }
inline Visibility &operator |=(Visibility &l, Visibility r) { l.value = l.value | r.value; return l; }
inline Visibility operator &(Visibility::Enum l, Visibility::Enum r) { return size_t(l) & size_t(r); }
inline Visibility operator &(Visibility::Enum l, Visibility r) { return size_t(l) & r.value; }
inline Visibility operator &(Visibility l, Visibility::Enum r) { return l.value & size_t(r); }
inline Visibility operator &(Visibility l, Visibility r) { return l.value & r.value; }
inline Visibility &operator &=(Visibility &l, Visibility::Enum r) { l.value = l.value & size_t(r); return l; }
inline Visibility &operator &=(Visibility &l, Visibility r) { l.value = l.value & r.value; return l; }
inline Visibility operator ^(Visibility::Enum l, Visibility::Enum r) { return size_t(l) ^ size_t(r); }
inline Visibility operator ^(Visibility::Enum l, Visibility r) { return size_t(l) ^ r.value; }
inline Visibility operator ^(Visibility l, Visibility::Enum r) { return l.value ^ size_t(r); }
inline Visibility operator ^(Visibility l, Visibility r) { return l.value ^ r.value; }
inline Visibility &operator ^=(Visibility &l, Visibility::Enum r) { l.value = l.value ^ size_t(r); return l; }
inline Visibility &operator ^=(Visibility &l, Visibility r) { l.value = l.value ^ r.value; return l; }
inline Visibility operator ~(Visibility::Enum v) { v = Visibility::Enum(size_t(~v)); return v; }
inline Visibility operator ~(Visibility v) { v.value = ~v.value; return v; }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const UI::Visibility &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, UI::Visibility &output) { output = UI::Visibility(value.toString()); }
namespace UI {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
