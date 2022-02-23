/*#if PLATFORM_MACOS
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#if PLATFORM_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif*/

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void CharCallback(WindowComponent* window, unsigned int c);
void KeyCallback(WindowComponent* window, int key, int scancode, int state, int mods);
void MouseButtonCallback(WindowComponent* window, int button, bool pressed);
void CursorPosCallback(WindowComponent* window, double xpos, double ypos);
void MouseWheelCallback(WindowComponent* window, double dx, double dy);


#if PLATFORM_MACOS
extern void* GetNSWindowView(GLFWwindow* wnd);
#endif

struct GLFWwindow *&GetWindowHandle(NativeWindowHandle& Handle);

static int32_t MouseCaptured = 0;

bool IsMouseCaptured() { return MouseCaptured > 0; }

void CaptureMouse(bool Captured)
{
    MouseCaptured += Captured ? 1 : -1;
}

void UpdateMouseCapture(WindowComponent* window)
{
    auto& w = GetWindowHandle(window->Handle);
    if (IsMouseCaptured())
    {
        glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

namespace
{

void GLFW_ResizeCallback(GLFWwindow* window, int width, int height)
{
    auto* w = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    w->Size.x = width;
    w->Size.y = height;
    w->SwapChain.Resize(w->Size);
    w->Render();
}

void GLFW_CharCallback(GLFWwindow* window, unsigned int c)
{
    if (!IsMouseCaptured() && ImGui::CharEvent(window, c))
    {
        return;
    }
    auto* w = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    CharCallback(w, c);
}

void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int state, int mods)
{
    if (!IsMouseCaptured() && ImGui::KeyEvent(window, key, scancode, state, mods))
    {
        return;
    }
    auto* w = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    KeyCallback(w, key, scancode, state, mods);
}

void GLFW_MouseButtonCallback(GLFWwindow* window, int button, int action, int)
{
    if (!IsMouseCaptured() && ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureMouse)
    {
        return;
    }
    auto* w = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    MouseButtonCallback(w, button, action == GLFW_PRESS);
    UpdateMouseCapture(w);
}

void GLFW_CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    /*if (ImGui::GetIO().WantSetMousePos)
    {
        return;
    }*/
    float xscale = 1;
    float yscale = 1;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    auto* w = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    CursorPosCallback(w, xpos, ypos);
}

void GLFW_MouseWheelCallback(GLFWwindow* window, double dx, double dy)
{
    if (ImGui::ScrollEvent(window, dx, dy))
    {
        return;
    }

    auto* w = static_cast<WindowComponent*>(glfwGetWindowUserPointer(window));
    MouseWheelCallback(w, dx, dy);
}

}

void WindowComponent::Load(Core::Application& Application)
{
    CreateWindowHandle();
    CreateGraphicsContext();
    CreateUI();
    Show();
}

void WindowComponent::Unload(Core::Application& Application)
{
    DestroyUI();
    DestroyGraphicsContext();
    DestroyWindowHandle();
}

void WindowComponent::Show()
{
    auto& window = GetWindowHandle(Handle);
    glfwShowWindow(window);
    FrameCounter.Start();
}

void WindowComponent::Hide()
{
    auto& window = GetWindowHandle(Handle);
    glfwHideWindow(window);
    FrameCounter.Reset();
}

void WindowComponent::Update(Core::Application& Application)
{
    glfwPollEvents();

    auto& window = GetWindowHandle(Handle);
    if (glfwWindowShouldClose(window))
    {
        glfwHideWindow(window);
        if (TerminateOnClose)
        {
            Application.Running = false;
        }
    }

    int visible = glfwGetWindowAttrib(window, GLFW_VISIBLE);
    if (visible)
    {
        Render();
    }
}

void WindowComponent::CreateWindowHandle()
{
    if (glfwInit() != GLFW_TRUE)
    {
        return;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    auto &window = GetWindowHandle(Handle);
    window = glfwCreateWindow(Size.x, Size.y, Title.data(), nullptr, nullptr);
    if (window == nullptr)
    {
        return;
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, &GLFW_ResizeCallback);
    glfwSetCharCallback(window, &GLFW_CharCallback);
    glfwSetKeyCallback(window, &GLFW_KeyCallback);
    glfwSetMouseButtonCallback(window, &GLFW_MouseButtonCallback);
    glfwSetCursorPosCallback(window, &GLFW_CursorPosCallback);
    glfwSetScrollCallback(window, &GLFW_MouseWheelCallback);

    //glfwSetWindowSizeLimits(window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void WindowComponent::DestroyWindowHandle()
{
    auto& window = GetWindowHandle(Handle);
    if (window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void WindowComponent::CreateGraphicsContext()
{
    auto& w = GetWindowHandle(Handle);
    void* h = nullptr;
#if PLATFORM_WIN32
    h = StaticCast<void>(glfwGetWin32Window(w));
#elif PLATFORM_MACOS
    glfwMakeContextCurrent(w);
    h = StaticCast<void>(glfwGetCocoaWindow(w));
#elif PLATFORM_LINUX
    // FIXME: Get x11 or wayland window handle using glfw
    glfwMakeContextCurrent(w);
    throw std::runtime_error("Missing window handle");
#endif

    auto result = GraphicsContext.Initialize(h, SwapChain);
}

void WindowComponent::DestroyGraphicsContext()
{

}

void WindowComponent::CreateUI()
{
    auto w = GetWindowHandle(Handle);
    ImGui::Initialize(w, GraphicsContext, SwapChain, "config.ini");
}

void WindowComponent::DestroyUI()
{
    auto w = GetWindowHandle(Handle);
    ImGui::Deinitialize(w);
}

void WindowComponent::Render()
{
    auto w = GetWindowHandle(Handle);
    ImGui::BeginRender(w);

    //auto dt = FrameCounter.CountValueAs<DateTime::SecondRatio>();
    PreDraw();

    int width, height;
    auto window = GetWindowHandle(Handle);
    glfwGetWindowSize(window, &width, &height);

    Clear();

    if (width > 0 && height > 0)
    {
        Draw();
    }
    Flush();
}

void WindowComponent::Clear()
{
    GraphicsContext.SetRenderBuffer(SwapChain.GetRenderBuffer());
    GraphicsContext.ClearRenderBuffers(BackgroundColor);
    GraphicsContext.ClearDepthStencilBuffers(1.0f, 0);
}

void WindowComponent::PreDraw()
{

}

void WindowComponent::Draw()
{

}

void WindowComponent::Flush()
{
    ImGui::EndRender();
    GraphicsContext.Render(SwapChain);
}
