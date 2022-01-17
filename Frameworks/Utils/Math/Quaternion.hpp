#pragma once

#include "Serialization/Serializer.hpp"

using Quaternion = hlslpp::quaternion;

namespace Serialization
{

template<>
struct ObjectSerializer<Quaternion>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.f32[0];
        data["y"] & value.f32[1];
        data["z"] & value.f32[1];
        data["w"] & value.f32[1];
    }
};

}
