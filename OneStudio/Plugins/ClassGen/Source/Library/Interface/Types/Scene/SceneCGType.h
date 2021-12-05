#pragma once

#include "Core/BaseCGType.h"
#include "Includes/TextureCompilation.gen.h"

namespace LegacyClassGen
{

class SceneCGType : public BaseCGType
{
public:

    /*static void processAllFiles(const Array<SharedReference<TextureCGType>> &textures, const APath &source)
    {
        AFile headerFile;
        AFile sourceFile;

        if (!headerFile.open(source + "Textures.h", AFileOpenMode::WriteBinary))
        {
            return;
        }

        if (!sourceFile.open(source + "Textures.cpp", AFileOpenMode::WriteBinary))
        {
            return;
        }

        headerFile << "#pragma once\r\n\r\n";
        headerFile << "#include <Experimental>\r\n\r\n";
        headerFile << "#include \"TextureAsset.h\"\r\n\r\n";

        sourceFile << "#include \"Textures.h\"\r\n\r\n";
        sourceFile << "AStaticRun(Textures)\r\n{\r\n\r\n";

        for (auto &texture : textures)
        {
            ALogMessage("", "Process TextureCGType %s", texture->path);

            texture->generateDeclaration(source);
            headerFile << texture->flush();

            texture->generateImplementation();
            sourceFile << texture->flush();
        }
        sourceFile << "\r\n}\r\n";
    }*/

    String getBaseType() const override
    {
        return "Core.Scene";
    }

    void generate() override
    {
    }

    void generateDeclaration(const APath &source)
    {
        /*String namespaceName = getNamespace();
        String name = path.baseName();
        String texturePath;
        data.read("Path", texturePath);

        pushRegion(name);
        generateInsideNamespaceIfNeeded(namespaceName, [&]() {
            String compilation;
            if (!data.read("Compilation", compilation) || compilation == LegacyClassGen::TextureCompilation::Names[LegacyClassGen::TextureCompilation::Embedded]) //TODO: improve enums comparing with strings
            {
                AFile textureDataFile;
                if (textureDataFile.open(source + (name + "TextureData.cpp"), AFileOpenMode::WriteBinary))
                {
                    textureDataFile << "#include <Experimental>\r\n\r\n";
                    textureDataFile << "Array<uint8_t> Get" << name << "_TextureData() {\r\n    return {\r\n    ";
                }
                serializeFile(APath(texturePath).resolveWithDirectory(path.directory()), [&](const String &text) {
                    textureDataFile << text;
                });
                if (textureDataFile.isOpen())
                {
                    textureDataFile << "\r\n};\r\n}\r\n";
                }

                generateFunction("Array<uint8_t>", "Get" + name + "_TextureData", {});
            }

            generateEntity("struct", name + "_TextureAsset", "TextureAsset", {}, [&]() {
                generateFunction("operator", "SharedReference<Graphics::Texture>", {}, [&]() {
                    generateField("static WeakReference<Graphics::Texture>", "cachedTexture");
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
        popRegion();*/
    }

    void generateImplementation()
    {
        //generateCall("AssetManager::getInstance().assets.insert", { getDefaultType(false).quote(), "[](){ return AVariant(SharedReference<Graphics::Texture>(" + getDefaultType(true) + ")); }" });
    }
};

}
