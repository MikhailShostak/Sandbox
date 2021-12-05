#pragma once
#include "AJSON.h"

#include "Serializable.h"

template<typename T>
inline AJSONValue toJSONValue(const T &value)
{
    if constexpr (std::is_base_of<Serializable, T>::value)
    {
        AJSONObject v;
        const_cast<T &>(value).serialize(v);
        return v;
    }
    else
    {
        return value;
    }
}

template<typename T>
inline void fromJSONValue(const AJSONValue &value, T &output)
{
    static_assert(std::is_base_of<Serializable, T>::value, "T is not implemented for serialization. Specialize the function or add Serializable interface");

    if (value.isObject())
    {
        output.deserialize(value.asObject());
    }
}

template<>
inline AJSONValue toJSONValue<AJSONObject>(const AJSONObject &value)
{
    return value;
}

template<>
inline void fromJSONValue<AJSONObject>(const AJSONValue &value, AJSONObject &output)
{
    output = value.toObject();
}

template<typename T>
inline AJSONValue toJSONValue(const SharedReference<T> &value)
{
    AJSONObject v;
    const_cast<T &>(*value).serialize(v);
    return v;
}

template<typename T>
inline void fromJSONValue(const AJSONValue &value, SharedReference<T> &output)
{
    if (value.isObject())
    {
        SharedReference<T> output = std::make_shared<T>();
        output->deserialize(value.asObject());
    }
}

template<typename T>
inline AJSONValue toJSONValue(const WeakReference<T> &value)
{
    return AJSONValue();
}

template<typename T>
inline void fromJSONValue(const AJSONValue &value, WeakReference<T> &output)
{

}

template<>
inline void fromJSONValue(const AJSONValue &value, bool &output)
{
    output = value.toBoolean();
}

