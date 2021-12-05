//CLASSGEN GENERATED REGION: Includes
#include "GridView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include <Graphics>

//CLASSGEN END REGION
#include "Includes/BorderImageView.gen.h"
#include "Includes/ScrollView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GridView::GridView()
{
    UI::OverlayData item_489_0;
    UI::OverlayData item_490_1;
    (*this).setData({item_489_0,item_490_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GridView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void GridView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GridView::onHierarchyCreate()
{
    SharedReference<UI::ImageView> background = SharedReference<UI::ImageView>(Create<UI::ImageView>([this](UI::ImageView *v)
    {
    }
));
    (*background).setName("Background");
    {
    }
    (*background).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).background = background;
    Super::onHierarchyCreate();
    setName("GridView");
}
//CLASSGEN END REGION

void GridView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    updateGrid();
    if (auto scrollView = DynamicCast<UI::ScrollView>(root))
    {
        scrollView->onScrollChanged = [this]() {
            updateScroll();
        };
    }
}
void GridView::updateGrid()
{
    Math::IntegerVector size{ 200, 200, 1 };
    APixmap pixmap;
    pixmap.setBuffer(Array<uint8_t>(size.getArea3()), size, APixmapDataFormat::Gray);

    if (checkVisibility)
    {
        drawCheck(pixmap, 10, 0, AColor::fromBytes(48), AColor::fromBytes(51));
        drawCheck(pixmap, 100, 0, AColor(0.9f, 1.0f), Blending::Multiply);
    }
    else
    {
        drawCheck(pixmap, 1, 0, AColor::fromBytes(48), AColor::fromBytes(48));
    }

    if (gridVisibility)
    {
        drawGrid(pixmap, 10, 0, AColor(0.9f, 1.0f), Blending::Multiply);
        drawGrid(pixmap, 100, 0, AColor(0.8f, 1.0f), Blending::Multiply);
    }

    SharedReference<Legacy::Graphics::Texture> texture = SharedReference<Legacy::Graphics::Texture>(Create<Legacy::Graphics::Texture>());
    texture->setPixmap(pixmap);
    texture->setWrapping(Legacy::Graphics::TextureWrapping::TiledWrapping);
    texture->load();
    StaticCast<ImageView>(background)->setImage(texture);
}

void GridView::updateScroll()
{
    auto scrollView = StaticCast<UI::ScrollView>(root);
    auto scrollOffset = scrollView->getScrollOffset();
    auto center = scrollView->getSurfacePosition(Math::Vector{ 0.5f, 0.5f });
    StaticCast<ImageView>(background)->setImageOffset(
        Math::remap2<Math::FloatType>(
            -center + scrollOffset,
            center + Math::Constants::NullVector,
            center + StaticCast<ImageView>(background)->getImage()->getSize().getXY<Math::Vector>()
        )
    );
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
