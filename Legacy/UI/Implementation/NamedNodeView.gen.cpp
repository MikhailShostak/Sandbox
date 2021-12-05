//CLASSGEN GENERATED REGION: Includes
#include "NamedNodeView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "FlexBox.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "Direction.gen.h"
#include "Overlay.gen.h"
#include "BorderImageView.gen.h"
#include "Label.gen.h"

//CLASSGEN END REGION
#include <Graphics>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
NamedNodeView::NamedNodeView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NamedNodeView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void NamedNodeView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NamedNodeView::onHierarchyCreate()
{
    SharedReference<UI::FlexBox> root = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*root).setName("Root");
    {
    }
    UI::FlexBoxData item_426_0;
    UI::FlexBoxData item_427_1;
    (*root).setData({item_426_0,item_427_1,});
    (*root).setDirection(UI::Direction::Vertical);
    SharedReference<UI::Overlay> header = CreateShared<UI::Overlay>([this](UI::Overlay *v)
    {
    }
);
    (*header).setName("Header");
    {
    }
    UI::OverlayData item_430_0;
    UI::OverlayData item_431_1;
    Math::Offsets padding_432;
    padding_432.Top = 4.000000;
    padding_432.Right = 8.000000;
    padding_432.Bottom = 4.000000;
    padding_432.Left = 8.000000;
    item_431_1.Padding = padding_432;
    (*header).setData({item_430_0,item_431_1,});
    headerBackground = CreateShared<UI::BorderImageView>([this](UI::BorderImageView *v)
    {
    }
);
    (*headerBackground).setName("HeaderBackground");
    {
    }
    (*headerBackground).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*headerBackground).setUseOriginalContentSize(false);
    (*header).addView(headerBackground);
    title = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*title).setName("Title");
    {
    }
    (*header).addView(title);
    (*root).addView(header);
    if (content)
    {
        (*root).addView(content);
    }
    else
    {
        SharedReference<UI::Label> defaultContent = CreateShared<UI::Label>([this](UI::Label *v)
        {
        }
);
        (*defaultContent).setName("DefaultContent");
        {
        }
        (*root).addView(defaultContent);
        content = defaultContent;
    }
    (*this).root = root;
    Super::onHierarchyCreate();
    setName("NamedNodeView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
