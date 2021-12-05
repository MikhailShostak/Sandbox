#pragma once

#include "Core/Controllers/Controller.h"
#include "Core/AWindow.h"

class WindowController : public Controller
{
    ::SharedReference<AWindow> window = nullptr;
public:

    ::SharedReference<AWindow> getWindow() const
    {
        return window;
    }

    WindowController();

    void setWindow(const ::SharedReference<AWindow> &window)
    {
        this->window = window;
    }

    void onActivate()
    {
        this->window->show();
    }

    void onDeactivate()
    {
        this->window->hide();
    }
};
