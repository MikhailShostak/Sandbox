#pragma once

#include "Core/BaseCGType.h"
#include "Includes/TextureCompilation.gen.h"

namespace LegacyClassGen
{

class TextureCGType : public BaseCGType
{
public:

    static void processAllFiles(const Array<SharedReference<TextureCGType>> &textures, const APath &source)
    {
        const String &package = LegacyClassGen::GenerationSettings::getInstance().currentPackage;
        APathInfo headerFileInfo(source + (package + "Textures.h"));
        APathInfo sourceFileInfo(source + (package + "Textures.cpp"));
        bool needRebuild = false;
        if (headerFileInfo.isExists() && sourceFileInfo.isExists())
        {
            for (auto &texture : textures)
            {
                APathInfo textureFileInfo(texture->path);
                if (textureFileInfo.modificationTime() > sourceFileInfo.modificationTime() || textureFileInfo.modificationTime() > headerFileInfo.modificationTime())
                {
                    ALogMessage("", "%s is newer, need to rebuild %s and %s",
                        textureFileInfo.path().toString(),
                        headerFileInfo.path().toString(),
                        sourceFileInfo.path().toString()
                    );
                    needRebuild = true;
                    break;
                }
            }
        }
        else
        {
            needRebuild = true;
        }

        if (!needRebuild)
        {
            return;
        }

        AFile headerFile;
        AFile sourceFile;
        if (!headerFile.open(headerFileInfo.path(), AFileOpenMode::WriteBinary))
        {
            return;
        }

        if (!sourceFile.open(sourceFileInfo.path(), AFileOpenMode::WriteBinary))
        {
            return;
        }

        headerFile << "#pragma once\r\n\r\n";
        headerFile << "#include <Graphics/Texture.h>\r\n\r\n";
        headerFile << "#include \"TextureAsset.h\"\r\n\r\n";

        sourceFile << "#include \"" << package << "Textures.h\"\r\n\r\n";
        sourceFile << "AStaticRun(" << package << "Textures)\r\n{\r\n\r\n";

        for (auto &texture : textures)
        {
            if (texture->isExternal())
            {
                continue;
            }

            ALogMessage("", "Process TextureCGType %s", texture->path);

            texture->generateDeclaration(source);
            headerFile << texture->flush();

            texture->generateImplementation();
            sourceFile << texture->flush();
        }
        sourceFile << "\r\n}\r\n";
    }

    String getBaseType() const override
    {
        return "Graphics.Texture";
    }

    Array<String> getImportFiles() const override
    {
        return { LegacyClassGen::GenerationSettings::getInstance().currentPackage + "Textures.h" };
    }

    void generate() override
    {
    }

    void generateDeclaration(const APath &source)
    {
        String namespaceName = getNamespace();
        String name = path.baseName();
        String texturePath;
        data.read("Path", texturePath);

        pushRegion(name);
        generateInsideNamespaceIfNeeded(namespaceName, [&]() {
            String compilation;
            if (!data.read("Compilation", compilation) || compilation == LegacyClassGen::TextureCompilation::Names[LegacyClassGen::TextureCompilation::Embedded]) //TODO: improve enums comparing with strings
            {
                APath textureDataPath = source + (name + "TextureData.cpp");
                if (APathInfo(textureDataPath).modificationTime() < APathInfo(path).modificationTime())
                {
                    AFile textureDataFile;
                    if (textureDataFile.open(textureDataPath, AFileOpenMode::WriteBinary))
                    {
                        textureDataFile << "\r\n\r\n";
                        textureDataFile << "Array<uint8_t> Get" << name << "_TextureData() {\r\n    return {\r\n    ";
                    }
                    serializeFile(APath(texturePath).resolveWithDirectory(path.directory()), [&](const String &text) {
                        textureDataFile << text;
                    });
                    if (textureDataFile.isOpen())
                    {
                        textureDataFile << "\r\n};\r\n}\r\n";
                    }
                }

                generateFunction("Array<uint8_t>", "Get" + name + "_TextureData", {});
            }

            generateEntity("struct", name + "_TextureAsset", "TextureAsset", {}, [&]() {
                generateFunction("operator", "SharedReference<Graphics::Texture>", {}, [&]() {
                    generateField("static AWeakPointer<Graphics::Texture>", "cachedTexture");
                    generateBranch("!cachedTexture", [&]() {
                        
                        if (compilation == LegacyClassGen::TextureCompilation::Names[LegacyClassGen::TextureCompilation::AbsolutePath]) //TODO: improve enums comparing with strings
                        {
                            generateField("SharedReference<Graphics::Texture>", "texture", "load(\"" + APath(texturePath).resolveWithDirectory(path.directory()).toUnixPathString() + "\")");
                        }
                        else if (compilation == LegacyClassGen::TextureCompilation::Names[LegacyClassGen::TextureCompilation::RelativePath]) //TODO: improve enums comparing with strings
                        {
                            //TODO: convert absolute path to relative...
                            generateField("SharedReference<Graphics::Texture>", "texture", "load(APath(\"" + APath(texturePath).toUnixPathString() + "\").resolveWithDirectory(APath::applicationDirectory()))");
                        }
                        else
                        {
                            generateField("SharedReference<Graphics::Texture>", "texture", "load(Get" + name + "_TextureData())");
                        }

                        generateAssignment("cachedTexture", "texture");
                        String filtration;
                        if (data.read("Filtration", filtration))
                        {
                            generateCall("cachedTexture->setFiltration", { "Graphics::TextureFiltration::" + filtration });
                        }
                        String wrapping;
                        if (data.read("Wrapping", wrapping))
                        {
                            generateCall("cachedTexture->setWrapping", { "Graphics::TextureWrapping::" + wrapping });
                        }

                        generateCall("cachedTexture->load", {});
                        generateReturn("texture");
                    });
                    generateReturn("cachedTexture");
                }, true);
            });
            generateField("constexpr static " + name + "_TextureAsset", name); //TODO: const
        });
        popRegion();
    }

    void generateImplementation()
    {
        generateCall("AssetManager::getInstance().assets.insert", { Str::Quote(getDefaultType(false)), "[](){ return AVariant(SharedReference<Graphics::Texture>(" + getDefaultType(true) + ")); }" });
    }
};

}
