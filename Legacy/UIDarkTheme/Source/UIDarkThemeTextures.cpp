#include "UIDarkThemeTextures.h"

AStaticRun(UIDarkThemeTextures)
{

AssetManager::getInstance().assets.insert({"MinimizeButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(MinimizeButtonSmall)); }});
AssetManager::getInstance().assets.insert({"StopButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(StopButtonSmall)); }});
AssetManager::getInstance().assets.insert({"FlatPanel", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(FlatPanel)); }});
AssetManager::getInstance().assets.insert({"MinusButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(MinusButtonSmall)); }});
AssetManager::getInstance().assets.insert({"InnerShadow", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(InnerShadow)); }});
AssetManager::getInstance().assets.insert({"NextStepButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(NextStepButtonSmall)); }});
AssetManager::getInstance().assets.insert({"ShadowBottom", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ShadowBottom)); }});
AssetManager::getInstance().assets.insert({"DownButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(DownButtonSmall)); }});
AssetManager::getInstance().assets.insert({"FileIcon", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(FileIcon)); }});
AssetManager::getInstance().assets.insert({"MaximizeButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(MaximizeButtonSmall)); }});
AssetManager::getInstance().assets.insert({"NextButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(NextButtonSmall)); }});
AssetManager::getInstance().assets.insert({"Line", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(Line)); }});
AssetManager::getInstance().assets.insert({"PinSocket", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(PinSocket)); }});
AssetManager::getInstance().assets.insert({"PlayButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(PlayButtonSmall)); }});
AssetManager::getInstance().assets.insert({"Popup", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(Popup)); }});
AssetManager::getInstance().assets.insert({"LeftButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(LeftButtonSmall)); }});
AssetManager::getInstance().assets.insert({"DropDownList", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(DropDownList)); }});
AssetManager::getInstance().assets.insert({"ButtonBackground", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ButtonBackground)); }});
AssetManager::getInstance().assets.insert({"CheckButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(CheckButtonSmall)); }});
AssetManager::getInstance().assets.insert({"CloseButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(CloseButtonSmall)); }});
AssetManager::getInstance().assets.insert({"ClosedFolderIcon", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ClosedFolderIcon)); }});
AssetManager::getInstance().assets.insert({"InvertedFlatPanel", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(InvertedFlatPanel)); }});
AssetManager::getInstance().assets.insert({"Node", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(Node)); }});
AssetManager::getInstance().assets.insert({"OpenedFolderIcon", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(OpenedFolderIcon)); }});
AssetManager::getInstance().assets.insert({"PauseButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(PauseButtonSmall)); }});
AssetManager::getInstance().assets.insert({"PlusButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(PlusButtonSmall)); }});
AssetManager::getInstance().assets.insert({"PrevButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(PrevButtonSmall)); }});
AssetManager::getInstance().assets.insert({"PrevStepButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(PrevStepButtonSmall)); }});
AssetManager::getInstance().assets.insert({"RightButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(RightButtonSmall)); }});
AssetManager::getInstance().assets.insert({"ShadowLeft", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ShadowLeft)); }});
AssetManager::getInstance().assets.insert({"ShadowRight", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ShadowRight)); }});
AssetManager::getInstance().assets.insert({"ShadowTop", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ShadowTop)); }});
AssetManager::getInstance().assets.insert({"ToolTip", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(ToolTip)); }});
AssetManager::getInstance().assets.insert({"TransitionIcon", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(TransitionIcon)); }});
AssetManager::getInstance().assets.insert({"UpButtonSmall", [](){ return AVariant(SharedReference<Legacy::Graphics::Texture>(UpButtonSmall)); }});

}
