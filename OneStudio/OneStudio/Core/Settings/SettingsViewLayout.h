#pragma once

#include "UIDeveloperLibraryView.h"

namespace UI
{

class SettingsViewLayout : public UI::RelativeLayout
{
public:
    SharedReference<UI::DeveloperLibraryView> developerLibaryView = new UI::DeveloperLibraryView();

    void load(UI::View &parentView)
    {
        developerLibaryView->setSizePolicy(SizePolicy::Expanded);
        parentView.addView(developerLibaryView);

        addConstraints(*developerLibaryView, parentView, 4);
    }

    void unload()
    {
        developerLibaryView->removeFromParent();
    }
};

}