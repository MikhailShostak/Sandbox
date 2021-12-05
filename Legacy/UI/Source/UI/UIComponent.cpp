#include "UIComponent.h"
#include <Graphics>
#include <Fonts>
#include <Console>
#include <UIDarkTheme>

#include "UIBundle.h"

#include "TextField.gen.h"
#include "Button.gen.h"
#include "Label.gen.h"
#include "UILine.h"
#include "ScrollView.gen.h"
#include "UIResizeGestureRecognizer.h"
#include "TabView.gen.h"
#include "Slider.gen.h"
#include "ProgressBar.gen.h"

//HACK
#include "UIApplication.h"
AOperationDispatcher &getOperationDispatcher()
{
    return UIApplication::getOperationDispatcher();
}

namespace UI
{

ConsoleVariable<bool> UICollisions{ false, "UI.Collisions" };

void Component::loadDefaultStyle()
{
    {
        AObject obj;
        ALoadEvent e(obj);
        UIBundle::getInstance().sendEvent(e);
    }

    Core::FontEngine::getInstance().load(getAsset("NotoSansUI_Regular"));
    Core::Font DefaultFont("Noto Sans UI", "Regular", 12);

    AddStyleProperty<UI::TextField>(&UI::TextField::setBackgroundImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::FieldImage));
    AddStyleProperty<UI::TextField>(&UI::TextField::setBorder, UIOffsets{ 8, 8, 8, 8 });
    AddStyleProperty<UI::TextField>(&UI::TextField::setFont, DefaultFont);
    AddStyleProperty<UI::TextField>(&UI::TextField::setPlaceholderColor, AColor::fromHex(0xFFAAAAAA));

    AddStyleProperty<UI::Line>(&UI::Line::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::LineImage));
    AddStyleProperty<UI::Line>(&UI::Line::setBorder, UIOffsets{ 6, 10, 6, 10 });

    /*AddStyleProperty<UI::Button>(&UI::Button::setTextAlign, Core::TextAlign::Center);
    AddStyleProperty<UI::Button>(&UI::Button::setTextColor, AColor::fromHex(0xFFFFFFFF));
    AddStyleProperty<UI::Button>(&UI::Button::setFont, DefaultFont);
    AddStyleProperty<UI::Button>(&UI::Button::setImage, SharedReference<Legacy::Graphics::Texture>(::Button));
    AddStyleProperty<UI::Button>(&UI::Button::setBorder, UIOffsets{ 8, 8, 8, 8 });
    AddStyleProperty<UI::Button>(&UI::Button::setSize, Math::IntegerVector{ 86, 26 });*/

    AddStyleProperty<UI::Label>(&UI::Label::setFont, DefaultFont);
    AddStyleProperty<UI::Label>(&UI::Label::setColor, AColor::fromHex(0xFFFFFFFF));

    //AddStyleProperty<UI::ScrollView>(&UI::ScrollView::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::ListImage));
    //AddStyleProperty<UI::ScrollView>(&UI::ScrollView::setBorder, UIOffsets{ 4, 4, 4, 4 });
    //AddStyleProperty<UI::ScrollView>(&UI::ScrollView::setFillCenter, false);
    //AddStyleProperty<UI::ItemView<UI::ItemAdapter>>(&UI::ItemView<UI::ItemAdapter>::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::ListImage));
    //AddStyleProperty<UI::ItemView<UI::ItemAdapter>>(&UI::ItemView<UI::ItemAdapter>::setBorder, UIOffsets{ 4, 4, 4, 4 });

    /*AddStyleProperty<UI::NodeLayoutItem>(&UI::NodeLayoutItem::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::ListImage));
    AddStyleProperty<UI::NodeLayoutItem>(&UI::NodeLayoutItem::setHighlightingImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::ListHighlightingImage));
    AddStyleProperty<UI::NodeLayoutItem>(&UI::NodeLayoutItem::setBorder, UIOffsets{ 4, 4, 4, 4 });
    AddStyleProperty<UI::NodeLayoutItem>(&UI::NodeLayoutItem::setTextAlign, Core::TextAlign::Center);*/

    AddStyleProperty<UI::ResizeGestureRecognizer>(&UI::ResizeGestureRecognizer::setControlPointImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::ControlPointImage));
    AddStyleProperty<UI::ResizeGestureRecognizer>(&UI::ResizeGestureRecognizer::setControlPointSize, Math::IntegerVector{ 10, 10 });

    /*AddStyleProperty<UI::Slider>(&UI::Slider::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::BackgroundBlackImage));
    AddStyleProperty<UI::Slider>(&UI::Slider::setBorder, UIOffsets{ 4, 4, 4, 4 });
    AddStyleProperty<UI::Slider>(&UI::Slider::setSliderImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::SliderImage));
    AddStyleProperty<UI::Slider>(&UI::Slider::setSliderBorder, UIOffsets{ 4, 4, 4, 4 });*/

    AddStyleProperty<UI::ProgressBar>(&UI::ProgressBar::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::BackgroundBlackImage));
    AddStyleProperty<UI::ProgressBar>(&UI::ProgressBar::setBorder, UIOffsets{ 4, 4, 4, 4 });
    AddStyleProperty<UI::ProgressBar>(&UI::ProgressBar::setProgressImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::ProgressImage));
    AddStyleProperty<UI::ProgressBar>(&UI::ProgressBar::setProgressBorder, UIOffsets{ 4, 4, 4, 4 });

    //AddStyleProperty(&UI::DialogView::setImage, UIBundle::getInstance().findObject<Legacy::Graphics::Texture>(Assets::DialogImage));
    //AddStyleProperty(&UI::DialogView::setBorder, UIOffsets{ 48, 32, 32, 32 });

    /*AddStyleProperty(&UI::LayoutNodeView::setImage, t);
    AddStyleProperty(&UI::LayoutNodeView::setBorder, UIOffsets{ 4, 4, 4, 4 });*/
}

