
namespace ClassGen
{

void TextureFileEditor::RenderFile()
{
    auto& info = *std::dynamic_pointer_cast<ClassGen::TextureInfo>(Data.Instance);

    if (ImGui::InputText("Namespace", &info.Namespace))
    {
        MarkFileDirty(Data.Path);
    }

    String s = info.Path.generic_string();
    if (ImGui::InputText("Path", &s))
    {
        info.Path = s;
        MarkFileDirty(Data.Path);
        if (!System::IsRegularFile(info.Path))
        {
            Texture = nullptr;
            return;
        }
    }

    if (LastPath != info.Path)
    {
        LastPath = info.Path;
        Texture = Graphics::LoadTexture(info.Path);
        g_GraphicsContext->Create2DTexture(*Texture);
    }

    if (Texture && ReinterpretCast<void>(&Texture->Data))
    {
        ImGui::Text(fmt::format("Width: {}", Texture->Size.x).data());
        ImGui::Text(fmt::format("Height: {}", Texture->Size.y).data());
        ImGui::Text(fmt::format("Layers: {}", Texture->Size.z).data());
        ImGui::Text(fmt::format("Channels: {}", Texture->Channels).data());
        Array<String> Metrics = { "B", "KiB", "MiB", "GiB" };
        size_t i = 0;
        float s = Texture->Buffer.size();
        for (; i < Metrics.size() && s >= 1024; ++i)
        {
            s /= 1024.0f;
        }

        ImGui::Text(fmt::format("Size: {}{}", s, Metrics[i]).data());
        ImGui::Text(fmt::format("Filtration: {}", Texture->Filtration.toString()).data());
        ImGui::Text(fmt::format("Wrapping: {}", Texture->Wrapping.toString()).data());

        ImGui::Image(ImGui::TexID(Texture), { (float)Texture->Size.x, (float)Texture->Size.y });
    }
}

}
