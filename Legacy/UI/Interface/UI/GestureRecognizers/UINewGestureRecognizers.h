#pragma once

#include "UIGestureRecognizer.h"

#include "Core/AWindow.h"
#include "UI/Views/UILine.h"

namespace UI
{

class SwipeGestureRecognizer : public GestureRecognizer
{
protected:
    Math::IntegerVector startPosition;
    Math::IntegerVector startScrollPosition;
    bool isActive = false;
public:
    virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isInside)
        {
            return;
        }

        isActive = true;
        startPosition = point;
        auto &v = static_cast<UI::ScrollView &>(getView());
        startScrollPosition = { v.horizontalSlider->getHandlePosition(), v.verticalSlider->getHandlePosition() };
    }

    virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        Math::IntegerVector offset = point - startPosition;
        auto &v = static_cast<UI::ScrollView &>(getView());
        v.horizontalSlider->setHandlePosition(startScrollPosition.X - offset.X);
        v.verticalSlider->setHandlePosition(startScrollPosition.Y - offset.Y);
        event.accept();
    }

    virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        isActive = false;
        event.accept();
    }
};

class RubberBandSelection : public GestureRecognizer
{
    Math::IntegerVector startPosition;
    SharedReference<BorderImageView> selectionView = std::make_shared<BorderImageView>();
    Array<SharedReference<View>> selectedViews;
    bool isActive = false;
public:
    ADelegate<View &()> requestContentView; //TODO: remove hack
    ADelegate<bool(const SharedReference<View> &view)> predicate;
    ADelegate<void(Array<SharedReference<View>> selectedViews)> selectionUpdated;

    RubberBandSelection()
    {
        APixmap pixmap;
        pixmap.setBuffer({
            255, 255,
            255, 255,
            255, 255,

            255, 255,
            255, 100,
            255, 255,

            255, 255,
            255, 255,
            255, 255,
            }, Math::IntegerVector{ 3, 3 }, APixmapDataFormat::GrayAlpha);
        SharedReference<Legacy::Graphics::Texture> image = std::make_shared<Legacy::Graphics::Texture>();
        image->setPixmap(pixmap);
        image->setFiltration(Legacy::Graphics::TextureFiltration::Nearest);
        selectionView->setImage(image);
        selectionView->setBorder({ 1, 1, 1, 1 });
        selectionView->setColor(AColor::GrayColor());
    }

    virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (isInside)
        {
            getView().getOwner()->getWindow()->removeFocus();
            startPosition = point;
            getView().addView(selectionView);
            isActive = true;

            selectionView->setPosition(startPosition.getXY<Math::Vector>());
            selectionView->setSize(Math::IntegerVector{});

            selectionUpdated({});

            event.accept();
        }
    }

    virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        selectionView->setPosition(startPosition.getXY<Math::Vector>());
        selectionView->setSize(Math::clamp2(point - startPosition, -startPosition, getView().getSize() - startPosition));

        selectedViews.clear();
        auto &contentView = requestContentView();
        selectedViews.reserve(contentView.getViews().size());
        for (const auto &view : contentView.getViews())
        {
            if (!predicate || predicate(view))
            {
                auto intesectRectangles = [](const Math::IntegerVector a1, const Math::IntegerVector a2, const Math::IntegerVector b1, const Math::IntegerVector b2) {
                    return a1.X < b2.x
                        && a2.x > b1.x
                        && a1.Y < b2.Y
                        && a2.Y > b1.Y;
                };

                auto intesectRectangles2 = [](const Math::IntegerRectangle &a, const Math::IntegerRectangle &b) {
                    return a.position.X < b.position.x + b.size.x
                        && a.position.x + a.size.x > b.position.x
                        && a.position.Y < b.position.Y + b.size.Y
                        && a.position.Y + a.size.Y > b.position.Y;
                };

                auto topLeft = startPosition;
                auto bottomRight = point;
                if (bottomRight.X < topLeft.X)
                {
                    std::swap(topLeft.X, bottomRight.X);
                }
                if (bottomRight.Y < topLeft.Y)
                {
                    std::swap(topLeft.Y, bottomRight.Y);
                }

                if (intesectRectangles(topLeft, bottomRight, view->getPosition().getXY<Math::IntegerVector>(), view->getPosition().getXY<Math::IntegerVector>() + view->getSize())) //TODO:replace with shape cast
                {
                    selectedViews.push_back(view);
                }
            }
        }

        if (selectionUpdated)
        {
            selectionUpdated(selectedViews);
        }
    }

    virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        selectionView->removeFromParent();
        isActive = false;
    }
};

class SignleSelection : public GestureRecognizer
{
public:
    ADelegate<void(SharedReference<View> selectedView, AWindowTouchDownEvent &event)> selectionUpdated;
    ADelegate<bool(const SharedReference<View> &view)> predicate;
    bool acceptEvents = false;
    virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (isInside)
        {
            getView().getOwner()->getWindow()->removeFocus();
            for (auto &pair : views)
            {
                if (predicate && !predicate(pair.first))
                {
                    continue;
                }

                if (acceptEvents)
                {
                    event.accept();
                }

                if (selectionUpdated)
                {
                    selectionUpdated(pair.first, event);
                }
                break;
            }
        }
    }
};

