#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include "AnchorView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class PreviewNodeView : public UI::Overlay
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PreviewNodeView This;
    typedef UI::Overlay Super;
    typedef void Interfaces;
protected:
    SharedReference<UI::View> Instance;
public:
    PreviewNodeView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::View> getInstance() const;
    void setInstance(SharedReference<UI::View> const &Instance);
    void setInstance(SharedReference<UI::View> &&Instance);
    SharedReference<UI::BorderImageView> borderView;
    void onHierarchyCreate();
//CLASSGEN END REGION
public:

	SharedReference<AnchorView> anchor = CreateShared<AnchorView>();

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        anchor->view = this;

        setEnabled(false);

        borderView->setImage(Graphics::Texture::getWhiteTexture());
        borderView->setColor(AColor::GrayColor());
        borderView->setFillCenter(false);
        borderView->setSizePolicy(UI::SizePolicy::Expanded);
        borderView->setBorder({ 1, 1, 1, 1 });
    }

protected:
    void onLayout(AUpdateEvent &event)
    {
        if (Instance)
        {
            if (Instance->getParent() != this)
            {
                this->insertView(1, Instance);

                setData({ {}, {} }); //HACK: serialization removes initial value...
            }
            /*instance->setPosition(Math::Vector{});
            instance->setSize(getSize());*/
            Instance->setVisibility(UI::Visibility::Inactive & UI::Visibility::Disabled);
            Instance->setSizePolicy(UI::SizePolicy::Expanded);
        }

        requestGraphicsUpdate();
        Super::onLayout(event);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
