#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: EnumerationHeader
class TestEnum
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Test1,
        Test2,
    };
    Enum value = Test1;
    TestEnum();
    inline TestEnum(Enum value):value(value) {}
    inline TestEnum(const TestEnum &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Test1",
        "Test2",
    };
    inline TestEnum(const String &name)
    {
        if (name == "Test1") { value = Test1; return; }
        if (name == "Test2") { value = Test2; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TestEnum::Test1:
        {
            return Names[0];
        }
        case TestEnum::Test2:
        {
            return Names[1];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
inline AJSONValue toJSONValue(const ::TestEnum &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, ::TestEnum &output) { output = ::TestEnum(value.toString()); }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
