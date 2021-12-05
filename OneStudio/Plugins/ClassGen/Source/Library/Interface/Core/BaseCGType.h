#pragma once

#include <Data>

#include "Includes/BlockFlags.gen.h"
#include "Includes/VisibilityType.gen.h"
#include "Includes/CGTypeGroup.gen.h"
#include "Includes/TypeInfo.gen.h"

namespace LegacyClassGen
{

String getNextIdentifier();

struct GenerationSettings : public ASingleton<GenerationSettings>
{
    Map<String, APath> filesDirectory;
public:

    bool forceGenerate = false;
    bool forceOverwrite = false;
    String currentPackage;

    const APath &getFilesDirectory(const String &extension) const
    {
        return filesDirectory.at(extension);
    }

    void setFilesDirectory(const String &extension, const APath &path)
    {
        filesDirectory[extension] = path;
    }

    APath resolveFilePath(const APath &path) const
    {
        auto it = filesDirectory.find(path.extension());
        if (it != filesDirectory.end())
        {
            //TODO: move to api?
            auto redirectPath = [](const APath &thisPath, const APath &path)
            {
                return path.isRelative() ? (thisPath.directory() + path) + thisPath.name() : path + thisPath.name();
            };
            return redirectPath(path, it->second);
        }

        return path;
    }
};

static const constexpr char HexMap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

inline void serializeFile(const APath &sourceFilePath, const ADelegate<void(const String &text)> callback, const String &indent = "    ", size_t bytesPerLine = 16)
{
    AFile sourceFile;
    if (!sourceFile.open(sourceFilePath, AFileOpenMode::ReadBinary))
    {
        return;
    }

    uint8_t byte = 0;
    char hexValue[] = { '0', 'x', '0', '0', '\0' };

    auto printByte = [&] {
        byte = sourceFile.take();
        hexValue[2] = HexMap[byte / 16];
        hexValue[3] = HexMap[byte % 16];
        callback(hexValue);
    };

    printByte();

    size_t i = 1;
    while (!sourceFile.atEnd())
    {
        if (!(bytesPerLine < 0) && (i % bytesPerLine) == 0)
        {
            callback(",\r\n");
            callback(indent);
            i = 0;
        }
        else
        {
            callback(", ");
        }
        printByte();
        ++i;
    }
}

inline String serializeFile(const APath &sourceFilePath, const String &indent = "    ", size_t bytesPerLine = 16)
{
    String result;
    serializeFile(sourceFilePath, [&](const String &text) {
        result.append(text);
    }, indent, bytesPerLine);
    return result;
}

class BaseCGType : public AObject
{
protected:
    String generatedRegionMark = "//CLASSGEN GENERATED REGION: ";
    String endRegionMark = "//CLASSGEN END REGION";
    String voidType = "void";
    String indent;
    String defaultIndent = "    ";
    Stack<String> regionsStack;

    AFile file;
    ADelegate<void(const String &data)> write;

    static String resolveType(const String &type)
    {
        return boost::replace_all_copy(type, ".", "::");
    }

    static Array<String> resolveTypes(const Array<String> &types)
    {
        Array<String> result;
        result.reserve(types.size());
        for (const String &type : types)
        {
            result.push_back(boost::replace_all_copy(type, ".", "::"));
        }
        return result;
    }

    static String addTemplateParameters(const String &type, const Array<String> &parameters)
    {
        if (parameters.empty())
        {
            return type;
        }

        return type + "<" + boost::join(parameters, ", ") + ">";
    }

    static void addDependencies(const BaseCGType &type, Array<String> &dependencies);
    static void addDependencies(const String &typeName, Array<String> &dependencies);
    static void addDependencies(const Array<String> &typeNames, Array<String> &dependencies);

    void pushIndent()
    {
        indent.append(defaultIndent);
    }

    void popIndent()
    {
        indent = indent.substr(0, indent.size() - defaultIndent.size());
    }

    void pushRegion(const String &region)
    {
        regionsStack.push_back(region);
    }

    void popRegion()
    {
        regionsStack.pop_back();
    }

public:
    APath path;
    XMLNode root;
    AJSONObject data;
    CGTypeGroup group;
    String package;

    Array<String> buffers;

