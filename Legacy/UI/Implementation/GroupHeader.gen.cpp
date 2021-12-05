//CLASSGEN GENERATED REGION: Includes
#include "GroupHeader.gen.h"
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
#include <UIDarkTheme>//TODO:temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GroupHeader::GroupHeader()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setAffectsParentLayout(false);
    UI::OverlayData item_173_0;
    Math::Offsets padding_174;
    padding_174.Top = 0.000000;
    padding_174.Right = 0.000000;
    padding_174.Bottom = 0.000000;
    padding_174.Left = 0.000000;
    item_173_0.Padding = padding_174;
    item_173_0.HorizontalAlignment = Core::Alignment::Start;
    item_173_0.VerticalAlignment = Core::Alignment::Start;
    UI::OverlayData item_181_1;
    Math::Offsets padding_182;
    padding_182.Top = 0.000000;
    padding_182.Right = 0.000000;
    padding_182.Bottom = 0.000000;
    padding_182.Left = 0.000000;
    item_181_1.Padding = padding_182;
    item_181_1.HorizontalAlignment = Core::Alignment::Start;
    item_181_1.VerticalAlignment = Core::Alignment::Start;
    (*this).setData({item_173_0,item_181_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GroupHeader::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void GroupHeader::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GroupHeader::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("GroupHeader");
    background = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*background).setName("Background");
    {
    }
    (*background).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setAffectsParentLayout(false);
    (*this).addView(background);
    content = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*content).setName("Content");
    {
    }
    (*content).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setAffectsParentLayout(false);
    UI::FlexBoxData item_144_0;
    item_144_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_146_1;
    item_146_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_148_2;
    item_148_2.Alignment = Core::Alignment::Center;
    (*content).setData({item_144_0,item_146_1,item_148_2,});
    (*content).setDirection(UI::Direction::Horizontal);
    (*content).setSpacing(4.000000);
    Math::Offsets padding_152;
    padding_152.Top = 4.000000;
    padding_152.Right = 4.000000;
    padding_152.Bottom = 4.000000;
    padding_152.Left = 4.000000;
    (*content).setPadding(padding_152);
    expandButton = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*expandButton).setName("ExpandButton");
    {
    }
    (*expandButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*expandButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*expandButton).setAffectsParentLayout(false);
    (*expandButton).setImage(PlusButtonSmall);
    (*content).addView(expandButton);
    title = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*title).setName("Title");
    {
    }
    (*title).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*title).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*title).setAffectsParentLayout(false);
    (*title).setTextAlign(Core::TextAlign::Start);
    (*title).setTextWrapping(Core::TextWrapping::Inline);
    (*content).addView(title);
    separator = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*separator).setName("Separator");
    {
    }
    (*separator).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*separator).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*separator).setAffectsParentLayout(false);
    (*content).addView(separator);
    (*this).addView(content);
}
//CLASSGEN END REGION

void GroupHeader::onLoad(ALoadEvent &event)
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

    SharedReference<Legacy::Graphics::Texture> t = std::make_shared<Legacy::Graphics::Texture>();
    t->setPixmap(pixmap);
    t->setWrapping(Legacy::Graphics::TextureWrapping::TiledWrapping);
    t->load();

    separator->setImage(t);
    separator->setVerticalSizePolicy(SizePolicy::Fixed);
    separator->setSize({ 5, 5 });

    expandButton->addGestureRecognizer(std::make_shared<TouchGestureRecognizer>());
    expandButton->setImage(::UpButtonSmall);
    expandButton->collapse();
    /*expandButton->eventChannel.registerDelegate([this](TapGestureEvent &event) {
        isExpanded = !isExpanded;

        if (isExpanded)
        {
            expandButton->setImage(::UpButtonSmall);
        }
        else
        {
            expandButton->setImage(::DownButtonSmall);
        }
    });*/
}

void GroupHeader::addCustomButton(const SharedReference<Legacy::Graphics::Texture> &image, ADelegate<void(TapGestureEvent &event)> &&callback)
{
    auto view = std::make_shared<UI::ImageView>();
    view->setImage(image);
    view->addGestureRecognizer(std::make_shared<TouchGestureRecognizer>());
    view->eventChannel.registerDelegate([callback](TapGestureEvent &event) { //HACK: prevents stackoverflow
        callback(event);
    });
    view->setSizePolicy(UI::SizePolicy::ContentWrapped);
    content->addView(view);

    auto layoutData = content->getData();
    UI::FlexBoxData data;
    data.Alignment = Core::Alignment::Center;
    layoutData.push_back(data);
    content->setData(layoutData);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
