#pragma once

#include <UI>

using Collision = APair<SharedReference<UI::View>, Math::IntegerVector>;
using CollisionInfo = APair<bool, Collision>;

struct RaycastReport
{
    Array<CollisionInfo> results;

    Array<Collision> getFilteredCollisions(bool hit) const
    {
        Array<Collision> filteredCollisions;
        for (const CollisionInfo &info : results)
        {
            if (info.first == hit)
            {
                filteredCollisions.push_back(info.second);
            }
        }
        return filteredCollisions;
    }
};

class Raycast
{
    RaycastReport report;
public:
    const RaycastReport &getReport() const { return report; }

    bool cast(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<UI::View> &view);

    bool worldCast(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<UI::View> &view);
    bool screenCast(const ACamera &camera, const Math::IntegerVector &screenPoint, const SharedReference<UI::View> &view);

    void clear() { report.results.clear(); }
private:
    void castInternal(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<UI::View> &view);
};

template<typename EventType>
inline void processTouchEvent(EventType &event, const ACamera &camera, const SharedReference<UI::View> &view, void(*callback)(EventType &event, UI::GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<UI::View>, Math::IntegerVector>> &views))
{
    Raycast raycast;
    if (raycast.screenCast(camera, event.getPosition(), view))
    {
        Array<Collision> collisions = raycast.getReport().getFilteredCollisions(true);
        size_t index = 0;
        for (const CollisionInfo &info : raycast.getReport().results)
        {
            const bool isInside = info.first;
            const Collision &collision = info.second;
            const SharedReference<UI::View> &view = collision.first;
            const Math::IntegerVector &point = collision.second;

            /*if (UICollisions && isInside)
            {

                float depth = float(index) / collisions.size();
                UIVisualDebug().drawMeshWireframe(view->getGraphicsMatrix(), Component::getSprite(), AColor(2.0f * (1.0f - depth), 2.0f * depth, 0.0f, 1.0f));
                ++index;
            }*/

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
