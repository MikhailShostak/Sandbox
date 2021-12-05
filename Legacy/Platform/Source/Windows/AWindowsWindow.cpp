#define GLEW_STATIC

#ifndef NOMINMAX
#  define NOMINMAX
#endif
#include <GL/glew.h>
#include <GL/wglew.h>
#include <Graphics>

#include "AWindowsPlatform.h"
#include "AWindowsWindow.h"

namespace Windows
{

Math::IntegerVector getPoint(LPARAM lParam)
{
    POINTS point = MAKEPOINTS(lParam);
    return Math::IntegerVector{ point.x, point.y };
}

ATouchID getTouchID(WPARAM wParam)
{
    ATouchID touchID = ATouchID::Undefined;
    if (wParam & MK_LBUTTON)
    {
        touchID += ATouchID::LeftMouseButton;
    }
    if (wParam & MK_RBUTTON)
    {
        touchID += ATouchID::RightMouseButton;
    }
    if (wParam & MK_MBUTTON)
    {
        touchID += ATouchID::MiddleMouseButton;
    }
    if (wParam & MK_XBUTTON1)
    {
        touchID += ATouchID::X1MouseButton;
    }
    if (wParam & MK_XBUTTON2)
    {
        touchID += ATouchID::X2MouseButton;
    }
    return touchID;
}

ATouchModifier getTouchModifier()
{
    ATouchModifier touchModifier = ATouchModifier::Undefined;
    if (GetKeyState(VK_SHIFT) & 0x8000)
    {
        touchModifier += ATouchModifier::ShiftKey;
    }
    if (GetKeyState(VK_CONTROL) & 0x8000)
    {
        touchModifier += ATouchModifier::ControlKey;
    }
    if (GetKeyState(VK_MENU) & 0x8000)
    {
        touchModifier += ATouchModifier::AltKey;
    }
    return touchModifier;
}

Window *getWindowFromHandle(HWND windowHandle)
{
    return reinterpret_cast<Window *>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
}

void WindowsManager::InitializeWindowsSubsystem()
{
    windowClass.lpszClassName = windowClassName;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.hInstance = applicationInstance;
    windowClass.hIcon = LoadIcon(applicationInstance, IDI_WINLOGO);
    windowClass.hIconSm = LoadIcon(applicationInstance, IDI_WINLOGO);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = nullptr;

    windowClass.lpfnWndProc = [](HWND windowHandle, UINT event, WPARAM wParam, LPARAM lParam) {
        //Link window with handle in both directions
        if (event == WM_NCCREATE)
        {
            auto data = reinterpret_cast<LPCREATESTRUCT>(lParam);
            Window *createdWindow = reinterpret_cast<Window *>(data->lpCreateParams);
            createdWindow->windowHandle = windowHandle;
            SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createdWindow));
        }

        //Process WinAPI C events through the C++ object
        Window *window = getWindowFromHandle(windowHandle);
        if (!window)
        {
            return DefWindowProc(windowHandle, event, wParam, lParam);
        }

        return window->processEvent(event, wParam, lParam);
    };

    AAssert(RegisterClassEx(&windowClass), "Could register a window class");
}

void WindowsManager::Initialize()
{
    if (offscreenDeviceContext == nullptr)
    {
        InitializeWindowsSubsystem();
        InitializeGraphicsSubsystem();
    }
    else
    {
        //Load OpenGL for DLLs
        OpenGLContext::getInstance().LoadOpenGL();
    }
}

