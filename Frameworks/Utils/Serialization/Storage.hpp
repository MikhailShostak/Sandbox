#pragma once

namespace Serialization
{

//TODO: support different data formats/backends
struct Data
{
    YAML::Node m_Storage;

    void FromString(const std::string &string)
    {
        m_Storage = YAML::Load(string);
    }

    bool FromFile(const std::filesystem::path &path)
    {
        if (!std::filesystem::is_regular_file(path))
        {
            return false;
        }

        m_Storage = YAML::LoadFile(path.generic_string());
        return true;
    }

    std::string ToString() const
    {
        YAML::Emitter out;
        out << m_Storage;
        return out.c_str();
    }

    bool ToFile(const std::filesystem::path &path) const
    {
        std::ofstream file;
        file.open(path, std::ios::binary);
        if (!file.is_open())
        {
            return false;
        }

        file << ToString();
        return true;
    }
};

//TODO: separate specialization tag may be a little bit safe
struct InputValue : public Data {};
struct OutputValue : public Data {};

//TODO: can this extra map be avoided?
template<typename ValueType>
struct Map
{
    ValueType &operator [](const std::string &key)
    {
        return m_Data[key];
    }

    std::map<std::string, ValueType> m_Data;
};

using InputMap = Map<InputValue>;
using OutputMap = Map<OutputValue>;

}
