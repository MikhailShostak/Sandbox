#include "UIMenu.h"

#include <Graphics>
#include <UIDarkTheme>

#include "UIPerspectiveCamera.h"
#include "Includes/ViewWindow.gen.h"


namespace UI
{

AStaticRun(MenuViewMetaObject)
{
CLASSGEN_GENERATED_REGION_META_OBJECT
CLASSGEN_END_REGION
}
CLASSGEN_GENERATED_REGION_OBJECT
CLASSGEN_END_REGION


struct MenuManager : public ASingleton<MenuManager>
{
    Window window;

    MenuManager()
    {
        window.setFlags(WindowFlags::Menu);
    }
};

void MenuView::onLoad(ALoadEvent& event)
{
    Super::onLoad(event);

    hide();

    if (getGestureRecognizers().size() == 0)
    {

        list->setName("list");
        addGestureRecognizer(CreateShared<TouchGestureRecognizer>(ATouchID::Undefined));
        eventChannel.registerDelegate<TouchDownGestureEvent>([this](TouchDownGestureEvent &event) {
            if (!event.isInside())
            {
                hideMenu();
            }
        });
        list->useAddButton = false;
        list->useRemoveButton = false;
        list->setAdapter(this);
        addView(list);
    }

}

void MenuView::onUpdate(AUpdateEvent &event)
{
    View::onUpdate(event);
    //TODO: add layout
    list->setSize(getSize());
}

void MenuView::onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index)
{
    data[index].delegate(event);
    hideMenu();
}

void MenuView::hideMenu()
{
    if (!getOwner())
    {
        hide();
        return;
    }

    AWindow *thisWindow = getOwner()->getWindow();
    if (thisWindow == &MenuManager::getInstance().window)
    {
        thisWindow->hide();
    }
    else
    {
        hide();
    }
}

void AttachMenuToView(const SharedReference<UI::View> &view, const SharedReference<UI::View> &menu, ATouchID touchID, const MenuGeometryCallback &GeometryCallback)
{
    UI::TouchGestureRecognizer *menuRecognizer = new UI::TouchGestureRecognizer(touchID);
    view->addGestureRecognizer(SharedReference<UI::TouchGestureRecognizer>(menuRecognizer));
    view->eventChannel.registerDelegate<UI::TouchDownGestureEvent>([menuRecognizer](UI::TouchDownGestureEvent &event) {
        if (&event.getSender() != menuRecognizer)
        {
            return;
        }

        if (event.isInside())
        {
            event.accept();
        }
    });
    const WeakReference<UI::View> &viewPtr = view;
    view->eventChannel.registerDelegate<UI::TapGestureEvent>([menuRecognizer, viewPtr, menu, GeometryCallback](UI::TapGestureEvent &event) {
        if (&event.getSender() != menuRecognizer)
        {
            return;
        }

        Math::IntegerRectangle geometry;

        if (GeometryCallback)
        {
            geometry = GeometryCallback(event, SharedReference<UI::View>(viewPtr), menu);
        }
        else
        {
            geometry = Math::IntegerRectangle{
                event.getView().getOwner()->getWindow()->getGeometry().position + event.getWindowTouchEvent().getPosition(),
                { 200, 0, }
            };
        }

        SharedReference<UI::BorderImageView> background = CreateShared<UI::BorderImageView>();
        background->setImage(::ButtonBackground);
        background->setBorder({ 2, 2, 2, 2, });
        background->setSizePolicy(SizePolicy::Expanded);

        SharedReference<UI::Overlay> overlay = CreateShared<UI::Overlay>();
        overlay->setData({ {}, { UIOffsets{1,1,1,1} } });
        overlay->addView(background);
        overlay->addView(menu);

        Window &window = MenuManager::getInstance().window;
        window.setView(overlay);

        geometry.Size = Math::getMax2(overlay->getContentSize(), geometry.Size);
        window.setGeometry(geometry);

        window.show();

        menu->setPosition(Math::Vector());
        menu->show();

        menu->requestUpdate();
        event.accept();
    });
}

}
