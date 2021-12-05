#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"

//CLASSGEN END REGION
#include <functional>
#include "UI/UILayout.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class RelativeLayout : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef RelativeLayout This;
    typedef UI::View Super;
    typedef void Interfaces;
public:
    RelativeLayout();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};
*/

enum class ConstraintAnchor
{
    Top,
    Right,
    Bottom,
    Left,
    VerticalBaseLine,
    HorizontalBaseLine,
    Baseline = VerticalBaseLine
};

struct Constraint final
{
    ConstraintAnchor sourceAnchor = ConstraintAnchor::Top;
    std::reference_wrapper<View> targetView;
    ConstraintAnchor targetAnchor = ConstraintAnchor::Bottom;
    int margin = 0;

    bool isHorizontal() const { return sourceAnchor == ConstraintAnchor::Left || sourceAnchor == ConstraintAnchor::Right; }
    bool isVertical() const { return !isHorizontal(); }
};

class RelativeLayout : public Layout
{
    struct ViewContraintsData
    {
        View *view;
        Array<Constraint> constraints;
    };
    std::array<Array<ViewContraintsData>, 2> constraints;
    View *parentView = nullptr;
public:
    using Super = Layout;
    using This = RelativeLayout;

    Math::IntegerVector getContentSize() const override;

    void load(View &parent) override { Super::load(parent); parentView = &parent; }
    void unload() override { Super::unload(); parentView = nullptr; }

    void addConstraint(View &sourceView, ConstraintAnchor sourceAnchor, View &targetView, ConstraintAnchor targetAnchor, int32_t padding = 0);
    void addConstraint(View &sourceView, const Constraint &constraint);
    void addConstraints(View &sourceView, View &targetView, int32_t padding = 0);
    void addConstraints(View &sourceView, View &targetView, UIOffsets padding);

    void removeConstraint(View &view, ConstraintAnchor anchor);
    void removeConstraintsForView(View &view);

    void removeAllConstraints();

    void onLayout(View &view) override;

private:
    void addInteranalConstraint(View &sourceView, const Constraint &constraint);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
