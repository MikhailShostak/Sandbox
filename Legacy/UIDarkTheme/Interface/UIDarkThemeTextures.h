#pragma once

#include <Graphics>

//CLASSGEN GENERATED REGION: MinimizeButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetMinimizeButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: MinimizeButtonSmallHeader
struct MinimizeButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: MinimizeButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetMinimizeButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static MinimizeButtonSmall_TextureAsset MinimizeButtonSmall;
//CLASSGEN GENERATED REGION: MinimizeButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: StopButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetStopButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: StopButtonSmallHeader
struct StopButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: StopButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetStopButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static StopButtonSmall_TextureAsset StopButtonSmall;
//CLASSGEN GENERATED REGION: StopButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: FlatPanelBegin
//CLASSGEN END REGION
Array<uint8_t> GetFlatPanel_TextureData();
//CLASSGEN GENERATED REGION: FlatPanelHeader
struct FlatPanel_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FlatPanelBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetFlatPanel_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static FlatPanel_TextureAsset FlatPanel;
//CLASSGEN GENERATED REGION: FlatPanelEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: MinusButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetMinusButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: MinusButtonSmallHeader
struct MinusButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: MinusButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetMinusButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static MinusButtonSmall_TextureAsset MinusButtonSmall;
//CLASSGEN GENERATED REGION: MinusButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: InnerShadowBegin
//CLASSGEN END REGION
Array<uint8_t> GetInnerShadow_TextureData();
//CLASSGEN GENERATED REGION: InnerShadowHeader
struct InnerShadow_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: InnerShadowBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetInnerShadow_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static InnerShadow_TextureAsset InnerShadow;
//CLASSGEN GENERATED REGION: InnerShadowEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NextStepButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetNextStepButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: NextStepButtonSmallHeader
struct NextStepButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: NextStepButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetNextStepButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static NextStepButtonSmall_TextureAsset NextStepButtonSmall;
//CLASSGEN GENERATED REGION: NextStepButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ShadowBottomBegin
//CLASSGEN END REGION
Array<uint8_t> GetShadowBottom_TextureData();
//CLASSGEN GENERATED REGION: ShadowBottomHeader
struct ShadowBottom_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ShadowBottomBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetShadowBottom_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Trilinear);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ShadowBottom_TextureAsset ShadowBottom;
//CLASSGEN GENERATED REGION: ShadowBottomEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: DownButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetDownButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: DownButtonSmallHeader
struct DownButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: DownButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetDownButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static DownButtonSmall_TextureAsset DownButtonSmall;
//CLASSGEN GENERATED REGION: DownButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: FileIconBegin
//CLASSGEN END REGION
Array<uint8_t> GetFileIcon_TextureData();
//CLASSGEN GENERATED REGION: FileIconHeader
struct FileIcon_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: FileIconBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetFileIcon_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static FileIcon_TextureAsset FileIcon;
//CLASSGEN GENERATED REGION: FileIconEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: MaximizeButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetMaximizeButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: MaximizeButtonSmallHeader
struct MaximizeButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: MaximizeButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetMaximizeButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static MaximizeButtonSmall_TextureAsset MaximizeButtonSmall;
//CLASSGEN GENERATED REGION: MaximizeButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NextButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetNextButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: NextButtonSmallHeader
struct NextButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: NextButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetNextButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static NextButtonSmall_TextureAsset NextButtonSmall;
//CLASSGEN GENERATED REGION: NextButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: LineBegin
//CLASSGEN END REGION
Array<uint8_t> GetLine_TextureData();
//CLASSGEN GENERATED REGION: LineHeader
struct Line_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: LineBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetLine_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Bilinear);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static Line_TextureAsset Line;
//CLASSGEN GENERATED REGION: LineEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PinSocketBegin
//CLASSGEN END REGION
Array<uint8_t> GetPinSocket_TextureData();
//CLASSGEN GENERATED REGION: PinSocketHeader
struct PinSocket_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PinSocketBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPinSocket_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static PinSocket_TextureAsset PinSocket;
//CLASSGEN GENERATED REGION: PinSocketEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PlayButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetPlayButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: PlayButtonSmallHeader
struct PlayButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PlayButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPlayButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static PlayButtonSmall_TextureAsset PlayButtonSmall;
//CLASSGEN GENERATED REGION: PlayButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PopupBegin
//CLASSGEN END REGION
Array<uint8_t> GetPopup_TextureData();
//CLASSGEN GENERATED REGION: PopupHeader
struct Popup_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PopupBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPopup_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static Popup_TextureAsset Popup;
//CLASSGEN GENERATED REGION: PopupEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: LeftButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetLeftButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: LeftButtonSmallHeader
struct LeftButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: LeftButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetLeftButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static LeftButtonSmall_TextureAsset LeftButtonSmall;
//CLASSGEN GENERATED REGION: LeftButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: DropDownListBegin
//CLASSGEN END REGION
Array<uint8_t> GetDropDownList_TextureData();
//CLASSGEN GENERATED REGION: DropDownListHeader
struct DropDownList_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: DropDownListBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetDropDownList_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static DropDownList_TextureAsset DropDownList;
//CLASSGEN GENERATED REGION: DropDownListEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ButtonBackgroundBegin
//CLASSGEN END REGION
Array<uint8_t> GetButtonBackground_TextureData();
//CLASSGEN GENERATED REGION: ButtonBackgroundHeader
struct ButtonBackground_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ButtonBackgroundBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetButtonBackground_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ButtonBackground_TextureAsset ButtonBackground;
//CLASSGEN GENERATED REGION: ButtonBackgroundEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: CheckButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetCheckButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: CheckButtonSmallHeader
struct CheckButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: CheckButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetCheckButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static CheckButtonSmall_TextureAsset CheckButtonSmall;
//CLASSGEN GENERATED REGION: CheckButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: CloseButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetCloseButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: CloseButtonSmallHeader
struct CloseButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: CloseButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetCloseButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static CloseButtonSmall_TextureAsset CloseButtonSmall;
//CLASSGEN GENERATED REGION: CloseButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClosedFolderIconBegin
//CLASSGEN END REGION
Array<uint8_t> GetClosedFolderIcon_TextureData();
//CLASSGEN GENERATED REGION: ClosedFolderIconHeader
struct ClosedFolderIcon_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClosedFolderIconBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetClosedFolderIcon_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ClosedFolderIcon_TextureAsset ClosedFolderIcon;
//CLASSGEN GENERATED REGION: ClosedFolderIconEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: InvertedFlatPanelBegin
//CLASSGEN END REGION
Array<uint8_t> GetInvertedFlatPanel_TextureData();
//CLASSGEN GENERATED REGION: InvertedFlatPanelHeader
struct InvertedFlatPanel_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: InvertedFlatPanelBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetInvertedFlatPanel_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static InvertedFlatPanel_TextureAsset InvertedFlatPanel;
//CLASSGEN GENERATED REGION: InvertedFlatPanelEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NodeBegin
//CLASSGEN END REGION
Array<uint8_t> GetNode_TextureData();
//CLASSGEN GENERATED REGION: NodeHeader
struct Node_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: NodeBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetNode_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static Node_TextureAsset Node;
//CLASSGEN GENERATED REGION: NodeEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: OpenedFolderIconBegin
//CLASSGEN END REGION
Array<uint8_t> GetOpenedFolderIcon_TextureData();
//CLASSGEN GENERATED REGION: OpenedFolderIconHeader
struct OpenedFolderIcon_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: OpenedFolderIconBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetOpenedFolderIcon_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static OpenedFolderIcon_TextureAsset OpenedFolderIcon;
//CLASSGEN GENERATED REGION: OpenedFolderIconEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PauseButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetPauseButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: PauseButtonSmallHeader
struct PauseButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PauseButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPauseButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static PauseButtonSmall_TextureAsset PauseButtonSmall;
//CLASSGEN GENERATED REGION: PauseButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PlusButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetPlusButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: PlusButtonSmallHeader
struct PlusButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PlusButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPlusButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static PlusButtonSmall_TextureAsset PlusButtonSmall;
//CLASSGEN GENERATED REGION: PlusButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PrevButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetPrevButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: PrevButtonSmallHeader
struct PrevButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PrevButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPrevButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static PrevButtonSmall_TextureAsset PrevButtonSmall;
//CLASSGEN GENERATED REGION: PrevButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: PrevStepButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetPrevStepButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: PrevStepButtonSmallHeader
struct PrevStepButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: PrevStepButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetPrevStepButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static PrevStepButtonSmall_TextureAsset PrevStepButtonSmall;
//CLASSGEN GENERATED REGION: PrevStepButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: RightButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetRightButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: RightButtonSmallHeader
struct RightButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: RightButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetRightButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static RightButtonSmall_TextureAsset RightButtonSmall;
//CLASSGEN GENERATED REGION: RightButtonSmallEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ShadowLeftBegin
//CLASSGEN END REGION
Array<uint8_t> GetShadowLeft_TextureData();
//CLASSGEN GENERATED REGION: ShadowLeftHeader
struct ShadowLeft_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ShadowLeftBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetShadowLeft_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Trilinear);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ShadowLeft_TextureAsset ShadowLeft;
//CLASSGEN GENERATED REGION: ShadowLeftEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ShadowRightBegin
//CLASSGEN END REGION
Array<uint8_t> GetShadowRight_TextureData();
//CLASSGEN GENERATED REGION: ShadowRightHeader
struct ShadowRight_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ShadowRightBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetShadowRight_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Trilinear);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ShadowRight_TextureAsset ShadowRight;
//CLASSGEN GENERATED REGION: ShadowRightEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ShadowTopBegin
//CLASSGEN END REGION
Array<uint8_t> GetShadowTop_TextureData();
//CLASSGEN GENERATED REGION: ShadowTopHeader
struct ShadowTop_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ShadowTopBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetShadowTop_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Trilinear);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ShadowTop_TextureAsset ShadowTop;
//CLASSGEN GENERATED REGION: ShadowTopEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ToolTipBegin
//CLASSGEN END REGION
Array<uint8_t> GetToolTip_TextureData();
//CLASSGEN GENERATED REGION: ToolTipHeader
struct ToolTip_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ToolTipBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetToolTip_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static ToolTip_TextureAsset ToolTip;
//CLASSGEN GENERATED REGION: ToolTipEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: TransitionIconBegin
//CLASSGEN END REGION
Array<uint8_t> GetTransitionIcon_TextureData();
//CLASSGEN GENERATED REGION: TransitionIconHeader
struct TransitionIcon_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: TransitionIconBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetTransitionIcon_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Bilinear);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static TransitionIcon_TextureAsset TransitionIcon;
//CLASSGEN GENERATED REGION: TransitionIconEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: UpButtonSmallBegin
//CLASSGEN END REGION
Array<uint8_t> GetUpButtonSmall_TextureData();
//CLASSGEN GENERATED REGION: UpButtonSmallHeader
struct UpButtonSmall_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: UpButtonSmallBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    if (SharedReference<Legacy::Graphics::Texture> cachedTexture = cachedTextureWeak.lock())
    {
        return cachedTexture;
    }
    else
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetUpButtonSmall_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        cachedTexture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        cachedTexture->load();
        return texture;
    }
}
//CLASSGEN END REGION
};
constexpr static UpButtonSmall_TextureAsset UpButtonSmall;
//CLASSGEN GENERATED REGION: UpButtonSmallEnd
//CLASSGEN END REGION
