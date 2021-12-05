#pragma once

#include "String.h"

template<size_t size = 4>
class AStaticInteger
{

    uint8_t data[size];

public:

    static AStaticInteger<size> Random()
    {
        AStaticInteger<size> number;
        number[0] = (rand() % 0xFF) + 1;
        for(size_t i = 1; i < size; ++i)
        {
            number[i] = (rand() % 0xFF) + 1;
        }
        return number;
    }

    static inline AStaticInteger<size> FromBinaryString(const String &string)
    {
        uint64_t number = std::stoull(string, 0, 2);
        AStaticInteger<size> result;
        memcpy(&result[0], &number, std::min<size_t>(size, sizeof(number)));
        return result;
    }

    static inline AStaticInteger<size> FromOctString(const String &string)
    {
        uint64_t number = std::stoull(string, 0, 8);
        AStaticInteger<size> result;
        memcpy(&result[0], &number, std::min<size_t>(size, sizeof(number)));
        return result;
    }

    static inline AStaticInteger<size> FromHexString(const String &string)
    {
        uint64_t number = std::stoull(string, 0, 16);
        AStaticInteger<size> result;
        memcpy(&result[0], &number, std::min<size_t>(size, sizeof(number)));
        return result;
    }

    static inline AStaticInteger<size> FromString(const String &string)
    {
        uint64_t number = std::stoull(string, 0, 10);
        AStaticInteger<size> result;
        memcpy(&result[0], &number, std::min<size_t>(size, sizeof(number)));
        return result;
    }

    using IntegerTypes = std::tuple<uint8_t, uint16_t, uint32_t, uint64_t>;
    using MaxIntegerType = typename std::tuple_element<size < std::tuple_size<IntegerTypes>::value ? size : (std::tuple_size<IntegerTypes>::value - 1), IntegerTypes>::type;

    AStaticInteger(MaxIntegerType value = 0)
    {
        as<MaxIntegerType>() = value;
    }

    constexpr size_t getSize() const
    {
        return size;
    }

    void clear()
    {
        memset(data, 0, size);
    }

    template<typename Type>
    Type &as()
    {
        static_assert(sizeof(Type) <= sizeof(data));
        return reinterpret_cast<Type &>(data[0]);
    }

    template<typename Type>
    const Type &as() const
    {
        static_assert(sizeof(Type) <= sizeof(data));
        return reinterpret_cast<const Type &>(data[0]);
    }

    uint8_t &operator [](size_t offset)
    {
        return data[offset];
    }

    const uint8_t &operator [](size_t offset) const
    {
        return data[offset];
    }

    bool operator ==(const AStaticInteger &integer) const
    {
        return memcmp(data, integer.data, size) == 0;
    }

    bool operator !=(const AStaticInteger &integer) const
    {
        return memcmp(data, integer.data, size) != 0;
    }

    String toString(bool skipNullBytes = false) const
    {
        std::stringstream ss;
        if(skipNullBytes)
        {
            for(size_t i = size; i > 0; --i)
            {
                if(data[i - 1] == 0)
                {

                }
                ss << uint16_t(data[i - 1]);
            }
        }
        else
        {
            for(size_t i = size; i > 0; --i)
            {
                ss << uint16_t(data[i - 1]);
            }
        }
        return ss.str();
    }

    String toOctString(bool skipNullBytes = false) const
    {
        std::stringstream ss;
        if(skipNullBytes)
        {
            for(size_t i = size; i > 0; --i)
            {
                if(data[i - 1] == 0)
                {

                }
                ss << std::oct << uint16_t(data[i - 1]);
            }
        }
        else
        {
            for(size_t i = size; i > 0; --i)
            {
                ss << std::oct << uint16_t(data[i - 1]);
            }
        }
        return ss.str();
    }

    String toHexString(bool skipNullBytes = false) const
    {
        std::stringstream ss;
        const size_t LastIndex = size - 1;
        if(skipNullBytes)
        {
            for(size_t i = 0; i < size; ++i)
            {
                if(data[LastIndex - i] < 0x10)
                {
                    ss << "0";
                }
                ss << std::hex << uint16_t(data[LastIndex - i]);
            }
        }
        else
        {
            for(size_t i = 0; i < size; ++i)
            {
                if(data[LastIndex - i] < 0x10)
                {
                    ss << "0";
                }
                ss << std::hex << uint16_t(data[LastIndex - i]);
            }
        }
        return ss.str();
    }

};

using AStaticInteger8 = AStaticInteger<1>;
using AStaticInteger16 = AStaticInteger<2>;
using AStaticInteger32 = AStaticInteger<4>;
using AStaticInteger64 = AStaticInteger<8>;

namespace std
{
    template<size_t size>
    struct hash<AStaticInteger<size>>
    {
        size_t operator()(const AStaticInteger<size> &integer) const { return std::hash<String>()(integer.toHexString(true)); }
    };
}