class Highlighting : public GestureRecognizer
{
    WeakReference<View> activeView;
public:

    using GestureRecognizer::GestureRecognizer;

    ADelegate<bool(const SharedReference<View> &view)> predicate;

    ADelegate<void(SharedReference<View> view)> entered;
    ADelegate<void(SharedReference<View> view)> exited;

    bool acceptEvents = false;

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        /*TouchMoveGestureEvent e(*this, event, getView(), point, isInside);
        if (sendAcceptableEventToView(e))
        {
            event.accept();
        }*/
        SharedReference<View> activeView = this->activeView.lock();
        if (!activeView && !isInside)
        {
            return;
        }

        auto isInisideAABB = [](const Math::IntegerVector p, const Math::IntegerVector v1, const Math::IntegerVector v2) {
            return v1.X < p.X && p.X < v2.X
                && v1.Y < p.Y && p.Y < v2.Y;
        };

        for (auto &pair : views)
        {
            if (predicate && !predicate(pair.first))
            {
                continue;
            }

            if (isInisideAABB(pair.second, { 0, 0 }, pair.first->getSize()))
            {
                if (activeView == pair.first)
                {
                    return;
                }

                if (activeView)
                {
                    exited(activeView);
                }

                if (acceptEvents)
                {
                    event.accept();
                }
                activeView = pair.first;
                entered(activeView);
                return;
            }
        }

        exited(activeView);
        activeView = nullptr;
    }
};

class GroupMovement : public GestureRecognizer
{
    Math::IntegerVector startPoisition;
    bool isActive = false;
    Array<Math::Vector> positions;
public:
    Math::FloatType gridSize = 0;
    Array<SharedReference<View>> views;
    virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isInside)
        {
            return;
        }

        for (auto &pair : views) //TODO: use first element
        {
            if (ranges::find(this->views, pair.first) == this->views.end())
            {
                continue;
            }

            startPoisition = point;
            isActive = true;

            positions.clear();
            positions.reserve(views.size());
            for (const auto &view : this->views)
            {
                positions.emplace_back(view->getPosition());
            }

            event.accept();
        }
    }

    virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        Math::IntegerVector offset = point - startPoisition;
        for (size_t i = 0; i < this->views.size(); ++i)
        {
            this->views[i]->setPosition(Math::snapToGrid2(positions[i] + offset.getXY<Math::Vector>(), gridSize));
        }
    }

    virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        isActive = false;
    }
};

class SingleMovement : public GestureRecognizer
{
    Math::IntegerVector startPoisition;
    Math::Vector viewPosition;
    SharedReference<View> view;
    bool isActive = false;
public:
    Math::FloatType gridSize = 0;
    ADelegate<bool(const SharedReference<View> &view)> predicate;
    virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isInside)
        {
            return;
        }

        for (auto &pair : views) //TODO: should it select top view instead of search?
        {
            if (predicate && !predicate(pair.first))
            {
                continue;
            }

            startPoisition = point;
            view = pair.first;
            viewPosition = view->getPosition();
            isActive = true;

            event.accept();
            break;
        }
    }

    virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        Math::IntegerVector offset = point - startPoisition;
        view->setPosition(Math::snapToGrid2(viewPosition + offset.getXY<Math::Vector>(), gridSize));
    }

    virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        view = nullptr;
        isActive = false;
    }
};

class Linking : public GestureRecognizer
{
    SharedReference<View> sourceView;
    bool isActive = false;
public:

    SharedReference<Line> line = std::make_shared<Line>();

    ADelegate<bool(const SharedReference<View> &view)> sourcePredicate;
    ADelegate<bool(const SharedReference<View> &view)> targetPredicate;
    ADelegate<void(const SharedReference<View> &sourceView, const SharedReference<View> &targetView)> linked;

    virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isInside)
        {
            return;
        }

        for (auto &pair : views) //TODO: should it select top view instead of search?
        {
            if (sourcePredicate && !sourcePredicate(pair.first))
            {
                continue;
            }

            line->sourceAnchor.offset = point.getXY<Math::Vector>();
            line->destinationAnchor.offset = point.getXY<Math::Vector>();
            getView().addView(line);
            sourceView = pair.first;

            isActive = true;
            event.accept();
            break;
        }
    }

    virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        line->destinationAnchor.offset = point.getXY<Math::Vector>();
    }

    virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isActive)
        {
            return;
        }

        for (auto &pair : views)
        {
            if (targetPredicate && !targetPredicate(pair.first))
            {
                continue;
            }

            linked(sourceView, pair.first);
            break;
        }

        line->removeFromParent();
        isActive = false;
    }
};

}