    void pushBuffer()
    {
        buffers.push_back(std::move(generatedBuffer));
        generatedBuffer.clear();
    }

    String popBuffer()
    {
        String temp = std::move(generatedBuffer);
        generatedBuffer = std::move(buffers.back());
        buffers.pop_back();
        return temp;
    }

    String generatedBuffer;

    BaseCGType()
    {
        write = [&](const String &data) {
            generatedBuffer.append(data);
        };
        regionsStack.push_back(String()); //HACK:: added for preventing a lot of checks
    }

    bool isInternal() const { return LegacyClassGen::GenerationSettings::getInstance().currentPackage == package; }
    bool isExternal() const { return !isInternal(); }
    virtual Array<String> getImportFiles() const { return { isExternal() ? package : (path.baseName() + ".gen.h") }; }

    String flush()
    {
        String buffer = std::move(generatedBuffer);
        clear();
        return buffer;
    }

    void clear()
    {
        generatedBuffer.clear();
    }

    virtual ~BaseCGType() {}

    Array<String> Dependencies;

    virtual void parse() {}
    virtual void collectDependencies()
    {
        Dependencies.clear();

        addDependencies(getBaseType(), Dependencies);
    }

    virtual String getBaseType() const
    {
        String type;
        data.read("BaseType", type);
        return type;
    }

    virtual String getNamespace() const
    {
        String namespaceName;
        data.read("Namespace", namespaceName);
        return namespaceName;
    }

    virtual String getDefaultType(bool resolved = false) const
    {
        String namespaceName = getNamespace();
        return !namespaceName.empty() ? namespaceName + (resolved ? "::" : ".") + path.baseName() : path.baseName();
    }

    virtual String createNewInstance(const String &type, const Array<String> &arguments) const
    {
        return "Create<" + type + ">(" + boost::join(arguments, ", ") + ")";
    }

    String createNewInstance(const String &type) const
    {
        return createNewInstance(type, {});
    }

    String createNewInstance(const Array<String> &arguments = {}) const
    {
        return createNewInstance(getDefaultType(true), arguments);
    }

    virtual void generate() = 0;

    virtual String generateInitialization(const LegacyClassGen::TypeInfo &typeInfo, const AJSONValue &value, const String &indent, const String &variableName, Array<String> &dependencies)
    {
        return value.toString();
    }

    void writeFile(const APath &path, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        generatedBuffer.clear();
        bool hasRegions = false;
        bool hasContent = false;
        if (!GenerationSettings::getInstance().forceGenerate)
        {
            APathInfo sourceInfo(this->path);
            APathInfo pathInfo(path);
            if (sourceInfo.isExists() && pathInfo.isExists() && sourceInfo.modificationTime() <= pathInfo.modificationTime())
            {
                return;
            }
        }

        if (file.open(path, AFileOpenMode::ReadBinary))
        {
            hasContent = size_t(file.readSize()) > 0;
            //TODO: add reserve
            //generatedBuffer.reserve(file.readSize());
            while (!file.atEnd())
            {
                auto l = file.readLine();
                const String line(l.begin(), l.end());
                write(line);
                write("\n");
                if (line.find_first_of(generatedRegionMark) == 0)
                {
                    for (auto &pair : regions)
                    {
                        const size_t startIndex = generatedRegionMark.size();
                        const size_t endIndex = startIndex + pair.first.size();

                        if (line.find_first_of(pair.first, startIndex) == startIndex && (line.size() == endIndex - 1 || !std::isalnum(line[endIndex])))
                        {
                            hasRegions = true;
                            pair.second();

                            while (!file.atEnd())
                            {
                                auto l2 = file.readLine();
                                const String line(l2.begin(), l2.end());
                                if (line.find_first_of(endRegionMark) == 0)
                                {
                                    write(endRegionMark);
                                    write("\r\n");
                                    break;
                                }
                            }

                            break;
                        }
                    }
                }
            }
            file.close();
        }

        //We want to keep a user file if it exists and doesn't have generated regions
        if (!hasContent || hasRegions || GenerationSettings::getInstance().forceOverwrite)
        {
            if (file.open(path, AFileOpenMode::WriteBinary))
            {
                if (!hasRegions)
                {
                    generatedBuffer.clear();
                    implementation();
                }
                file << generatedBuffer;
                file.close();
            }
        }
        generatedBuffer.clear();
    }

