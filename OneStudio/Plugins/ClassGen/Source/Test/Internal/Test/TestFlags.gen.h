#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: FlagsHeader
class TestFlags
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlagsBody
public:
    enum Enum
    {
        Test1 = 0x1,
        Test2 = 0x2,
    };
    size_t value = 0;
    TestFlags();
    inline TestFlags(size_t value):value(value) {}
    inline TestFlags(Enum value):value(size_t(value)) {}
    inline explicit operator size_t() const { return size_t(value); }
    inline explicit operator bool() const { return bool(value); }
    static constexpr const char *Names[] =
    {
        "Test1",
        "Test2",
    };
    inline Array<String> toStrings() const
    {
        Array<String> strings;
        if (value & TestFlags::Test1) { strings.push_back(Names[0]); }
        if (value & TestFlags::Test2) { strings.push_back(Names[1]); }
        return strings;
    }
    inline TestFlags(const String &flags)
    {
        Array<String> data = flags.split('|');
        if (data.indexOf("Test1") != size_t(-1)) { value |= Test1; }
        if (data.indexOf("Test2") != size_t(-1)) { value |= Test2; }
    }
    inline String toString() const { return String::join(toStrings(), "|"); }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Operators
inline TestFlags operator |(TestFlags::Enum l, TestFlags::Enum r) { return size_t(l) | size_t(r); }
inline TestFlags operator |(TestFlags::Enum l, TestFlags r) { return size_t(l) | r.value; }
inline TestFlags operator |(TestFlags l, TestFlags::Enum r) { return l.value | size_t(r); }
inline TestFlags operator |(TestFlags l, TestFlags r) { return l.value | r.value; }
inline TestFlags &operator |=(TestFlags &l, TestFlags::Enum r) { l.value = l.value | size_t(r); return l; }
inline TestFlags &operator |=(TestFlags &l, TestFlags r) { l.value = l.value | r.value; return l; }
inline TestFlags operator &(TestFlags::Enum l, TestFlags::Enum r) { return size_t(l) & size_t(r); }
inline TestFlags operator &(TestFlags::Enum l, TestFlags r) { return size_t(l) & r.value; }
inline TestFlags operator &(TestFlags l, TestFlags::Enum r) { return l.value & size_t(r); }
inline TestFlags operator &(TestFlags l, TestFlags r) { return l.value & r.value; }
inline TestFlags &operator &=(TestFlags &l, TestFlags::Enum r) { l.value = l.value & size_t(r); return l; }
inline TestFlags &operator &=(TestFlags &l, TestFlags r) { l.value = l.value & r.value; return l; }
inline TestFlags operator ^(TestFlags::Enum l, TestFlags::Enum r) { return size_t(l) ^ size_t(r); }
inline TestFlags operator ^(TestFlags::Enum l, TestFlags r) { return size_t(l) ^ r.value; }
inline TestFlags operator ^(TestFlags l, TestFlags::Enum r) { return l.value ^ size_t(r); }
inline TestFlags operator ^(TestFlags l, TestFlags r) { return l.value ^ r.value; }
inline TestFlags &operator ^=(TestFlags &l, TestFlags::Enum r) { l.value = l.value ^ size_t(r); return l; }
inline TestFlags &operator ^=(TestFlags &l, TestFlags r) { l.value = l.value ^ r.value; return l; }
inline TestFlags operator ~(TestFlags::Enum v) { v = TestFlags::Enum(size_t(~v)); return v; }
inline TestFlags operator ~(TestFlags v) { v.value = ~v.value; return v; }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Serialization
inline AJSONValue toJSONValue(const ::TestFlags &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, ::TestFlags &output) { output = ::TestFlags(value.toString()); }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
