#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Math
    //CLASSGEN END REGION
    //CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class RotationOrder
    //CLASSGEN END REGION
{
    //CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX,
    };
    Enum value = XYZ;
    RotationOrder();
    inline RotationOrder(Enum value):value(value) {}
    inline RotationOrder(const RotationOrder &value) : value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "XYZ",
        "XZY",
        "YXZ",
        "YZX",
        "ZXY",
        "ZYX",
    };
    inline RotationOrder(const String &name)
    {
        if (name == "XYZ") { value = XYZ; return; }
        if (name == "XZY") { value = XZY; return; }
        if (name == "YXZ") { value = YXZ; return; }
        if (name == "YZX") { value = YZX; return; }
        if (name == "ZXY") { value = ZXY; return; }
        if (name == "ZYX") { value = ZYX; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case RotationOrder::XYZ:
        {
            return Names[0];
        }
        case RotationOrder::XZY:
        {
            return Names[1];
        }
        case RotationOrder::YXZ:
        {
            return Names[2];
        }
        case RotationOrder::YZX:
        {
            return Names[3];
        }
        case RotationOrder::ZXY:
        {
            return Names[4];
        }
        case RotationOrder::ZYX:
        {
            return Names[5];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const Math::RotationOrder &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Math::RotationOrder &output) { output = Math::RotationOrder(value.toString()); }
namespace Math {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
