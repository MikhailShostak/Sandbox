#pragma once

#include "Serialization/Serializer.hpp"

using Float2 = hlslpp::float2;
using Float3 = hlslpp::float3;
using Float4 = hlslpp::float4;

using Int2 = hlslpp::int2;
using Int3 = hlslpp::int3;
using Int4 = hlslpp::int4;

namespace Serialization
{

template<>
struct ObjectSerializer<Int2>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.i32[0];
        data["y"] & value.i32[1];
    }
};

template<>
struct ObjectSerializer<Int3>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.i32[0];
        data["y"] & value.i32[1];
        data["z"] & value.i32[2];
    }
};

template<>
struct ObjectSerializer<Int4>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.i32[0];
        data["y"] & value.i32[1];
        data["z"] & value.i32[2];
        data["w"] & value.i32[3];
    }
};

template<>
struct ObjectSerializer<Float2>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.f32[0];
        data["y"] & value.f32[1];
    }
};

template<>
struct ObjectSerializer<Float3>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.f32[0];
        data["y"] & value.f32[1];
        data["z"] & value.f32[2];
    }
};

template<>
struct ObjectSerializer<Float4>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        data["x"] & value.f32[0];
        data["y"] & value.f32[1];
        data["z"] & value.f32[2];
        data["w"] & value.f32[3];
    }
};

}
