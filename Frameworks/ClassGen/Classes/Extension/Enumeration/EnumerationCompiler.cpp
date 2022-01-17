namespace ClassGen
{

void EnumerationCompiler::Compile(const SharedReference<ClassGen::BaseInfo>& BaseInfo, const System::Path& OutputFilePath)
{
    auto e = DynamicCast<ClassGen::EnumerationInfo>(BaseInfo);
    if (!e)
    {
        return;
    }
    auto &enumInfo = *e;
    if (enumInfo.Values.empty())
    {
        return;
    }

    auto enumName = OutputFilePath.stem().generic_string();
    auto enumNamespace = boost::replace_all_copy(enumInfo.Namespace, ".", "::");
    auto enumFullName = !enumNamespace.empty() ? (enumNamespace + "::" + enumName) : (enumName);
    std::ofstream file;
    file.open(OutputFilePath.generic_string(), std::ios::binary);
    fmt::print("Write: {}\n", OutputFilePath.generic_string());
    file << "#pragma once\n";
    file << "\n";
    if (!enumNamespace.empty())
    {
        file << "namespace " << enumNamespace << "\n";
        file << "{\n";
    }
    
    file << "enum class " << enumName << "\n";
    file << "{\n";

    //TODO: optimize
    auto fileInfo = FindClassByName(enumName, enumNamespace);
    const bool isFlags = fileInfo.Type == "Flags";

    if (isFlags)
    {
        size_t i = 0;
        for (const auto& value : enumInfo.Values)
        {
            if (i == 0)
            {
                file << "    " << value << " = 0,\n";
            }
            else
            {
                file << "    " << value << " = 1 << " << i << ",\n";
            }
            ++i;
        }
    }
    else //enum
    {
        for (auto& value : enumInfo.Values)
        {
            file << "    " << value << ",\n";
        }
    }
    file << "};\n";

    if (isFlags)
    {
        file << "DECLARE_FLAG_OPERATORS(" << enumFullName << ")\n";
    }

    if (!enumNamespace.empty())
    {
        file << "}\n";
    }

    file <<
R"(
namespace Serialization
{
template<>
struct Serializer<InputValue, )" << enumFullName << R"(>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (data.m_Storage.IsScalar())
        {
            const auto &valueName = data.m_Storage.template as<std::string>();
)";
    if (isFlags)
    {
        file <<
"            const Array<String> values = Str::Split(valueName, String(\"|\"));\n" <<
"            value = " << enumFullName << "::" << enumInfo.Values[0] << ";\n";
        for (auto& v : enumInfo.Values)
        {
            file <<
"            if (ranges::find(values, \"" << v << "\") != values.end()) { value |= " << enumFullName << "::" << v << "; }\n";
        }
    }
    else
    {
        for (auto& v : enumInfo.Values)
        {
            file <<
"            if (valueName == \"" << v << "\") { value = " << enumFullName << "::" << v << "; return; }\n";
        }
        file <<
"            value = " << enumFullName << "::" << enumInfo.Values[0] << ";\n";
    }
    file <<
        R"(
        }
    }
};

template<>
struct Serializer<OutputValue, )" << enumFullName << R"(>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {
)";

if (isFlags)
{
    file <<
"        Array<String> strings;\n";
    for (auto& v : enumInfo.Values)
    {
        file <<
"        if (bool(value & " << enumFullName << "::" << v << ")) { strings.push_back(\"" << v << "\"); }\n";
    }
    file <<
"        data.m_Storage = Str::Join(strings, String(\"|\"));\n";
}
else
{
file <<
R"(
        switch(value)
        {
)";
    for (auto& v : enumInfo.Values)
    {
        file <<
"        case " << enumFullName << "::" << v << ": data.m_Storage = \"" << v << "\"; return;\n";
    }
    file <<
"        }\n";
}
    file <<
R"(
    }
};

}
)";
}

}