LRESULT Window::processEvent(UINT event, WPARAM wParam, LPARAM lParam)
{
    auto &pressedButtons = WindowsManager::getInstance().pressedButtons;
    auto &menuHandle = WindowsManager::getInstance().menuHandle;
    if(menuHandle && windowHandle != menuHandle)
    {
        const bool isWindowClicked = event == WM_NCLBUTTONDOWN || event == WM_NCRBUTTONDOWN || event == WM_LBUTTONDOWN || event == WM_RBUTTONDOWN;
        const bool isWindowDeactivated = event == WM_KILLFOCUS;
        if (isWindowClicked || isWindowDeactivated)
        {
            POINT pt;
            RECT rcWindow;
            GetCursorPos(&pt);
            GetWindowRect(menuHandle, &rcWindow);

            if (!PtInRect(&rcWindow, pt))
            {
                Window *menuWindow = getWindowFromHandle(menuHandle);
                AHideEvent e(*this);
                menuWindow->owner.sendEvent(e);
                menuHandle = nullptr;
            }
        }
    }

    static bool log = false;
    static ASteadyClock::time_point lastUpdate; //TODO: hack
    switch (event)
    {
    case WM_PAINT:
        {
            AUpdateEvent e(*this);
            owner.sendEvent(e);
        }
        if (log)
        {
            ALogMessage("", "WM_PAINT");
        }
        break;
    case WM_ERASEBKGND:
        break;
    case WM_MOUSEACTIVATE:
        if (owner.getFlags() & WindowFlags::PopUp)
        {
            return MA_NOACTIVATE;
        }
        break;
    case WM_NCACTIVATE:
        break;
    case WM_ACTIVATE:
        break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
    {
        SetCapture(windowHandle);
        pressedButtons = wParam;
        {
            AWindowTouchDownEvent e(*this, getTouchID(processMouseDownButtons(wParam)), getTouchModifier(), getPoint(lParam));
            owner.sendEvent(e);
        }
        /*if (std::chrono::duration_cast<AMilliseconds>(ASteadyClock::now() - lastUpdate).count() > 16)
        {
            for (auto &window : windows)
            {
                lastUpdate = ASteadyClock::now();
                UpdateWindow(window->windowHandle);
            }
        }*/
        if (log)
        {
            ALogMessage("", "WM_BUTTONDOWN");
        }
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        {
            AWindowTouchMoveEvent e(*this, getTouchID(wParam), getTouchModifier(), getPoint(lParam));
            owner.sendEvent(e);
        }
        /*if (std::chrono::duration_cast<AMilliseconds>(ASteadyClock::now() - lastUpdate).count() > 16)
        {
            for (auto &window : windows)
            {
                lastUpdate = ASteadyClock::now();
                UpdateWindow(window->windowHandle);
            }
        }*/
        if (log)
        {
            ALogMessage("", "WM_MOUSEMOVE");
        }
        return 0;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
    {
        {
            AWindowTouchUpEvent e(*this, getTouchID(processMouseUpButtons(wParam)), getTouchModifier(), getPoint(lParam));
            owner.sendEvent(e);
        }
        pressedButtons = wParam;
        ReleaseCapture();
        /*if (std::chrono::duration_cast<AMilliseconds>(ASteadyClock::now() - lastUpdate).count() > 16)
        {
            for (auto &window : windows)
            {
                lastUpdate = ASteadyClock::now();
                UpdateWindow(window->windowHandle);
            }
        }*/
        if (log)
        {
            ALogMessage("", "WM_BUTTONUP");
        }
        return 0;
    }
    case WM_MOUSEHOVER:
    case WM_MOUSELEAVE:
        return 0;
    case WM_MOUSEWHEEL:
    {
        //int fwKeys = GET_KEYSTATE_WPARAM(wParam);
        AWindowTouchWheelEvent e(*this, getTouchModifier(), getPoint(lParam) - owner.getGeometry().position, GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
        owner.sendEvent(e);
        return 0;
    }
    case WM_KEYDOWN:
    {
        AWindowKeyPressEvent e(*this, wParam);
        owner.sendEvent(e);
        keyboardEvent(wParam);
        WindowsManager::getInstance().keyDownAccepted = e.isAccepted();
        return 0;
    }
    case WM_CHAR:
    {
        if (!WindowsManager::getInstance().keyDownAccepted)
        {
            AWindowKeyCharEvent e(*this, char(wParam));
            owner.sendEvent(e);
        }
        return 0;
    }
    case WM_KEYUP:
    {
        AWindowKeyReleaseEvent e(*this, wParam);
        owner.sendEvent(e);
        return 0;
    }
    case WM_MOVE:
    {
        UIMoveEvent e(*this, Math::IntegerVector{ int16_t(LOWORD(lParam)), int16_t(HIWORD(lParam)) });
        owner.sendEvent(e);
        return 0;
    }
    case WM_SIZE:
    {
        UIResizeEvent e(*this, Math::IntegerVector{ LOWORD(lParam), HIWORD(lParam) });
        owner.sendEvent(e);
        return 0;
    }
    case WM_CLOSE:
    {
        ACloseEvent e(*this);
        owner.sendEvent(e);
        ShowWindow(windowHandle, SW_HIDE);
        return 0;
    }
    default:
        break;
    }

    return DefWindowProc(windowHandle, event, wParam, lParam);
}

Window::Window(AWindow &owner):
    owner(owner)
{
    WindowsManager::getInstance().windows.push_back(this);
    ARegisterEventCallback(onShow);
    ARegisterEventCallback(onHide);
    ARegisterEventCallback(onClose);

    ARegisterEventCallback(onMove);
    ARegisterEventCallback(onResize);
    ARegisterEventCallback(onGeometryChange);
    ARegisterEventCallback(onTitleChange);
    ARegisterEventCallback(onFlagsChange);
    owner.eventChannel.registerObserver(*this);

    initialize();
}

void Window::initialize()
{
    auto &windowClassName = WindowsManager::getInstance().windowClassName;
    CreateWindowEx(0, windowClassName, STRING_TO_PTCHAR(owner.getTitle()), WS_OVERLAPPEDWINDOW, 600, 300, owner.getGeometry().size.x, owner.getGeometry().size.y, nullptr, nullptr, applicationInstance, reinterpret_cast<LPVOID>(this));
}

Window::~Window()
{
    owner.eventChannel.unregisterObserver(*this);
    AUnregisterEventCallback(onFlagsChange);
    AUnregisterEventCallback(onTitleChange);
    AUnregisterEventCallback(onGeometryChange);
    AUnregisterEventCallback(onResize);
    AUnregisterEventCallback(onMove);

    AUnregisterEventCallback(onClose);
    AUnregisterEventCallback(onHide);
    AUnregisterEventCallback(onShow);

    ArrayUtils::Remove(WindowsManager::getInstance().windows, this);
    if (WindowsManager::getInstance().windows.empty())
    {
        PostQuitMessage(0);
    }
}

void Window::onShow(AShowEvent &event)
{
    if (owner.getFlags() & WindowFlags::PopUp)
    {
        auto &menuHandle = WindowsManager::getInstance().menuHandle;
        //TODO: do it with separate function
        SetWindowPos(windowHandle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        ShowWindow(windowHandle, SW_SHOW);
        if (menuHandle && menuHandle != windowHandle)
        {
            Window *window = getWindowFromHandle(menuHandle);
            AHideEvent e(*this);
            window->owner.sendEvent(e);
        }
        menuHandle = windowHandle;

        //FlashWindow(windowHandle, false);
        //SetForegroundWindow(windowHandle); //Focus
    }
    else
    {
        ShowWindow(windowHandle, SW_SHOWNORMAL);
    }
}

void Window::onHide(AHideEvent &event)
{
    ShowWindow(windowHandle, SW_HIDE);
}

void Window::onClose(ACloseEvent &event)
{
    ShowWindow(windowHandle, SW_HIDE);
}

void Window::onMove(UIMoveEvent &event)
{
    const Math::IntegerVector &position = event.getValue();
    RECT rect;
    GetClientRect(windowHandle, &rect);
    rect.left = position.x;
    rect.top = position.y;
    DWORD style = GetWindowLong(windowHandle, GWL_STYLE);
    AdjustWindowRectEx(&rect, style, false, 0);
    MoveWindow(windowHandle, rect.left, rect.top, rect.right, rect.bottom, false);
}

void Window::onResize(UIResizeEvent &event)
{
    const Math::IntegerVector &size = event.getValue();
    RECT rect;
    GetClientRect(windowHandle, &rect);
    rect.right = size.x;
    rect.bottom = size.y;
    DWORD style = GetWindowLong(windowHandle, GWL_STYLE);
    AdjustWindowRectEx(&rect, style, false, 0);
    MoveWindow(windowHandle, rect.left, rect.top, rect.right, rect.bottom, true);
    //UpdateWindow(windowHandle);
}

void Window::onGeometryChange(UIGeometryChangeEvent &event)
{
    const Math::IntegerRectangle &geometry = event.getValue();
    RECT rect{ 0, 0, 0, 0 };
    DWORD style = GetWindowLong(windowHandle, GWL_STYLE);
    AdjustWindowRectEx(&rect, style, false, 0);
    MoveWindow(windowHandle, geometry.position.x, geometry.position.y, geometry.size.x - rect.left + rect.right, geometry.size.y - rect.top + rect.bottom, true);
    //UpdateWindow(windowHandle);
}

void Window::onTitleChange(UITitleChangeEvent &event)
{
    SetWindowText(windowHandle, STRING_TO_PTCHAR(event.getValue()));
}

void Window::onFlagsChange(UIPropertyChangeEvent<WindowFlags> &event)
{
    setWindowFlags(event.getValue());
}

void Window::setWindowFlags(WindowFlags flags)
{
    auto style = WS_OVERLAPPED;
    auto exStyle = 0;
    if (flags & WindowFlags::HasTitle)
    {
        style |= WS_CAPTION;
    }
    if (flags & WindowFlags::HasButtons)
    {
        style |= WS_SYSMENU;
    }
    if (flags & WindowFlags::ResizeSupport)
    {
        style |= WS_SIZEBOX;
    }
    if (flags & WindowFlags::MinimizeSupport)
    {
        style |= WS_MINIMIZEBOX;
    }
    if (flags & WindowFlags::MaximizeSupport)
    {
        style |= WS_MAXIMIZEBOX;
    }
    if (flags & WindowFlags::PopUp)
    {
        //style |= WS_POPUP;
        exStyle |= WS_EX_TOPMOST;
        exStyle |= WS_EX_NOACTIVATE;
    }
    if (flags & WindowFlags::Tool)
    {
        exStyle |= WS_EX_TOOLWINDOW;
    }
    if (flags & WindowFlags::DragAndDropSupport)
    {
        exStyle |= WS_EX_ACCEPTFILES;
    }

    SetWindowLong(windowHandle, GWL_STYLE, owner.getVisible() ? style | WS_VISIBLE : style);
    SetWindowLong(windowHandle, GWL_EXSTYLE, exStyle);
}

void Window::keyboardEvent(int key)
{
    switch(key)
    {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    default:
        break;
    }
}

WPARAM Window::processMouseDownButtons(WPARAM wParam)
{
    return pressedMouseButtons = wParam;
}

WPARAM Window::processMouseUpButtons(WPARAM wParam)
{
    WPARAM result = pressedMouseButtons &= ~wParam;
    pressedMouseButtons = wParam;
    return result;
}

}



























namespace Windows
{

AError setPixelFormat(HDC deviceContext, bool renderToWindow, uint8_t colorBits = 24, uint8_t alphaBits = 8, uint8_t depthBits = 32, uint8_t stensilBits = 8)
{
    PIXELFORMATDESCRIPTOR attributes = PIXELFORMATDESCRIPTOR();
    attributes.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    attributes.nVersion = 1;
    attributes.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    attributes.iLayerType = PFD_MAIN_PLANE;
    attributes.iPixelType = PFD_TYPE_RGBA;
    attributes.cColorBits = colorBits;
    attributes.cAlphaBits = alphaBits;
    attributes.cDepthBits = depthBits;
    attributes.cStencilBits = stensilBits;
    auto format = ChoosePixelFormat(deviceContext, &attributes);
    if (format == 0 || !SetPixelFormat(deviceContext, format, nullptr))
    {
        return AError(GetLastError(), "The pixel format is invalid");
    }
    return AError::getEmptyError();
}

void WindowsManager::InitializeGraphicsSubsystem()
{
    LPCTSTR emptyWindowClassName = TEXT("EmptyWindow");

    WNDCLASSEX emptyWindowClass = WNDCLASSEX();
    emptyWindowClass.lpszClassName = emptyWindowClassName;
    emptyWindowClass.cbSize = sizeof(WNDCLASSEX);

    emptyWindowClass.lpfnWndProc = [](HWND windowHandle, UINT event, WPARAM wParam, LPARAM lParam) {
        if (event == WM_NCCREATE)
        {
            WindowsManager & windowManager = WindowsManager::getInstance();
            windowManager.offscreenWindowHandle = windowHandle;
            windowManager.offscreenDeviceContext = GetDC(windowManager.offscreenWindowHandle);
            setPixelFormat(windowManager.offscreenDeviceContext, true);
            OpenGLContext::getInstance().Create(windowManager.offscreenDeviceContext);
        }

        return DefWindowProc(windowHandle, event, wParam, lParam);
    };

    AAssert(RegisterClassEx(&emptyWindowClass), "Could register a window class");
    CreateWindowEx(0, emptyWindowClassName, nullptr, WS_OVERLAPPED, 0, 0, 0, 0, nullptr, nullptr, applicationInstance, nullptr);
}

AStaticRun(GraphicsContext)
{
    Windows::WindowsManager::getInstance().Initialize();
}

void GetGLVersion(int *major, int *minor)
{
    // for all versions
    char *ver = (char *)glGetString(GL_VERSION); // ver = "3.2.0"

    *major = ver[0] - '0';
    if (*major >= 3)
    {
        // for GL 3.x
        glGetIntegerv(GL_MAJOR_VERSION, major); // major = 3
        glGetIntegerv(GL_MINOR_VERSION, minor); // minor = 2
    }
    else
    {
        *minor = ver[2] - '0';
    }

    // GLSL
    ver = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION); // ver = "1.50 NVIDIA via Cg compiler"
}

constexpr static const int32_t LatestPatchVersion = -1;

void OpenGLContext::LoadOpenGL()
{
    glewExperimental = true;
    GLenum glewCompletionCode = glewInit();
    if (glewCompletionCode != GLEW_OK)
    {
        std::cout << glewGetErrorString(glewCompletionCode) << "\n";
        return;
    }
    Legacy::Graphics::API::glCheckErrors(true);
}

void OpenGLContext::Create(HDC deviceContext)
{
    if (renderingContext != nullptr)
    {
        return;
    }

    auto createContext = [this, &deviceContext](int32_t major, int32_t minor) {
        HGLRC tempContext = wglCreateContext(deviceContext);
        wglMakeCurrent(deviceContext, tempContext);

        static int32_t supported_major;
        static int32_t supported_minor;
        GetGLVersion(&supported_major, &supported_minor);

        if (supported_major < 3 || (supported_major == 3 && supported_minor < 2))
        {
            return;
        }

        if (minor == LatestPatchVersion)
        {
            minor = supported_minor;
            if (major == LatestPatchVersion)
            {
                major = supported_major;
            }
        }

        if (supported_major < major || (supported_major == major && supported_minor < minor))
        {
            return;
        }

        int contextAttributes[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, major,
            WGL_CONTEXT_MINOR_VERSION_ARB, minor,
            //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
        if (wglCreateContextAttribsARB != nullptr)
        {
            renderingContext = wglCreateContextAttribsARB(deviceContext, 0, contextAttributes);
        }

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(tempContext);
    };

    createContext(3, 3);

    Apply(deviceContext);
    Legacy::Graphics::API::glCheckErrors();

    LoadOpenGL();

    Legacy::Graphics::API::load();
    Legacy::Graphics::API::glCheckErrors();
}

void OpenGLContext::Apply(HDC deviceContext)
{
    wglMakeCurrent(deviceContext, renderingContext);
}

void OpenGLContext::Destroy()
{
    wglDeleteContext(renderingContext);
}

OpenGLWindow::OpenGLWindow(AWindow &owner):
    Window(owner)
{
    LinkStaticRun(GraphicsContext);
    deviceContext = GetDC(windowHandle);
    setPixelFormat(deviceContext, true);

    //SetWindowLong(windowHandle, GWL_EXSTYLE, GetWindowLong(windowHandle, GWL_EXSTYLE) | WS_EX_LAYERED);
    //UpdateWindow(windowHandle);
}

OpenGLWindow::~OpenGLWindow()
{
    ReleaseDC(windowHandle, deviceContext);
}

/*int OpenGLWindow::getMultiSampledFormat(uint8_t samples, uint8_t colorBits, uint8_t depthBits, uint8_t stensilBits)
{
static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

int format = 0;

if (!wglChoosePixelFormatARB)
{
return format;
}

UINT nMaxFormats = 1;
UINT nNumFormats;

int attributes[] = {
WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
WGL_COLOR_BITS_ARB, 24,
WGL_ALPHA_BITS_ARB, 8,
WGL_DEPTH_BITS_ARB, depthBits,
WGL_STENCIL_BITS_ARB, stensilBits,
WGL_SAMPLE_BUFFERS_ARB, 1,
WGL_SAMPLES_ARB, samples,
0
};

float pfAttribFList[] = { 0, 0 };

wglChoosePixelFormatARB(deviceContext, attributes, pfAttribFList, nMaxFormats, &format, &nNumFormats);

return format;
}*/

LRESULT OpenGLWindow::processEvent(UINT event, WPARAM wParam, LPARAM lParam)
{
    switch (event)
    {
    case WM_PAINT:
        OpenGLContext::getInstance().Apply(deviceContext);
        glViewport(0, 0, owner.getGeometry().size.x, owner.getGeometry().size.y);
        Super::processEvent(event, wParam, lParam);
        SwapBuffers(deviceContext);
        return 0;
    case WM_SIZE:

        /*{
            Math::IntegerVector size = owner.getGeometry().size;
            HDC hdc = CreateCompatibleDC(deviceContext);

            // The window has to be layered if you want transparency
            //SetWindowLong(windowHandle, GWL_EXSTYLE, GetWindowLong(windowHandle, GWL_EXSTYLE) | WS_EX_LAYERED);

            // Create our DIB section and select the bitmap into the DC
            void* pvBits;
            BITMAPINFO bmi;
            ZeroMemory(&bmi, sizeof(BITMAPINFO));
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = size.x;
            bmi.bmiHeader.biHeight = size.y;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;
            bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * (bmi.bmiHeader.biBitCount / 8);
            HBITMAP hbitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0x0);
            SelectObject(hdc, hbitmap);

            uint8_t* data = (uint8_t *)pvBits;
            // Copy the pixels from the image to the bitmap (but pre-multiply the alpha value)
            for (int i = 0; i < size.area() * 4; ++i)
            {
                data[i] = 255 * (float(i) / size.area());
            }

            POINT ptSrc = { 0, 0 };
            SIZE sizeWnd = { bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight };
            BLENDFUNCTION bf;
            bf.BlendOp = AC_SRC_OVER;
            bf.BlendFlags = 0;
            bf.AlphaFormat = AC_SRC_ALPHA;
            bf.SourceConstantAlpha = 0xFF;
            UpdateLayeredWindow(windowHandle, nullptr, nullptr, &sizeWnd, hdc, &ptSrc, 0, &bf, ULW_ALPHA);
        }*/
        //glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        break;
    }

    return Super::processEvent(event, wParam, lParam);
}

}
