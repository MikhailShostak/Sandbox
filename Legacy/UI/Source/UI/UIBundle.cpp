#include "UIBundle.h"

#include "fonts-build.h"
#include "ui-build.h"

#include "APixmap.h"
#include "APixmapLoader.h"
#include "AssetsRepository.h"
#include "Includes/Texture.gen.h"

ImplementBundle(UI)
{
    LoadBundle_fonts_build();
    LoadBundle_ui_build();

    APixmap field = APixmapLoader::getInstance().decompress(getAsset("field"));
    APixmap line = APixmapLoader::getInstance().decompress(getAsset("line"));
    APixmap list = APixmapLoader::getInstance().decompress(getAsset("list"));
    APixmap listHighlighting = APixmapLoader::getInstance().decompress(getAsset("list_highlighting"));
    APixmap listControlPoint = APixmapLoader::getInstance().decompress(getAsset("controlpoint"));
    APixmap button = APixmapLoader::getInstance().decompress(getAsset("button"));
    APixmap dialog = APixmapLoader::getInstance().decompress(getAsset("dialog"));
    APixmap header = APixmapLoader::getInstance().decompress(getAsset("header"));
    APixmap backgroundBlack = APixmapLoader::getInstance().decompress(getAsset("background_black"));
    APixmap slider = APixmapLoader::getInstance().decompress(getAsset("slider"));
    APixmap progress = APixmapLoader::getInstance().decompress(getAsset("progress"));

    Asset *asset = nullptr;

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::FieldImage);
    asset->setProperty("Pixmap", field);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::LineImage);
    asset->setProperty("Pixmap", line);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::ListImage);
    asset->setProperty("Pixmap", list);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::ListHighlightingImage);
    asset->setProperty("Pixmap", listHighlighting);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::ControlPointImage);
    asset->setProperty("Pixmap", listControlPoint);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::ButtonImage);
    asset->setProperty("Pixmap", button);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::DialogImage);
    asset->setProperty("Pixmap", dialog);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::HeaderImage);
    asset->setProperty("Pixmap", header);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::BackgroundBlackImage);
    asset->setProperty("Pixmap", backgroundBlack);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::SliderImage);
    asset->setProperty("Pixmap", slider);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);

    asset = &assetsRepository.registerAsset<Legacy::Graphics::Texture>(Assets::ProgressImage);
    asset->setProperty("Pixmap", progress);
    asset->setProperty("Filtration", Legacy::Graphics::TextureFiltration::Nearest);
}
