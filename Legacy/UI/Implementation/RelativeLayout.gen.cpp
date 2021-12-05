//CLASSGEN GENERATED REGION: Includes
#include "RelativeLayout.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "Includes/Button.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
RelativeLayout::RelativeLayout()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void RelativeLayout::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void RelativeLayout::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
*/

void RelativeLayout::addInteranalConstraint(View &sourceView, const Constraint &constraint)
{
    auto &c = constraints[constraint.isHorizontal() ? 0 : 1];
    auto existedIt = std::find_if(c.begin(), c.end(), [&sourceView](const ViewContraintsData &data) {
        return data.view == &sourceView;
    });

    auto dependentIt = std::find_if(c.begin(), c.end(), [&sourceView](const ViewContraintsData &data) {
        for (auto &c : data.constraints)
        {
            if (&c.targetView.get() == &sourceView)
            {
                return true;
            }
        }
        return false;
    });

    if (dependentIt != c.end())
    {
        if (existedIt != c.end())
        {
            AAssert(existedIt < dependentIt, "Failed");
            existedIt->constraints.push_back(constraint);
        }
        else
        {
            c.insert(dependentIt, ViewContraintsData{ &sourceView, { constraint } });
        }
    }
    else
    {
        if (existedIt != c.end())
        {
            existedIt->constraints.push_back(constraint);
        }
        else
        {
            c.push_back(ViewContraintsData{ &sourceView, { constraint } });
        }
    }
}

void RelativeLayout::addConstraint(View &sourceView, ConstraintAnchor sourceAnchor, View &targetView, ConstraintAnchor targetAnchor, int32_t padding)
{
    addInteranalConstraint(sourceView, { sourceAnchor, targetView, targetAnchor, padding });
}

void RelativeLayout::addConstraint(View &sourceView, const Constraint &constraint)
{
    addInteranalConstraint(sourceView, constraint);
}

void RelativeLayout::addConstraints(View &sourceView, View &targetView, int32_t padding)
{
    addConstraint(sourceView, { ConstraintAnchor::Top, targetView, ConstraintAnchor::Top, padding });
    addConstraint(sourceView, { ConstraintAnchor::Right, targetView, ConstraintAnchor::Right, padding });
    addConstraint(sourceView, { ConstraintAnchor::Bottom, targetView, ConstraintAnchor::Bottom, padding });
    addConstraint(sourceView, { ConstraintAnchor::Left, targetView, ConstraintAnchor::Left, padding });
}

void RelativeLayout::addConstraints(View &sourceView, View &targetView, UIOffsets padding)
{
    addConstraint(sourceView, { ConstraintAnchor::Top, targetView, ConstraintAnchor::Top, padding.top });
    addConstraint(sourceView, { ConstraintAnchor::Right, targetView, ConstraintAnchor::Right, padding.right });
    addConstraint(sourceView, { ConstraintAnchor::Bottom, targetView, ConstraintAnchor::Bottom, padding.bottom });
    addConstraint(sourceView, { ConstraintAnchor::Left, targetView, ConstraintAnchor::Left, padding.left });
}

void RelativeLayout::removeConstraint(View &view, ConstraintAnchor anchor)
{
    auto &c = constraints[anchor == ConstraintAnchor::Left || anchor == ConstraintAnchor::Right ? 0 : 1];
    for (auto it = c.begin(); it != c.end(); ++it)
    {
        if (it->view == &view)
        {
            Array<Constraint> &viewConstraints = it->constraints;
            for (auto it = viewConstraints.begin(); it != viewConstraints.end(); ++it)
            {
                if (it->sourceAnchor == anchor)
                {
                    viewConstraints.erase(it);
                    break;
                }
            }

            if (viewConstraints.empty())
            {
                c.erase(it);
            }
            return;
        }
    }
}

void RelativeLayout::removeConstraintsForView(View &view)
{
    auto remove = [](Array<ViewContraintsData> &constraints, View &view) {
        for (auto it = constraints.begin(); it != constraints.end(); ++it)
        {
            if (it->view == &view)
            {
                constraints.erase(it);
                return;
            }
        }
    };

    remove(constraints[1], view);
    remove(constraints[0], view);
}

