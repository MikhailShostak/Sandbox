namespace ClassGen
{

void ClassCompiler::Compile(const SharedReference<ClassGen::BaseInfo>& BaseInfo, const System::Path& OutputFilePath)
{
    auto c = DynamicCast<ClassGen::ClassInfo>(BaseInfo);
    if (!c)
    {
        return;
    }
    auto &classInfo = *c;

    bool isStruct = ranges::contains(classInfo.Attributes, "Structure");
    auto className = OutputFilePath.stem().generic_string();
    auto classNamespace = boost::replace_all_copy(classInfo.Namespace, ".", "::");
    auto classBaseType = writeRecursivelyResolved(classInfo.BaseType);
    std::ofstream file;
    file.open(OutputFilePath.generic_string(), std::ios::binary);
    fmt::print("Write: {}\n", OutputFilePath.generic_string());
    file << "#pragma once\n";
    file << "\n";
    if (!classNamespace.empty())
    {
        file << "namespace " << classNamespace << "\n";
        file << "{\n";
    }
    if (!classInfo.TemplateTypes.empty())
    {
        file << "template<";
        file << (classInfo.TemplateTypes | ranges::views::transform([](String& name) { return "typename " + name; }) | ranges::views::cache1 | ranges::views::join(',') | ranges::to<String>());
        file << ">\n";
    }
    file << "struct " << className << "\n";
    if (!classInfo.BaseType.Name.empty())
    {
        file << "    : public " << classBaseType << "\n";
    }
    file << "{\n";
    file << "    using This = " << className << ";\n";
    if (!classInfo.BaseType.Name.empty())
    {
        file << "    using Super = " << classBaseType << ";\n";
    }
    for (const auto& p : classInfo.Properties)
    {
        file << "    " << writeRecursivelyResolved(p.Type) << " " << p.Name << ";\n";
    }


    bool hasCustomDefaultConstructor = ranges::contains(classInfo.Attributes, "DefaultConstructor");
    if (hasCustomDefaultConstructor)
    {
        file << "    " << className << "();\n";
    }

    if (ranges::contains(classInfo.Attributes, "Copy"))
    {
        if (!hasCustomDefaultConstructor)
        {
            file << "    " << className << "() = default;\n";
            hasCustomDefaultConstructor = true;
        }
        file << "    " << className << "(const " << className << " &other);\n";
        file << "    " << className << " &operator =(const " << className << " &other);\n";
    }
    else if (ranges::contains(classInfo.Attributes, "DefaultCopy"))
    {
        if (!hasCustomDefaultConstructor)
        {
            file << "    " << className << "() = default;\n";
            hasCustomDefaultConstructor = true;
        }
        file << "    " << className << "(const " << className << " &other) = default;\n";
        file << "    " << className << " &operator =(const " << className << " &other) = default;\n";
    }
    else if (ranges::contains(classInfo.Attributes, "DeleteCopy"))
    {
        if (!hasCustomDefaultConstructor)
        {
            file << "    " << className << "() = default;\n";
            hasCustomDefaultConstructor = true;
        }
        file << "    " << className << "(const " << className << " &other) = delete;\n";
        file << "    " << className << " &operator =(const " << className << " &other) = delete;\n";
    }

    if (ranges::contains(classInfo.Attributes, "Move"))
    {
        if (!hasCustomDefaultConstructor)
        {
            file << "    " << className << "() = default;\n";
            hasCustomDefaultConstructor = true;
        }
        file << "    " << className << "(" << className << " &&other);\n";
        file << "    " << className << " &operator =(" << className << " &&other);\n";
    }
    else if (ranges::contains(classInfo.Attributes, "DefaultMove"))
    {
        if (!hasCustomDefaultConstructor)
        {
            file << "    " << className << "() = default;\n";
            hasCustomDefaultConstructor = true;
        }
        file << "    " << className << "(" << className << " &&other) = default;\n";
        file << "    " << className << " &operator =(" << className << " &&other) = default;\n";
    }
    else if (ranges::contains(classInfo.Attributes, "DeleteMove"))
    {
        file << "    " << className << "(" << className << " &&other) = delete;\n";
        file << "    " << className << " &operator =(" << className << " &&other) = delete;\n";
    }

    bool hasCustomDestructor = ranges::contains(classInfo.Attributes, "Destructor");
    if (hasCustomDestructor || !isStruct)
    {
        file << "\n";
        file << "    ";
        if (!isStruct)
        {
            file << "virtual";
        }
        file << " ~" << className << "()";
        if (hasCustomDestructor)
        {
            file << ";";
        }
        else
        {
            file << " {}";
        }
    }

    auto indirectType = writeRecursivelyResolved(classInfo.IndirectType);
    if (!indirectType.empty())
    {
        file << "\n";
        file << "protected:\n";
        file << "    " << indirectType << " *GetIndirectValue();\n";
        file << "public:\n";
        file << "    " << indirectType << " &operator*() { return *GetIndirectValue(); }\n";
        file << "    const " << indirectType << " &operator*() const { return *ConstCast<decltype(this)>(this)->GetIndirectValue(); }\n";
        file << "    " << indirectType << " *operator->() { return GetIndirectValue(); }\n";
        file << "    const " << indirectType << " *operator->() const { return ConstCast<decltype(this)>(this)->GetIndirectValue(); }\n";
    }
    file << "\n";
    file << "    template<typename T>\n";
    file << "    void Serialize(T &&data)\n";
    file << "    {\n";
    for (const auto& p : classInfo.Properties)
    {
        if (ranges::contains(p.Attributes, "Serialize"))
        {
            file << "        data[\"" << p.Name << "\"] & " << p.Name << ";\n";
        }
    }
    file << "    }\n";
    for (const ClassGen::EventInfo& e : classInfo.Events)
    {
        if (e.InputParameters.empty())
        {
            file << "    Meta::Function<void> " << e.Name << ";\n";
            continue;
        }

        Array<String> parameters = e.InputParameters | ranges::views::transform([](auto& p)
            {
                auto addReference = [&](const String& name) { return p.Copy ? name : (name + " &"); };
                auto addConst = [&](const String& name) { return p.Writable ? name : ("const " + name); };
                return addConst(addReference(writeRecursivelyResolved(p.Type))) + " /*" + p.Name + "*/";
            }) | ranges::to<Array<String>>();

            file << "    Meta::Function<void, " << boost::join(parameters, ", ") << "> " << e.Name << ";\n";
    }
    for (const ClassGen::FunctionInfo& f : classInfo.Functions)
    {
        Array<String> parameters = f.InputParameters | ranges::views::transform([](auto& p)
            {
                auto addReference = [&](const String& name) { return p.Copy ? name : (name + " &"); };
                auto addConst = [&](const String& name) { return p.Writable ? name : ("const " + name); };
                return addConst(addReference(writeRecursivelyResolved(p.Type))) + " " + p.Name;
            }) | ranges::to<Array<String>>();

            auto resolveReturnType = [&]() -> String
            {
                if (f.OutputParameters.empty())
                {
                    return "void";
                }

                Array<String> parameters = f.OutputParameters | ranges::views::transform([](auto& p) { return writeRecursivelyResolved(p.Type) + "/*" + p.Name + "*/"; }) | ranges::to<Array<String>>();
                return "std::tuple<" + boost::join(parameters, ", ") + ">";
            };

            file << "    virtual " << resolveReturnType() << " " << f.Name << "(" << boost::join(parameters, ", ") << ");\n";
    }
    file << "};\n";

    if (!classNamespace.empty())
    {
        file << "}\n";
    }
}

}