    void writeFile2(const APath& path, const Array<APair<String, ADelegate<void()>>>& regions)
    {
        //skip if updated
        if (!GenerationSettings::getInstance().forceGenerate)
        {
            APathInfo sourceInfo(this->path);
            APathInfo pathInfo(path);
            if (sourceInfo.isExists() && pathInfo.isExists() && sourceInfo.modificationTime() <= pathInfo.modificationTime())
            {
                return;
            }
        }

        generatedBuffer.clear();
        size_t regionIndex = 0;

        //update regions
        if (file.open(path, AFileOpenMode::ReadBinary))
        {
            //TODO: add reserve
            //generatedBuffer.reserve(file.readSize());
            while (!file.atEnd())
            {
                auto l = file.readLine();
                const String line(l.begin(), l.end());
                if (line.find_first_of(generatedRegionMark) == 0)
                {
                    bool expectedRegion = [&]() {
                        if (regionIndex >= regions.size())
                        {
                            return false;
                        }

                        auto pair = regions[regionIndex];

                        const size_t startIndex = generatedRegionMark.size();
                        const size_t endIndex = startIndex + pair.first.size();

                        return line.find_first_of(pair.first, startIndex) == startIndex && (line.size() == endIndex - 1 || !std::isalnum(line[endIndex]));
                    }();

                    while (!file.atEnd())
                    {
                        auto l2 = file.readLine();
                        const String line(l2.begin(), l2.end());
                        if (line.find_first_of(endRegionMark) == 0)
                        {
                            if (expectedRegion)
                            {
                                generateRegion(regions[regionIndex].first, regions[regionIndex].second);
                                ++regionIndex;
                            }
                            break;
                        }
                    }
                }
                else
                {
                    write(line);
                    write("\n");
                }
            }
            file.close();
        }

        //push new regions
        for (; regionIndex < regions.size(); ++regionIndex)
        {
            generateRegion(regions[regionIndex].first, regions[regionIndex].second);
        }

        if (file.open(path, AFileOpenMode::WriteBinary))
        {
            file << generatedBuffer;
            file.close();
        }
        generatedBuffer.clear();
    }

    void writeGeneratedFile2(const String& extension, const Array<APair<String, ADelegate<void()>>>& regions)
    {
        writeFile2(GenerationSettings::getInstance().resolveFilePath(path.resolveWithExtension("gen." + extension)), regions);
    }
    
    void writeGeneratedFile(const String &extension, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeFile(GenerationSettings::getInstance().resolveFilePath(path.resolveWithExtension("gen." + extension)), implementation, regions);
    }

    void writeHeaderFile(const Array<String> &globalIncludes, const Array<String> &localIncludes, const String &namespaceName, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeGeneratedFile("h", [&]() {
            pushRegion("Includes");
            generateHeader(globalIncludes, localIncludes);
            if (!globalIncludes.empty() || !localIncludes.empty())
            {
                write("\r\n");
            }
            popRegion();
            pushRegion("Namespace");
            generateInsideNamespaceIfNeeded(namespaceName, implementation);
            popRegion();
        }, regions);
    }

    void writeHeaderFile(const Array<String> &globalIncludes, const Array<String> &localIncludes, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeHeaderFile(globalIncludes, localIncludes, String(), implementation, regions);
    }

    void writeHeaderFile(const Array<String> &globalIncludes, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeHeaderFile(globalIncludes, {}, String(), implementation, regions);
    }

    void writeHeaderFile(const String &namespaceName, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeHeaderFile({}, {}, namespaceName, implementation, regions);
    }

    void writeHeaderFile(const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeHeaderFile({}, {}, String(), implementation, regions);
    }

    void writeSourceFile(bool includeHeader, const Array<String> &globalIncludes, const Array<String> &localIncludes, const String &namespaceName, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeGeneratedFile("cpp", [&]() {
            if (includeHeader)
            {
                pushRegion("Includes");
                generateSource(includeHeader, globalIncludes, localIncludes);
                popRegion();
            }
            pushRegion("Namespace");
            generateInsideNamespaceIfNeeded(namespaceName, implementation);
            popRegion();
        }, regions);
    }

