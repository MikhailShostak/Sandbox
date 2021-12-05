#pragma once

#include <Experimental>

namespace Ui {
class OSPluginPreferencesView;
}

class OSPluginPreferencesView : public UI::View
{
public:

    explicit OSPluginPreferencesView();
    ~OSPluginPreferencesView();

//public slots:

    void accept();

protected:

    //void showEvent(QShowEvent *event) override;

};
