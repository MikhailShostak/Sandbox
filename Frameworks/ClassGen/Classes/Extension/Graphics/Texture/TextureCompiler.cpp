namespace ClassGen
{

void TextureCompiler::Compile(const SharedReference<ClassGen::BaseInfo>& BaseInfo, const System::Path& OutputFilePath)
{
    auto t = DynamicCast<ClassGen::TextureInfo>(BaseInfo);
    if (!t)
    {
        return;
    }
    auto& textureInfo = *t;

    auto assetName = OutputFilePath.stem().generic_string();
    auto assetNamespace = boost::replace_all_copy(textureInfo.Namespace, ".", "::");

    std::ofstream file;
    file.open(OutputFilePath.generic_string(), std::ios::binary);
    fmt::print("Write: {}\n", OutputFilePath.generic_string());

    file << "#pragma once\n";
    if (!assetNamespace.empty())
    {
        file << "\n";
        file << "namespace " << assetNamespace << "\n";
        file << "{\n";
    }

    file << "\n";
    file << "inline DynamicAsset<Graphics::Texture> " << assetName << " = { \"" << assetName << "\", [](auto &instance)\n{\n";
    file << "Graphics::LoadTexture(instance, \"" << Serialization::ToString(textureInfo.Path) << "\");\n";
    file << "} };\n";

    if (!assetNamespace.empty())
    {
        file << "}\n";
    }
}

}
