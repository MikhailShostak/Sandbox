
namespace ClassGen
{

void TextureFileEditor::RenderFile()
{
    auto& info = *DynamicCast<ClassGen::TextureInfo>(Data.Instance);

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

    if (!FiltrationEditor.Changed)
    {
        FiltrationEditor.ID = fmt::format("Filtration##{}", fmt::ptr(&info.TextureFiltration));
        FiltrationEditor.TypeInfo.Name = "Graphics.TextureFiltration";
        FiltrationEditor.FileInfo = FindClassByName(FiltrationEditor.TypeInfo);
        FiltrationEditor.Value = Serialization::ToString(info.TextureFiltration);
        FiltrationEditor.Changed = [this, &info]()
        {
            info.TextureInstance = nullptr;
            MarkFileDirty(Data.Path);
        };
    }
    if (!WrappingEditor.Changed)
    {
        WrappingEditor.ID = fmt::format("Wrapping##{}", fmt::ptr(&info.TextureWrapping));
        WrappingEditor.TypeInfo.Name = "Graphics.TextureWrapping";
        WrappingEditor.FileInfo = FindClassByName(WrappingEditor.TypeInfo);
        WrappingEditor.Value = Serialization::ToString(info.TextureWrapping);
        WrappingEditor.Changed = [this, &info]()
        {
            info.TextureInstance = nullptr;
            MarkFileDirty(Data.Path);
        };
    }
    FiltrationEditor.Draw();
    WrappingEditor.Draw();

    if (LastPath != info.Path)
    {
        LastPath = info.Path;
        Texture = info.Load(*g_GraphicsContext);
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

        ImGui::Image(ImGui::TexID(Texture), { (float)Texture->Size.x, (float)Texture->Size.y });
    }
}

}