template<>
inline void fromJSONValue(const AJSONValue &value, uint8_t &output)
{
    output = uint8_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, int8_t &output)
{
    output = int8_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, uint16_t &output)
{
    output = uint16_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, int16_t &output)
{
    output = int16_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, uint32_t &output)
{
    output = uint32_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, int32_t &output)
{
    output = int32_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, uint64_t &output)
{
    output = uint64_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, int64_t &output)
{
    output = int64_t(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, float &output)
{
    output = float(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, double &output)
{
    output = double(value.toNumber());
}

template<>
inline void fromJSONValue(const AJSONValue &value, String &output)
{
    output = value.toString();
}

template<>
inline AJSONValue toJSONValue<APath>(const APath &value)
{
    return value.toUnixPathString();
}

template<>
inline void fromJSONValue<APath>(const AJSONValue &value, APath &output)
{
    output = value.toString();
}

template<>
inline AJSONValue toJSONValue(const Array<String> &value)
{
    return AJSONArray(value);
}

template<>
inline void fromJSONValue(const AJSONValue &value, Array<String> &output)
{
    AJSONArray a = value.toArray();
    for (auto &v : a)
    {
        if (!v.isString())
        {
            continue;
        }

        output.push_back(v.asString());
    }
}

#include <Math>

template<>
inline AJSONValue toJSONValue(const Math::IntegerVector &value)
{
    AJSONObject o;
    o.insert("X", value.x);
    o.insert("Y", value.y);
    o.insert("Z", value.z);
    o.insert("W", value.w);
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::IntegerVector &output)
{
    AJSONObject o = value.toObject();
    o.read("X", output.x);
    o.read("Y", output.y);
    o.read("Z", output.z);
    o.read("W", output.w);
}

template<>
inline AJSONValue toJSONValue(const Math::FloatVector &value)
{
    AJSONObject o;
    o.insert("X", value.x);
    o.insert("Y", value.y);
    o.insert("Z", value.z);
    o.insert("W", value.w);
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::FloatVector &output)
{
    AJSONObject o = value.toObject();
    o.read("X", output.x);
    o.read("Y", output.y);
    o.read("Z", output.z);
    o.read("W", output.w);
}

template<>
inline AJSONValue toJSONValue(const Math::DoubleVector &value)
{
    AJSONObject o;
    o.insert("X", value.x);
    o.insert("Y", value.y);
    o.insert("Z", value.z);
    o.insert("W", value.w);
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::DoubleVector &output)
{
    AJSONObject o = value.toObject();
    o.read("X", output.x);
    o.read("Y", output.y);
    o.read("Z", output.z);
    o.read("W", output.w);
}

template<>
inline AJSONValue toJSONValue(const Math::Quaternion &value)
{
    AJSONObject o;
    o.insert("X", value.x);
    o.insert("Y", value.y);
    o.insert("Z", value.z);
    o.insert("W", value.w);
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::Quaternion &output)
{
    AJSONObject o = value.toObject();
    o.read("X", output.x);
    o.read("Y", output.y);
    o.read("Z", output.z);
    o.read("W", output.w);
}

template<>
inline AJSONValue toJSONValue(const Math::FloatRectangle &value)
{
    AJSONObject o;
    o.insert("Position", toJSONValue(value.Position));
    o.insert("Size", toJSONValue(value.Size));
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::FloatRectangle &output)
{
    AJSONObject o = value.toObject();
    AJSONValue position;
    o.read("Position", position);
    fromJSONValue(position, output.Position);

    AJSONValue rotation;
    o.read("Size", rotation);
    fromJSONValue(rotation, output.Size);
}

template<>
inline AJSONValue toJSONValue(const Math::DoubleRectangle &value)
{
    AJSONObject o;
    o.insert("Position", toJSONValue(value.Position));
    o.insert("Size", toJSONValue(value.Size));
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::DoubleRectangle &output)
{
    AJSONObject o = value.toObject();
    AJSONValue position;
    o.read("Position", position);
    fromJSONValue(position, output.Position);

    AJSONValue rotation;
    o.read("Size", rotation);
    fromJSONValue(rotation, output.Size);
}


template<>
inline AJSONValue toJSONValue(const Math::IntegerRectangle &value)
{
    AJSONObject o;
    o.insert("Position", toJSONValue(value.Position));
    o.insert("Size", toJSONValue(value.Size));
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::IntegerRectangle &output)
{
    AJSONObject o = value.toObject();
    AJSONValue position;
    o.read("Position", position);
    fromJSONValue(position, output.Position);

    AJSONValue rotation;
    o.read("Size", rotation);
    fromJSONValue(rotation, output.Size);
}

template<>
inline AJSONValue toJSONValue(const Math::Transform &value)
{
    AJSONObject o;
    o.insert("Position", toJSONValue(value.Position));
    o.insert("Rotation", toJSONValue(value.Rotation));
    return o;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Math::Transform &output)
{
    AJSONObject o = value.toObject();
    AJSONValue position;
    o.read("Position", position);
    fromJSONValue(position, output.Position);

    AJSONValue rotation;
    o.read("Rotation", rotation);
    fromJSONValue(rotation, output.Rotation);
}

inline AJSONValue toJSONValue(const Math::RotationOrder &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Math::RotationOrder &output) { output = Math::RotationOrder(value.toString()); }

template<>
inline AJSONValue toJSONValue<Math::FloatOffsets>(const Math::FloatOffsets &value)
{
    AJSONObject object;
    object.insert("Top", value.top);
    object.insert("Right", value.right);
    object.insert("Bottom", value.bottom);
    object.insert("Left", value.left);
    return object;
}

template<>
inline AJSONValue toJSONValue<Math::DoubleOffsets>(const Math::DoubleOffsets &value)
{
    AJSONObject object;
    object.insert("Top", value.top);
    object.insert("Right", value.right);
    object.insert("Bottom", value.bottom);
    object.insert("Left", value.left);
    return object;
}

template<>
inline AJSONValue toJSONValue<Math::IntegerOffsets>(const Math::IntegerOffsets &value)
{
    AJSONObject object;
    object.insert("Top", value.top);
    object.insert("Right", value.right);
    object.insert("Bottom", value.bottom);
    object.insert("Left", value.left);
    return object;
}

template<>
inline void fromJSONValue<Math::FloatOffsets>(const AJSONValue &value, Math::FloatOffsets &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &object = value.asObject();

    object.read("Top", output.top);
    object.read("Right", output.right);
    object.read("Bottom", output.bottom);
    object.read("Left", output.left);
}

template<>
inline void fromJSONValue<Math::DoubleOffsets>(const AJSONValue &value, Math::DoubleOffsets &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &object = value.asObject();

    object.read("Top", output.top);
    object.read("Right", output.right);
    object.read("Bottom", output.bottom);
    object.read("Left", output.left);
}

template<>
inline void fromJSONValue<Math::IntegerOffsets>(const AJSONValue &value, Math::IntegerOffsets &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &object = value.asObject();

    object.read("Top", output.top);
    object.read("Right", output.right);
    object.read("Bottom", output.bottom);
    object.read("Left", output.left);
}

template<>
inline AJSONValue toJSONValue<AColor>(const AColor &value)
{
    AJSONObject object;
    object.insert("Red", value.Red);
    object.insert("Green", value.Green);
    object.insert("Blue", value.Blue);
    object.insert("Alpha", value.Alpha);
    return object;
}

template<>
inline void fromJSONValue<AColor>(const AJSONValue &value, AColor &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &object = value.asObject();

    object.read("Red", output.Red);
    object.read("Green", output.Green);
    object.read("Blue", output.Blue);
    object.read("Alpha", output.Alpha);
}

template<typename T>
inline AJSONValue toJSONValue(const Array<T> &values)
{
    AJSONArray data;
    data.reserve(values.size());
    for (const T &item : values)
    {
        data.push_back(toJSONValue(item));
    }
    return data;
}

template<typename T>
inline void fromJSONValue(const AJSONValue &value, Array<T> &output)
{
    if (!value.isArray())
    {
        return;
    }

    const AJSONArray &data = value.asArray();
    output.reserve(data.size()); //TODO: resize?
    for (const AJSONValue &item : data)
    {
        T outputItem{};
        fromJSONValue(item, outputItem);
        output.push_back(outputItem);
    }
}

template<typename T>
inline AJSONValue toJSONValue(const OrderedDictionary<String, T> &values)
{
    AJSONObject data;
    for (const auto &pair : values)
    {
        data.insert(pair.first, toJSONValue(pair.second));
    }
    return data;
}

template<typename T>
inline void fromJSONValue(const AJSONValue &value, OrderedDictionary<String, T> &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &data = value.asObject();
    for (const auto &pair : data)
    {
        T outputItem{};
        fromJSONValue(pair.second, outputItem);
        output.insert({ pair.first, outputItem });
    }
}

template<typename T>
inline AJSONValue toJSONValue(const UnorderedDictionary<String, T> &values)
{
    AJSONObject data;
    for (const auto &pair : values)
    {
        data.insert(pair.first, toJSONValue(pair.second));
    }
    return data;
}

template<typename T>
inline void fromJSONValue(const AJSONValue &value, UnorderedDictionary<String, T> &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &data = value.asObject();
    for (const auto &pair : data)
    {
        T outputItem{};
        fromJSONValue(pair.second, outputItem);
        output.insert({ pair.first, outputItem });
    }
}