void RelativeLayout::removeAllConstraints()
{
    constraints[1].clear();
    constraints[0].clear();
}

Math::IntegerVector RelativeLayout::getContentSize() const
{
    /*if (parentView)
    {
        const_cast<RelativeLayout*>(this)->onLayout(*parentView);
    }*/

    int32_t left = std::numeric_limits<int32_t>::max();
    int32_t right = std::numeric_limits<int32_t>::min();
    int32_t top = std::numeric_limits<int32_t>::max();
    int32_t bottom = std::numeric_limits<int32_t>::min();


    /*for (ViewContraintsData &data : constraints[0])
    {
    Button *b = dynamic_cast<Button*>(data.view);
    if (b)
    {
    b->setText("");
    }
    }*/

    Map<View *, Math::IntegerRectangle> geometry;

    auto getTargetValueFromSize = [](const Math::IntegerVector &size, ConstraintAnchor anchor) {
        switch (anchor)
        {
        case ConstraintAnchor::Top:
        case ConstraintAnchor::Left:
            return 0;
        case ConstraintAnchor::Right:
            return size.x;
        case ConstraintAnchor::Bottom:
            return size.y;
        };
    };

    auto getTargetValueFromRectangle = [](const Math::IntegerRectangle &rectangle, ConstraintAnchor anchor) {
        switch (anchor)
        {
        case ConstraintAnchor::Top:
            return rectangle.getTop();
        case ConstraintAnchor::Right:
            return rectangle.getRight();
        case ConstraintAnchor::Bottom:
            return rectangle.getBottom();
        case ConstraintAnchor::Left:
            return rectangle.getLeft();
        };
    };

    auto getTargetValue = [this, &geometry, &getTargetValueFromRectangle, &getTargetValueFromSize](View &view, ConstraintAnchor anchor) {
        auto it = geometry.find(&view);
        if (it != geometry.end())
        {
            return getTargetValueFromRectangle(it->second, anchor);
        }

        if (&view != this->parentView)
        {
            return getTargetValueFromRectangle(view.getGeometry(), anchor);
        }

        return getTargetValueFromSize(view.getSize(), anchor);
    };

    Math::IntegerRectangle r;
    for (size_t mainDirection = 0; mainDirection < 2; ++mainDirection)
    {
        const size_t subDirection = mainDirection == 0 ? 1 : 0;

        size_t i = 0;
        for (const ViewContraintsData &data : constraints[mainDirection])
        {
            bool startProvided = false;
            bool endProvided = false;
            int32_t targetValueForStart = 0;
            int32_t targetValueForEnd = 0;
            for (const Constraint &c : data.constraints)
            {
                switch (c.sourceAnchor)
                {
                case ConstraintAnchor::Left:
                case ConstraintAnchor::Top:
                    targetValueForStart = getTargetValue(c.targetView, c.targetAnchor) + c.margin;
                    startProvided = true;
                    break;
                case ConstraintAnchor::Bottom:
                case ConstraintAnchor::Right:
                    targetValueForEnd = getTargetValue(c.targetView, c.targetAnchor) - c.margin;
                    endProvided = true;
                    break;
                default:
                    break;
                }
            }

            const View &v = *data.view;
            auto it = geometry.find(data.view);
            if (it == geometry.end())
            {
                geometry.insert({ data.view, Math::IntegerRectangle{} });
                it = geometry.find(data.view);
            }
            Math::IntegerRectangle &rect = it->second;

            /*Button *b = dynamic_cast<Button*>(data.view);
            if (b)
            {
            b->setText(b->getText() + String(mainDirection == 0 ? "h" : "v") + fmt::format("{}", i));
            }*/
            SizePolicy policy = mainDirection == 0 ? v.getHorizontalSizePolicy() : v.getVerticalSizePolicy();

            /*if (policy == SizePolicy::Expanded && startProvided && endProvided)
            {
                rect.size[mainDirection] = std::max<int32_t>(v.getContentSize()[mainDirection], targetValueForEnd - targetValueForStart);
            }
            else if (policy == SizePolicy::ContentWrapped)
            {
                rect.size[mainDirection] = v.getContentSize()[mainDirection];
            }*/

            rect.size[mainDirection] = v.getMinimalSize()[mainDirection];

            if (startProvided)
            {
                rect.position[mainDirection] = targetValueForStart;
            }
            else if (endProvided)
            {
                //TODO: should be minimal left size
                rect.position[mainDirection] = 0;// targetValueForEnd - s[mainDirection];
            }
            ++i;
        }
    }

    for (const std::pair<View *, Math::IntegerRectangle> &pair : geometry)
    {
        left = std::min<int32_t>(left, pair.second.getLeft());
        right = std::max<int32_t>(right, pair.second.getRight());
        top = std::min<int32_t>(top, pair.second.getTop());
        bottom = std::max<int32_t>(bottom, pair.second.getBottom());
    }

    return Math::IntegerVector{ right - left, bottom - top };
}

