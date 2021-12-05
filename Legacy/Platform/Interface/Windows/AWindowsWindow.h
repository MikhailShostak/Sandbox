#pragma once

#include "Windows/AWindowsPlatform.h"
#include "Core/AWindow.h"

namespace Windows
{

struct WindowsManager : public ASingleton<WindowsManager>
{
    LPCTSTR windowClassName = TEXT("Window");
    WNDCLASSEX windowClass = WNDCLASSEX();
    Array<class Window *> windows;
    HWND menuHandle = nullptr;
    WPARAM pressedButtons = 0;
    bool keyDownAccepted = false;

    HWND offscreenWindowHandle = nullptr;
    HDC offscreenDeviceContext = nullptr;

    void InitializeWindowsSubsystem();
    void InitializeGraphicsSubsystem();

    void Initialize();
};

class Window : public AObject
{
protected:
    AWindow & owner;
    WPARAM pressedMouseButtons = 0;
public:
    HWND windowHandle = nullptr;

    Window(AWindow &owner);
    virtual ~Window();

    void initialize();

    virtual LRESULT processEvent(UINT event, WPARAM wParam, LPARAM lParam);

    void onShow(AShowEvent &event);
    void onHide(AHideEvent &event);
    void onClose(ACloseEvent &event);

    void onMove(UIMoveEvent &event);
    void onResize(UIResizeEvent &event);
    void onGeometryChange(UIGeometryChangeEvent &event);
    void onTitleChange(UITitleChangeEvent &event);
    void onFlagsChange(UIPropertyChangeEvent<WindowFlags> &event);

    void setWindowFlags(WindowFlags flags);

    void keyboardEvent(int key);

    WPARAM processMouseDownButtons(WPARAM wParam);
    WPARAM processMouseUpButtons(WPARAM wParam);
};

class OpenGLContext : public ASingleton<OpenGLContext>
{
    HGLRC renderingContext;
public:
    void LoadOpenGL();
    void Create(HDC deviceContext);
    void Apply(HDC deviceContext);
    void Destroy();
};

class OpenGLWindow : public Window
{
    HDC deviceContext = nullptr;
public:
    using Super = Window;

    LRESULT processEvent(UINT event, WPARAM wParam, LPARAM lParam) override;

    OpenGLWindow(AWindow &owner);
    ~OpenGLWindow();
};

}