void Component::onLoad(ALoadEvent &event)
{
    static bool registered = false;
    if (!registered)
    {
        registered = true;

        Core::Shortcut s;
        s.KeyModifier = Core::KeyModifier::Ctrl;

        s.KeyCode = 49;
        getWindow()->Shortcuts.push_back({ s, []() {
            Console::getInstance().applyCommand("Debug.CaptureViewHierarchy");
        } });

        s.KeyCode = 50;
        getWindow()->Shortcuts.push_back({ s, []() {
            Console::getInstance().applyCommand("Debug.ViewObjects");
        } });

        s.KeyCode = 51;
        getWindow()->Shortcuts.push_back({ s, []() {
            Console::getInstance().applyCommand("Debug.CountObjects");
        } });
    }

    AVisualComponent::onLoad(event);
    registerInput();

    if (!getSprite()->isLoaded())
    {
        getSprite()->load();
    }
    if (!getPlaceholderImage()->isLoaded())
    {
        getPlaceholderImage()->load();
    }

    if (view)
    {
        view->sendEvent(event);
    }
}

void Component::onUnload(AUnloadEvent &event)
{
    if (view)
    {
        view->sendEvent(event);
    }

    unregisterInput();
    AVisualComponent::onUnload(event);
}

void Component::onDraw(AUpdateEvent &event)
{
    //getRenderer().addMesh(getOwner().getMatrix() * Math::Matrix(Math::IntegerVector(size.x, size.y)), getSprite(), material);
    update(); //TODO: remove this update for safe performance and implement smart rendering

    view->setSize(ACamera::getCurrentCamera()->resolution);
    if (view && !view->getViews().empty())
    {
        view->getViews().front()->setSize(ACamera::getCurrentCamera()->resolution);
        view->sendEvent(event);
    }
}

bool Raycast::worldCast(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<View> &view)
{
    clear();
    castInternal(startWorldPoint, endWorldPoint, view);
    return !report.results.empty();
}

bool Raycast::screenCast(const Math::IntegerVector &screenPoint, const SharedReference<View> &view)
{
    const auto &&start = mapFromScreenSpaceToWorldSpace(*view->getOwner()->getSpace(), screenPoint, 1.0f);
    const auto &&end = mapFromScreenSpaceToWorldSpace(*view->getOwner()->getSpace(), screenPoint, -1.0f);
    return worldCast(start, end, view);
}