void RelativeLayout::onLayout(View &thisView)
{
    auto getValue = [&thisView](View &view, ConstraintAnchor anchor) -> int {
        switch (anchor)
        {
        case ConstraintAnchor::Top:
            return (&thisView != &view ? view.getGeometry().getTop() : 0);
        case ConstraintAnchor::Right:
            return (&thisView != &view ? view.getGeometry().getRight() : view.getSize().x);
        case ConstraintAnchor::Bottom:
            return (&thisView != &view ? view.getGeometry().getBottom() : view.getSize().y);
        case ConstraintAnchor::Left:
            return (&thisView != &view ? view.getGeometry().getLeft() : 0);
        }
    };

    /*for (ViewContraintsData &data : constraints[0])
    {
        Button *b = dynamic_cast<Button*>(data.view);
        if (b)
        {
            b->setText("");
        }
    }*/

    Math::IntegerRectangle rectangle;
    for (size_t mainDirection = 0; mainDirection < 2; ++mainDirection)
    {
        const size_t subDirection = mainDirection == 0 ? 1 : 0;

        size_t i = 0;
        for (ViewContraintsData &data : constraints[mainDirection])
        {
            bool startProvided = false;
            bool endProvided = false;
            int32_t targetValueForStart = 0;
            int32_t targetValueForEnd = 0;
            for (const Constraint &c : data.constraints)
            {
                switch (c.sourceAnchor)
                {
                case ConstraintAnchor::Left:
                case ConstraintAnchor::Top:
                    targetValueForStart = getValue(c.targetView, c.targetAnchor) + c.margin;
                    startProvided = true;
                    break;
                case ConstraintAnchor::Bottom:
                case ConstraintAnchor::Right:
                    targetValueForEnd = getValue(c.targetView, c.targetAnchor) - c.margin;
                    endProvided = true;
                    break;
                default:
                    break;
                }
            }

            View &v = *data.view;
            /*Button *b = dynamic_cast<Button*>(data.view);
            if (b)
            {
                b->setText(b->getText() + String(mainDirection == 0 ? "h" : "v") + fmt::format("{}", i));
            }*/
            SizePolicy policy = mainDirection == 0 ? v.getHorizontalSizePolicy() : v.getVerticalSizePolicy();

            Math::Vector p = v.getPosition();
            Math::IntegerVector s = v.getSize();
            if (policy == SizePolicy::Expanded && startProvided && endProvided)
            {
                s[mainDirection] = std::max<int32_t>(v.getContentSize()[mainDirection], targetValueForEnd - targetValueForStart);
            }
            else if (policy == SizePolicy::ContentWrapped)
            {
                s[mainDirection] = v.getContentSize()[mainDirection];
            }

            if (startProvided && endProvided)
            {
                p[mainDirection] = (targetValueForStart + targetValueForEnd - s[mainDirection]) / 2;
            }
            else
            {
                if (startProvided)
                {
                    p[mainDirection] = targetValueForStart;
                }
                else if (endProvided)
                {
                    p[mainDirection] = targetValueForEnd - s[mainDirection];
                }
            }
            v.setSize(s);
            v.setPosition(p);
            ++i;
        }

    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