    void writeSourceFile(bool includeHeader, const Array<String> &globalIncludes, const Array<String> &localIncludes, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeSourceFile(includeHeader, globalIncludes, localIncludes, String(), implementation, regions);
    }

    void writeSourceFile(bool includeHeader, const Array<String> &globalIncludes, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeSourceFile(includeHeader, globalIncludes, {}, String(), implementation, regions);
    }

    void writeSourceFile(bool includeHeader, const String &namespaceName, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeSourceFile(includeHeader, {}, {}, namespaceName, implementation, regions);
    }

    void writeSourceFile(bool includeHeader, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeSourceFile(includeHeader, {}, {}, String(), implementation, regions);
    }

    void writeSourceFile(const String &namespaceName, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeSourceFile(true, {}, {}, namespaceName, implementation, regions);
    }

    void writeSourceFile(const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeSourceFile(true, {}, {}, String(), implementation, regions);
    }

    void writeInlineFile(const String &namespaceName, const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeGeneratedFile("inl", [&]() {
            generateInsideNamespaceIfNeeded(namespaceName, implementation);
        }, regions);
    }

    void writeInlineFile(const ADelegate<void()> &implementation, const Map<String, ADelegate<void()>> &regions = Map<String, ADelegate<void()>>())
    {
        writeInlineFile(String(), implementation, regions);
    }

    void writeIndent()
    {
        write(indent);
    }

    void writeWithIndent(const String &data)
    {
        writeIndent();
        write(data);
    }

    void generateRegion(const String &regionName, const ADelegate<void()> &implementation)
    {
        write(generatedRegionMark);
        write(regionName);
        write("\r\n");
        implementation();
        write(endRegionMark);
        write("\r\n");
    }

    void generateRegionIfNeeded(const String &regionName, const ADelegate<void()> &implementation)
    {
        if (!regionName.empty())
        {
            generateRegion(regionName, implementation);
        }
        else
        {
            implementation();
        }
    }

    void generateRegionIfNeeded(const ADelegate<void()> &implementation)
    {
        generateRegionIfNeeded(regionsStack.back(), implementation);
    }

    void generateDefine(const String &name, const String &value = String())
    {
        if (!value.empty())
        {
            write("#define " + name + " " + value);
        }
        else
        {
            write("#define " + name);
        }
    }

    void generateInclude(const String &path, bool global)
    {
        if (global)
        {
            write("#include <" + path + ">\r\n");
        }
        else
        {
            write("#include \"" + path + "\"\r\n");
        }
    }

    void generateIncludes(const Array<String> &globalIncludes, const Array<String> &localIncludes = Array<String>())
    {
        if (!globalIncludes.empty())
        {
            for (const auto &include : globalIncludes)
            {
                generateInclude(include, true);
            }
            write("\r\n");
        }
        if (!localIncludes.empty())
        {
            for (const auto &include : localIncludes)
            {
                generateInclude(include, false);
            }
            write("\r\n");
        }
    }

    void generateHeader(const Array<String> &globalIncludes, const Array<String> &localIncludes = Array<String>())
    {
        write("#pragma once\r\n\r\n");
        generateRegionIfNeeded([&]() {
            generateIncludes(globalIncludes, localIncludes);
        });
    }

    void generateHeaderInclude()
    {
        generateInclude(path.baseName() + ".gen.h", false);
    }

    void generateSource(bool includeHeader, const Array<String> &globalIncludes, const Array<String> &localIncludes = Array<String>())
    {
        if (includeHeader)
        {
            generateRegionIfNeeded([&]() {
                generateHeaderInclude();
            });
            write("\r\n");
        }
        generateIncludes(globalIncludes, localIncludes);
    }

    void generateAlias(const String &name, const String &type)
    {
        writeWithIndent(fmt::format("typedef {} {};\r\n", type, name));
    }

    void generateDefaultClassAliases(const String &thisType, const String &superType, const Array<String> &interfaces)
    {
        generateVisiblityScope(VisibilityType::Public, [&]() {
            generateAlias("This", thisType);
            generateAlias("Super", !superType.empty() ? superType : voidType);
            generateAlias("Interfaces", !interfaces.empty() ? fmt::format("std::tuple<{}>", boost::join(interfaces, ", ")) : voidType);
        });
    }