void Raycast::castInternal(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<View> &view)
{
    if (!view->isVisible() || !view->isEnabled() || !view->isExpanded())
    {
        return;
    }

    for (auto it = view->getViews().rbegin(); it != view->getViews().rend(); ++it)
    {
        castInternal(startWorldPoint, endWorldPoint, *it);
    }

    const Math::Vector planePosition = Math::Vector{ 0, 0, 0 };
    const Math::Vector planeNormal = Math::Vector{ 0, 0, -1 };

    Math::Vector contactPoint;
    bool isInside = false;
    if (Math::intersectRayWithPlane(mapFromWorldSpaceToLocalSpace(*view, startWorldPoint), mapFromWorldSpaceToLocalSpace(*view, endWorldPoint), planePosition, planeNormal, contactPoint))
    {
        //TODO: const Math::BoundingVolume &spriteBV = getSprite().getBoundingVolume();
        if (0.0f <= contactPoint.x && contactPoint.x <= 1.0f && 0.0f <= contactPoint.y && contactPoint.y <= 1.0f)
        {
            isInside = true;
        }
    }

    report.results.push_back(CollisionInfo{ isInside, Collision{ view, Math::IntegerVector{
        static_cast<int32_t>(view->getSize().x * contactPoint.x),
        static_cast<int32_t>(view->getSize().y * contactPoint.y)
    } } });
}

template<typename EventType>
void processTouchEvent(EventType &event, const SharedReference<View> &view, void(*callback)(EventType &event, GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views))
{
    Raycast raycast;
    if (raycast.screenCast(event.getPosition(), view))
    {
        Array<Collision> collisions = raycast.getReport().getFilteredCollisions(true);
        size_t index = 0;
        for (const CollisionInfo &info : raycast.getReport().results)
        {
            const bool isInside = info.first;
            const Collision &collision = info.second;
            const SharedReference<View> &view = collision.first;
            const Math::IntegerVector &point = collision.second;

            if (UICollisions && isInside)
            {

                float depth = float(index) / collisions.size();
                UIVisualDebug().drawMeshWireframe(view->getGraphicsMatrix(), Component::getSprite(), AColor(2.0f * (1.0f - depth), 2.0f * depth, 0.0f, 1.0f));
                ++index;
            }

            for (auto it = view->getGestureRecognizers().rbegin(); it != view->getGestureRecognizers().rend(); ++it)
            {
                (callback)(event, **it, point, isInside, collisions);
                if (event.isAccepted())
                {
                    return;
                }
            }
        }
    }
}

void Component::onTouchDown(AWindowTouchDownEvent &event)
{
    if (!view)
    {
        return;
    }

    processTouchEvent<AWindowTouchDownEvent>(event, view, [](AWindowTouchDownEvent &event, GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (recognizer.shouldProcessTouchDown(event))
        {
            recognizer.onTouchDown(event, point, isInside, views);
        }
    });
}

void Component::onTouchMove(AWindowTouchMoveEvent &event)
{
    if (!view)
    {
        return;
    }

    processTouchEvent<AWindowTouchMoveEvent>(event, view, [](AWindowTouchMoveEvent &event, GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        recognizer.onTouchMove(event, point, isInside, views);
    });
}

void Component::onTouchUp(AWindowTouchUpEvent &event)
{
    if (!view)
    {
        return;
    }

    processTouchEvent<AWindowTouchUpEvent>(event, view, [](AWindowTouchUpEvent &event, GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        recognizer.onTouchUp(event, point, isInside, views);
    });
}

void Component::onTouchWheel(AWindowTouchWheelEvent &event)
{
    if (!view)
    {
        return;
    }

    processTouchEvent<AWindowTouchWheelEvent>(event, view, [](AWindowTouchWheelEvent &event, GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) {
        recognizer.onTouchWheel(event, point, isInside, views);
    });
}

void Component::registerInput()
{
    getWindow()->inputEventChannel.registerObserver(*this);
}

void Component::unregisterInput()
{
    getWindow()->inputEventChannel.unregisterObserver(*this);
}

}
