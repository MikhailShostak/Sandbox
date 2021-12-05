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
class BlockFlags
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlagsBody
public:
    enum Enum
    {
        AddIndents = 0x1,
        AddEmptyLines = 0x2,
        CompleteWithSemicolon = 0x4,
        SkipBraces = 0x8,
        AddRegions = 0x10,
        Compact = 0x20,
    };
    size_t value = 0;
    BlockFlags();
    inline BlockFlags(size_t value):value(value) {}
    inline BlockFlags(Enum value):value(size_t(value)) {}
    inline explicit operator size_t() const { return size_t(value); }
    inline explicit operator bool() const { return bool(value); }
    static constexpr const char *Names[] =
    {
        "AddIndents",
        "AddEmptyLines",
        "CompleteWithSemicolon",
        "SkipBraces",
        "AddRegions",
        "Compact",
    };
    inline Array<String> toStrings() const
    {
        Array<String> strings;
        if (value & BlockFlags::AddIndents) { strings.push_back(Names[0]); }
        if (value & BlockFlags::AddEmptyLines) { strings.push_back(Names[1]); }
        if (value & BlockFlags::CompleteWithSemicolon) { strings.push_back(Names[2]); }
        if (value & BlockFlags::SkipBraces) { strings.push_back(Names[3]); }
        if (value & BlockFlags::AddRegions) { strings.push_back(Names[4]); }
        if (value & BlockFlags::Compact) { strings.push_back(Names[5]); }
        return strings;
    }
    inline BlockFlags(const String &flags)
    {
        Array<String> data;
        boost::split(data, flags, boost::is_any_of("|"));
        if (ranges::find(data, "AddIndents") != data.end()) { value |= AddIndents; }
        if (ranges::find(data, "AddEmptyLines") != data.end()) { value |= AddEmptyLines; }
        if (ranges::find(data, "CompleteWithSemicolon") != data.end()) { value |= CompleteWithSemicolon; }
        if (ranges::find(data, "SkipBraces") != data.end()) { value |= SkipBraces; }
        if (ranges::find(data, "AddRegions") != data.end()) { value |= AddRegions; }
        if (ranges::find(data, "Compact") != data.end()) { value |= Compact; }
    }
    inline String toString() const { return boost::join(toStrings(), "|"); }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Operators
inline BlockFlags operator |(BlockFlags::Enum l, BlockFlags::Enum r) { return size_t(l) | size_t(r); }
inline BlockFlags operator |(BlockFlags::Enum l, BlockFlags r) { return size_t(l) | r.value; }
inline BlockFlags operator |(BlockFlags l, BlockFlags::Enum r) { return l.value | size_t(r); }
inline BlockFlags operator |(BlockFlags l, BlockFlags r) { return l.value | r.value; }
inline BlockFlags &operator |=(BlockFlags &l, BlockFlags::Enum r) { l.value = l.value | size_t(r); return l; }
inline BlockFlags &operator |=(BlockFlags &l, BlockFlags r) { l.value = l.value | r.value; return l; }
inline BlockFlags operator &(BlockFlags::Enum l, BlockFlags::Enum r) { return size_t(l) & size_t(r); }
inline BlockFlags operator &(BlockFlags::Enum l, BlockFlags r) { return size_t(l) & r.value; }
inline BlockFlags operator &(BlockFlags l, BlockFlags::Enum r) { return l.value & size_t(r); }
inline BlockFlags operator &(BlockFlags l, BlockFlags r) { return l.value & r.value; }
inline BlockFlags &operator &=(BlockFlags &l, BlockFlags::Enum r) { l.value = l.value & size_t(r); return l; }
inline BlockFlags &operator &=(BlockFlags &l, BlockFlags r) { l.value = l.value & r.value; return l; }
inline BlockFlags operator ^(BlockFlags::Enum l, BlockFlags::Enum r) { return size_t(l) ^ size_t(r); }
inline BlockFlags operator ^(BlockFlags::Enum l, BlockFlags r) { return size_t(l) ^ r.value; }
inline BlockFlags operator ^(BlockFlags l, BlockFlags::Enum r) { return l.value ^ size_t(r); }
inline BlockFlags operator ^(BlockFlags l, BlockFlags r) { return l.value ^ r.value; }
inline BlockFlags &operator ^=(BlockFlags &l, BlockFlags::Enum r) { l.value = l.value ^ size_t(r); return l; }
inline BlockFlags &operator ^=(BlockFlags &l, BlockFlags r) { l.value = l.value ^ r.value; return l; }
inline BlockFlags operator ~(BlockFlags::Enum v) { v = BlockFlags::Enum(size_t(~v)); return v; }
inline BlockFlags operator ~(BlockFlags v) { v.value = ~v.value; return v; }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::BlockFlags &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::BlockFlags &output) { output = LegacyClassGen::BlockFlags(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