    void generateBlock(const ADelegate<void()> &implementation, BlockFlags flags = BlockFlags())
    {
        auto addBegin = [&]() {
            if (flags & BlockFlags::SkipBraces)
            {
                return;
            }
            if (flags & BlockFlags::Compact)
            {
                write("{");
            }
            else
            {
                writeWithIndent("{\r\n");
            }
        };

        auto addEnd = [&]() {
            if (flags & BlockFlags::SkipBraces)
            {
                return;
            }
            auto t = flags & BlockFlags::CompleteWithSemicolon ? "};\r\n" : "}\r\n";
            if (flags & BlockFlags::Compact)
            {
                write(t);
            }
            else
            {
                writeWithIndent(t);
            }
        };

        if (flags & BlockFlags::AddRegions)
        {
            generateRegionIfNeeded(regionsStack.back() + "Begin", addBegin);
        }
        else
        {
            addBegin();
        }

        if (flags & BlockFlags::AddEmptyLines)
        {
            write("\r\n");
        }
        if (flags & BlockFlags::AddIndents)
        {
            pushIndent();
        }
        implementation();
        if (flags & BlockFlags::AddIndents)
        {
            popIndent();
        }
        if (flags & BlockFlags::AddEmptyLines)
        {
            write("\r\n");
        }

        if (flags & BlockFlags::AddRegions)
        {
            generateRegionIfNeeded(regionsStack.back() + "End", addEnd);
        }
        else
        {
            addEnd();
        }
    }

    void generateBranch(const String &condition, const ADelegate<void()> &trueImplementation, const ADelegate<void()> &elseImplementation = ADelegate<void()>())
    {
        writeWithIndent("if (");
        write(condition);
        write(")\r\n");
        generateBlock(trueImplementation, BlockFlags::AddIndents);
        if (elseImplementation)
        {
            writeWithIndent("else");
            generateBlock(elseImplementation, BlockFlags::AddIndents);
        }
    }

    void generatePreProcessorBranch(const String &condition, const ADelegate<void()> &trueImplementation, const ADelegate<void()> &elseImplementation = ADelegate<void()>())
    {
        write("#if ");
        write(condition);
        write("\r\n");
        trueImplementation();
        if (elseImplementation)
        {
            write("#else\r\n");
            elseImplementation();
        }
        write("#endif //");
        write(condition);
        write("\r\n");
    }

    void generateNamespaceWithoutBlock(const String &name)
    {
        writeWithIndent(fmt::format("namespace {}\r\n", name));
    }

    void generateNamespace(const String &name, const ADelegate<void()> &implementation)
    {
        generateRegionIfNeeded([&]() {
            generateNamespaceWithoutBlock(name);
        });
        generateBlock(implementation, BlockFlags::AddEmptyLines | BlockFlags::AddRegions);
    }

    void generateInsideNamespaceIfNeeded(const String &namespaceName, const ADelegate<void()> &implementation)
    {
        if (!namespaceName.empty())
        {
            generateNamespace(namespaceName, implementation);
        }
        else
        {
            generateBlock(implementation, BlockFlags::AddRegions | BlockFlags::SkipBraces);
        }
    }

    void generateTemplate(const Array<String> &types)
    {
        writeWithIndent("template<");
        Array<String> typenames;
        for (const String &type : types)
        {
            typenames.push_back("typename " + type);
        }
        write(boost::join(typenames, ", "));
        write(">");
        write("\r\n");
    }

    void generateEntity(const String &metaClass, const String &name = String(), const String &baseType = String(), const Array<String> &interfaces = {})
    {
        writeWithIndent(metaClass);
        if (!name.empty())
        {
            write(" ");
            write(name);
        }
        if (!baseType.empty() || !interfaces.empty())
        {
            write(" : public ");
        }
        if (!baseType.empty())
        {
            write(baseType);
            if (!interfaces.empty())
            {
                write(", public ");
            }
        }
        if (!interfaces.empty())
        {
            write(boost::join(interfaces, ", public "));
        }
        write("\r\n");
    }

