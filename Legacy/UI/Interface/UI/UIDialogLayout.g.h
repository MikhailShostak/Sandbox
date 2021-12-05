/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include "Includes/View.gen.h"
#include "Includes/BorderImageView.gen.h"
#include "Includes/Label.gen.h"
#include "Includes/RelativeLayout.gen.h"

namespace UI
{

class DialogLayout : public RelativeLayout
{
    typedef UI::RelativeLayout Super;
    typedef DialogLayout This;
public:
    SharedReference<BorderImageView> backgroundImageView = SharedReference<BorderImageView>(Create<BorderImageView>());
    SharedReference<Label> titleLabel = SharedReference<Label>(Create<Label>());
    //SharedReference<ButtonGroup> buttonGroup = new ButtonGroup();

    DialogLayout(View &view)
    {
        auto *parent = &view;
        backgroundImageView->setName("backgroundImageView");
        backgroundImageView->setSizePolicy(UI::SizePolicy::Expanded);
        view.addView(backgroundImageView);
        titleLabel->setName("titleLabel");
        titleLabel->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        view.addView(titleLabel);
        /*buttonGroup->setName("buttonGroup");
        buttonGroup->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);
        view.addView(buttonGroup);*/
        addConstraint(*backgroundImageView, {UI::ConstraintAnchor::Top, *parent, UI::ConstraintAnchor::Top, 0});
        addConstraint(*backgroundImageView, {UI::ConstraintAnchor::Right, *parent, UI::ConstraintAnchor::Right, 0});
        addConstraint(*backgroundImageView, {UI::ConstraintAnchor::Bottom, *parent, UI::ConstraintAnchor::Bottom, 0});
        addConstraint(*backgroundImageView, {UI::ConstraintAnchor::Left, *parent, UI::ConstraintAnchor::Left, 0});
        addConstraint(*titleLabel, {UI::ConstraintAnchor::Left, *backgroundImageView, UI::ConstraintAnchor::Left, 34});
        addConstraint(*titleLabel, {UI::ConstraintAnchor::Top, *backgroundImageView, UI::ConstraintAnchor::Top, 26});
        addConstraint(*titleLabel, {UI::ConstraintAnchor::Right, *backgroundImageView, UI::ConstraintAnchor::Right, 34});
        //addConstraint(*buttonGroup, {UI::ConstraintAnchor::Bottom, *backgroundImageView, UI::ConstraintAnchor::Bottom, 28});
    }

};

}
