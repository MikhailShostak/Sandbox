//CLASSGEN GENERATED REGION: Includes
#include "TabItem.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "FlexBox.gen.h"
#include "Direction.gen.h"
#include "Label.gen.h"

//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
#include "UITouchGestureRecognizer.h"//TODO: temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TabItem::TabItem()
{
    Math::Transform transform_183;
    Math::Vector position_184;
    position_184.X = 0.000000;
    position_184.Y = 0.000000;
    position_184.Z = 0.000000;
    position_184.W = 0.000000;
    transform_183.Position = position_184;
    Math::Quaternion rotation_189;
    rotation_189.X = 0.000000;
    rotation_189.Y = 0.000000;
    rotation_189.Z = 0.000000;
    rotation_189.W = 1.000000;
    transform_183.Rotation = rotation_189;
    (*this).setTransform(transform_183);
    Math::IntegerVector size_194;
    size_194.X = 0.000000;
    size_194.Y = 0.000000;
    size_194.Z = 0.000000;
    size_194.W = 0.000000;
    (*this).setSize(size_194);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::OverlayData item_207_0;
    Math::Offsets padding_208;
    padding_208.Top = 0.000000;
    padding_208.Right = 0.000000;
    padding_208.Bottom = 0.000000;
    padding_208.Left = 0.000000;
    item_207_0.Padding = padding_208;
    item_207_0.HorizontalAlignment = Core::Alignment::Start;
    item_207_0.VerticalAlignment = Core::Alignment::Start;
    UI::OverlayData item_215_1;
    Math::Offsets padding_216;
    padding_216.Top = 0.000000;
    padding_216.Right = 0.000000;
    padding_216.Bottom = 0.000000;
    padding_216.Left = 0.000000;
    item_215_1.Padding = padding_216;
    item_215_1.HorizontalAlignment = Core::Alignment::Start;
    item_215_1.VerticalAlignment = Core::Alignment::Start;
    (*this).setData({item_207_0,item_215_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TabItem::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TabItem::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TabItem::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TabItem");
    background = CreateShared<UI::ImageView>();
    (*background).setName("Background");
    Math::Transform transform_72;
    Math::Vector position_73;
    position_73.X = 0.000000;
    position_73.Y = 0.000000;
    position_73.Z = 0.000000;
    position_73.W = 0.000000;
    transform_72.Position = position_73;
    Math::Quaternion rotation_78;
    rotation_78.X = 0.000000;
    rotation_78.Y = 0.000000;
    rotation_78.Z = 0.000000;
    rotation_78.W = 1.000000;
    transform_72.Rotation = rotation_78;
    (*background).setTransform(transform_72);
    Math::IntegerVector size_83;
    size_83.X = 0.000000;
    size_83.Y = 0.000000;
    size_83.Z = 0.000000;
    size_83.W = 0.000000;
    (*background).setSize(size_83);
    (*background).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setAffectsParentLayout(false);
    (*this).addView(background);
    SharedReference<UI::FlexBox> content = CreateShared<UI::FlexBox>();
    (*content).setName("Content");
    Math::Transform transform_91;
    Math::Vector position_92;
    position_92.X = 0.000000;
    position_92.Y = 0.000000;
    position_92.Z = 0.000000;
    position_92.W = 0.000000;
    transform_91.Position = position_92;
    Math::Quaternion rotation_97;
    rotation_97.X = 0.000000;
    rotation_97.Y = 0.000000;
    rotation_97.Z = 0.000000;
    rotation_97.W = 1.000000;
    transform_91.Rotation = rotation_97;
    (*content).setTransform(transform_91);
    Math::IntegerVector size_102;
    size_102.X = 0.000000;
    size_102.Y = 0.000000;
    size_102.Z = 0.000000;
    size_102.W = 0.000000;
    (*content).setSize(size_102);
    (*content).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setAffectsParentLayout(false);
    UI::FlexBoxData item_111_0;
    item_111_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_113_1;
    item_113_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_115_2;
    item_115_2.Alignment = Core::Alignment::Center;
    (*content).setData({item_111_0,item_113_1,item_115_2,});
    (*content).setDirection(UI::Direction::Horizontal);
    (*content).setSpacing(8.000000);
    Math::Offsets padding_119;
    padding_119.Top = 8.000000;
    padding_119.Right = 8.000000;
    padding_119.Bottom = 8.000000;
    padding_119.Left = 8.000000;
    (*content).setPadding(padding_119);
    title = CreateShared<UI::Label>();
    (*title).setName("Title");
    Math::Transform transform_124;
    Math::Vector position_125;
    position_125.X = 0.000000;
    position_125.Y = 0.000000;
    position_125.Z = 0.000000;
    position_125.W = 0.000000;
    transform_124.Position = position_125;
    Math::Quaternion rotation_130;
    rotation_130.X = 0.000000;
    rotation_130.Y = 0.000000;
    rotation_130.Z = 0.000000;
    rotation_130.W = 1.000000;
    transform_124.Rotation = rotation_130;
    (*title).setTransform(transform_124);
    Math::IntegerVector size_135;
    size_135.X = 0.000000;
    size_135.Y = 0.000000;
    size_135.Z = 0.000000;
    size_135.W = 0.000000;
    (*title).setSize(size_135);
    (*title).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*title).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*title).setAffectsParentLayout(false);
    (*title).setTextAlign(Core::TextAlign::Start);
    (*title).setTextWrapping(Core::TextWrapping::Inline);
    (*content).addView(title);
    separator = CreateShared<UI::ImageView>();
    (*separator).setName("Separator");
    Math::Transform transform_145;
    Math::Vector position_146;
    position_146.X = 0.000000;
    position_146.Y = 0.000000;
    position_146.Z = 0.000000;
    position_146.W = 0.000000;
    transform_145.Position = position_146;
    Math::Quaternion rotation_151;
    rotation_151.X = 0.000000;
    rotation_151.Y = 0.000000;
    rotation_151.Z = 0.000000;
    rotation_151.W = 1.000000;
    transform_145.Rotation = rotation_151;
    (*separator).setTransform(transform_145);
    Math::IntegerVector size_156;
    size_156.X = 0.000000;
    size_156.Y = 0.000000;
    size_156.Z = 0.000000;
    size_156.W = 0.000000;
    (*separator).setSize(size_156);
    (*separator).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*separator).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*separator).setAffectsParentLayout(false);
    (*content).addView(separator);
    closeButton = CreateShared<UI::ImageView>();
    (*closeButton).setName("CloseButton");
    Math::Transform transform_164;
    Math::Vector position_165;
    position_165.X = 0.000000;
    position_165.Y = 0.000000;
    position_165.Z = 0.000000;
    position_165.W = 0.000000;
    transform_164.Position = position_165;
    Math::Quaternion rotation_170;
    rotation_170.X = 0.000000;
    rotation_170.Y = 0.000000;
    rotation_170.Z = 0.000000;
    rotation_170.W = 1.000000;
    transform_164.Rotation = rotation_170;
    (*closeButton).setTransform(transform_164);
    Math::IntegerVector size_175;
    size_175.X = 14.000000;
    size_175.Y = 14.000000;
    size_175.Z = 0.000000;
    size_175.W = 0.000000;
    (*closeButton).setSize(size_175);
    (*closeButton).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*closeButton).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*closeButton).setAffectsParentLayout(false);
    (*content).addView(closeButton);
    (*this).addView(content);
}
//CLASSGEN END REGION

void TabItem::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    background->setImage(Legacy::Graphics::Texture::getWhiteTexture());
    background->setColor(AColor::fromHex(0xFF282828));

    Array<uint8_t> data;
    data.resize(4 * 4);

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            data[i * 4 + j] = (i == 0 && j == 0 || i == 2 && j == 2) ? 0x38 : 0x28;
        }
    }

    APixmap pixmap;
    pixmap.setBuffer(data, { 4, 4 }, APixmapDataFormat::Gray);

    SharedReference<Legacy::Graphics::Texture> t = CreateShared<Legacy::Graphics::Texture>();
    t->setPixmap(pixmap);
    t->setWrapping(Legacy::Graphics::TextureWrapping::TiledWrapping);
    t->load();

    separator->setImage(t);
    separator->setVerticalSizePolicy(SizePolicy::Fixed);
    separator->setSize({ 5, 5 });

    closeButton->addGestureRecognizer(CreateShared<TouchGestureRecognizer>());
    closeButton->setImage(::CloseButtonSmall);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