    void generateEntity(const String &metaClass, const String &name, const String &baseType, const Array<String> &interfaces, const ADelegate<void()> &implementation)
    {
        generateRegionIfNeeded(!regionsStack.back().empty() ? regionsStack.back() + "Header" : String(), [&]() {
            generateEntity(metaClass, name, baseType, interfaces);
        });
        generateBlock([&]() {
            generateRegionIfNeeded(!regionsStack.back().empty() ? regionsStack.back() + "Body" : String(), [&]() {
                implementation();
            });
        }, BlockFlags::CompleteWithSemicolon);
    }

    void generateStructureWithoutBlock(const String &name, const String &baseType, const Array<String> &interfaces)
    {
        generateEntity("struct", name, baseType, interfaces);
    }

    void generateStructure(const String &name, const String &baseType, const Array<String> &interfaces, const ADelegate<void()> &implementation)
    {
        generateEntity("struct", name, baseType, interfaces, implementation);
    }

    void generateClassWithoutBlock(const String &name, const String &baseType, const Array<String> &interfaces)
    {
        generateEntity("class", name, baseType, interfaces);
    }

    void generateClass(const String &name, const String &baseType, const Array<String> &interfaces, const ADelegate<void()> &implementation)
    {
        generateEntity("class", name, baseType, interfaces, implementation);
    }

    void generateVisiblityScope(VisibilityType visibilityType, const ADelegate<void()> &implementation)
    {
        write(boost::to_lower_copy(visibilityType.toString()) + ":\r\n");
        pushIndent();
        implementation();
        popIndent();
    }

    void generateEnumeration(const String &name, const Array<String> &values)
    {
        generateRegionIfNeeded(!regionsStack.back().empty() ? regionsStack.back() + "Header" : String(), [&]() {
            generateEntity("enum", name);
        });

        generateBlock([&]() {
            generateRegionIfNeeded(!regionsStack.back().empty() ? regionsStack.back() + "Values" : String(), [&]() {
                for (const auto &value : values)
                {
                    writeWithIndent(value + ",\r\n");
                }
            });
        }, BlockFlags::AddIndents | BlockFlags::CompleteWithSemicolon);
    }

    void generateEnumerationClass(const String &name, const Array<String> &values)
    {
        generateEnumeration("class " + name, values);
    }

    void generateFunction(const String &returnType, const String &name, const Array<String> arguments, const ADelegate<void()> &implementation = nullptr, bool constant = false, bool isVirtual = false, bool isInline = false, bool compact = false)
    {
        writeWithIndent(fmt::format("{}{}({})", (isVirtual ? "virtual " : "" ) + (!returnType.empty() ? returnType + " " : String()), name, boost::join(arguments, ", ")));
        if (constant)
        {
            write(" const");
        }
        if (implementation)
        {
            if (!compact)
            {
                write("\r\n");
            }
            generateBlock(implementation, compact ? BlockFlags::AddIndents | BlockFlags::Compact : BlockFlags::AddIndents);
        }
        else if (isVirtual)
        {
            write(" = 0;\r\n");
        }
        else
        {
            write(";\r\n");
        }
    }

    void generateConstructor(const String &name, const Array<String> arguments, const ADelegate<void()> &implementation = nullptr)
    {
        generateFunction(String(), name, arguments, implementation, false);
    }

    void generateDestructor(const String &name, const ADelegate<void()> &implementation = nullptr, bool isVirtual = false)
    {
        generateFunction(String(), "~" + name, {}, implementation ? implementation : []() {}, false, isVirtual, false, !implementation);
    }

    void generateMethodImplementation(const String &returnType, const String &className, const String &methodName, const Array<String> arguments, const ADelegate<void()> &implementation, bool constant = false)
    {
        generateFunction(returnType, !className.empty() ? (className + "::" + methodName) : methodName, arguments, implementation, constant);
    }

    void generateConstructorImplementation(const String &name, const Array<String> arguments, const ADelegate<void()> &implementation = nullptr)
    {
        generateMethodImplementation(String(), name, name, arguments, implementation);
    }

    void generateField(const String &type, const String &name, const String &defaultValue = String())
    {
        if (!defaultValue.empty())
        {
            writeWithIndent(fmt::format("{} {} = {};\r\n", type, name, defaultValue));
        }
        else
        {
            writeWithIndent(fmt::format("{} {};\r\n", type, name));
        }
    }

