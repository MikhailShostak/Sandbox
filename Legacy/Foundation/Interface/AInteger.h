#pragma once

class AInteger
{

    Array<uint8_t> data;

public:

    static AInteger Random(size_t size)
    {
        AInteger number;
        number.resize(size);
        number[0] = (rand() % 0xFF) + 1;
        for(size_t i = 1; i < size; ++i)
        {
            number[i] = (rand() % 0xFF) + 1;
        }
        return number;
    }

    static inline AInteger FromBinaryString(const String &string)
    {
        AInteger result;
        result.resize(sizeof(uint64_t));
        result.as<uint64_t>() = std::stoull(string, 0, 2);
        return result;
    }

    static inline AInteger FromOctString(const String &string)
    {
        AInteger result;
        result.resize(sizeof(uint64_t));
        result.as<uint64_t>() = std::stoull(string, 0, 8);
        return result;
    }

    static inline AInteger FromHexString(const String &string)
    {
        AInteger result;
        result.resize(sizeof(uint64_t));
        result.as<uint64_t>() = std::stoull(string, 0, 16);
        return result;
    }

    static inline AInteger FromString(const String &string)
    {
        AInteger result;
        result.resize(sizeof(uint64_t));
        result.as<uint64_t>() = std::stoull(string, 0, 10);
        return result;
    }

    uint8_t getSize() const
    {
        return data.size();
    }

    void clear()
    {
        memset(&data[0], 0, getSize());
    }

    void resize(size_t size)
    {
        data.resize(size);
    }

    template<typename Type>
    Type &as()
    {
        return reinterpret_cast<Type &>(data[0]);
    }

    template<typename Type>
    const Type &as() const
    {
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

    bool operator ==(const AInteger &integer) const
    {
        if(integer.getSize() != getSize())
        {
            return false;
        }

        return memcmp(&data[0], &integer.data[0], getSize()) == 0;
    }

    bool operator !=(const AInteger &integer) const
    {
        if(integer.getSize() != getSize())
        {
            return true;
        }

        return memcmp(&data[0], &integer.data[0], getSize()) != 0;
    }


    String toString(bool skipNullBytes = false) const
    {
        std::stringstream ss;
        if(skipNullBytes)
        {
            for(size_t i = getSize(); i > 0; --i)
            {
                if(data[i - 1] == 0)
                {

                }
                ss << uint16_t(data[i - 1]);
            }
        }
        else
        {
            for(size_t i = getSize(); i > 0; --i)
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
            for(size_t i = getSize(); i > 0; --i)
            {
                if(data[i - 1] == 0)
                {

                }
                ss << std::oct << uint16_t(data[i - 1]);
            }
        }
        else
        {
            for(size_t i = getSize(); i > 0; --i)
            {
                ss << std::oct << uint16_t(data[i - 1]);
            }
        }
        return ss.str();
    }

    String toHexString(bool skipNullBytes = false) const
    {
        std::stringstream ss;
        if(skipNullBytes)
        {
            for(size_t i = getSize(); i > 0; --i)
            {
                if(data[i - 1] == 0)
                {

                }
                ss << std::hex << uint16_t(data[i - 1]);
            }
        }
        else
        {
            for(size_t i = getSize(); i > 0; --i)
            {
                ss << std::hex << uint16_t(data[i - 1]);
            }
        }
        return ss.str();
    }

};

namespace std
{
    template<>
    struct hash<AInteger>
    {
        size_t operator()(const AInteger &integer) const { return std::hash<String>()(integer.toHexString(true)); }
    };
}