    void generateSwitch(const String &value, const String &caseNamespace, const Array<String> &cases, const ADelegate<void(const String &value, size_t index)> &implementation, const ADelegate<void()> &defaultImplementation = nullptr)
    {
        writeWithIndent(fmt::format("switch ({})\r\n", value));
        generateBlock([&]() {
            for (size_t i = 0; i < cases.size(); ++i)
            {
                writeWithIndent("case ");
                if (!caseNamespace.empty())
                {
                    write(caseNamespace + "::");
                }
                write(cases[i]);
                write(":\r\n");
                generateBlock([&]() {
                    implementation(cases[i], i);
                }, BlockFlags::AddIndents);
            }
            if (defaultImplementation)
            {
                writeWithIndent("default:\r\n");
                generateBlock([&]() {
                    defaultImplementation();
                });
            }
        });
    }

    void generateReturn(const String &field)
    {
        writeWithIndent(fmt::format("return {};\r\n", field));
    }

    void generateAssignment(const String &field, const String &value)
    {
        writeWithIndent(fmt::format("{} = {};\r\n", field, value));
    }

    void generateMovement(const String &field, const String &value)
    {
        writeWithIndent(fmt::format("{} = std::move({});\r\n", field, value));
    }

    void generateCall(const String &function, const Array<String> &arguments, const Array<String> &templateParameters = {})
    {
        if (!templateParameters.empty())
        {
            writeWithIndent(fmt::format("{}<{}>({});\r\n", function, boost::join(templateParameters, ", "), boost::join(arguments, ", ")));
        }
        else
        {
            writeWithIndent(fmt::format("{}({});\r\n", function, boost::join(arguments, ", ")));
        }
    }

    void generateClassCall(const String &type, const String &function, const Array<String> &arguments, const Array<String> &templateParameters = {})
    {
        generateCall(type + "::" + function, arguments, templateParameters);
    }

    void generateSuperCall(const String &function, const Array<String> &arguments, const Array<String> &templateParameters = {})
    {
        generateClassCall("Super", function, arguments, templateParameters);
    }

    void generatePropertyMethods(const String &type, const String &name, bool readOnly = false, bool isVirtual = false)
    {
        generateFunction(type, "get" + name, {}, nullptr, true, isVirtual);
        if (!readOnly)
        {
            generateFunction(voidType, "set" + name, { type + " const &" + name }, nullptr, false, isVirtual);
            generateFunction(voidType, "set" + name, { type + " &&" + name }, nullptr, false, isVirtual);
        }
    }

    void generatePropertyImplementation(const String &type, const String &className, const String &propertyName, const Array<String> &preCallbacks, const Array<String> &postCallbacks, bool readOnly = false)
    {
        generateMethodImplementation(type, className, "get" + propertyName, {}, [&]() {
            generateReturn("this->" + propertyName);
        }, true);
        if (!readOnly)
        {
            generateMethodImplementation(voidType, className, "set" + propertyName, { type + " const &" + propertyName }, [&]() {
                //writeWithIndent("if (this->" + propertyName +" == " + propertyName + ") return;\r\n");
                for (const auto &preCallback : preCallbacks)
                {
                    generateCall(preCallback, {});
                }
                generateAssignment("this->" + propertyName, propertyName);
                for (const auto &postCallback : postCallbacks)
                {
                    generateCall(postCallback, {});
                }
            });
            generateMethodImplementation(voidType, className, "set" + propertyName, { type + " &&" + propertyName }, [&]() {
                //writeWithIndent("if (this->" + propertyName + " == " + propertyName + ") return;\r\n");
                for (const auto &preCallback : preCallbacks)
                {
                    generateCall(preCallback, {});
                }
                generateMovement("this->" + propertyName, propertyName);
                for (const auto &postCallback : postCallbacks)
                {
                    generateCall(postCallback, {});
                }
            });
        }
    }

    void generatePropertyImplementation(const String &type, const String &className, const String &propertyName, const Array<String> &postCallbacks = {})
    {
        generatePropertyImplementation(type, className, propertyName, {}, postCallbacks);
    }

    void processProperties(const String &variable, const LegacyClassGen::BaseCGType *typeData, const AJSONObject &values, Array<String> &dependencies);
};

}
