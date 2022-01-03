#include "NativeApplication.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#if PLATFORM_MACOS
extern void* GetNSWindowView(GLFWwindow* wnd);
#endif

namespace
{

void GLFW_ResizeCallback(GLFWwindow* window, int width, int height)
{
    auto *w = static_cast<NativeApplication *>(glfwGetWindowUserPointer(window));
    w->MainWindowSize.x = width;
    w->MainWindowSize.y = height;
    w->m_SwapChain.Resize(w->MainWindowSize);
    w->UpdateWindow();
}

void GLFW_CharCallback(GLFWwindow* window, unsigned int c)
{
    ImGui::CharEvent(window, c);
}

void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int state, int mods)
{
    ImGui::KeyEvent(window, key, scancode, state, mods);
}

void GLFW_MouseButtonCallback(GLFWwindow* window, int button, int state, int)
{

}

void GLFW_CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    float xscale = 1;
    float yscale = 1;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    //TODO: Mouse Input
    //auto w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
}

void GLFW_MouseWheelCallback(GLFWwindow* window, double dx, double dy)
{
    ImGui::ScrollEvent(window, dx, dy);
}

GLFWwindow* g_MainWindow = nullptr;

bool GLFW_CreateMainWindow(const std::string &title, const hlslpp::int2 &size, NativeApplication* window)
{
    if (glfwInit() != GLFW_TRUE)
    {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    g_MainWindow = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
    if (g_MainWindow == nullptr)
    {
        return false;
    }

    glfwSetWindowUserPointer(g_MainWindow, window);
    glfwSetFramebufferSizeCallback(g_MainWindow, &GLFW_ResizeCallback);
    glfwSetCharCallback(g_MainWindow, &GLFW_CharCallback);
    glfwSetKeyCallback(g_MainWindow, &GLFW_KeyCallback);
    glfwSetMouseButtonCallback(g_MainWindow, &GLFW_MouseButtonCallback);
    glfwSetCursorPosCallback(g_MainWindow, &GLFW_CursorPosCallback);
    glfwSetScrollCallback(g_MainWindow, &GLFW_MouseWheelCallback);

    //glfwSetWindowSizeLimits(g_MainWindow, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);
    return true;
}

void GLFW_DestroyMainWindow()
{
    if (g_MainWindow)
    {
        glfwDestroyWindow(g_MainWindow);
        glfwTerminate();
    }
}

bool GLFW_PollEvents()
{
    glfwPollEvents();
    return !glfwWindowShouldClose(g_MainWindow);
}

}

NativeApplication::NativeApplication()
{
}

NativeApplication::~NativeApplication()
{
    ImGui::Deinitialize();
    GLFW_DestroyMainWindow();
}

bool NativeApplication::InitEngine()
{
#if PLATFORM_WIN32
    m_NativeWindowHandle = StaticCast<void>(glfwGetWin32Window(g_MainWindow));
#elif PLATFORM_MACOS
    glfwMakeContextCurrent(g_MainWindow);
    m_NativeWindowHandle = StaticCast<void>(glfwGetCocoaWindow(g_MainWindow));
#elif PLATFORM_LINUX
    // FIXME: Get x11 or wayland window handle using glfw
    glfwMakeContextCurrent(g_MainWindow);
    throw std::runtime_error("Missing window handle");
#endif

    auto [result] = m_GraphicsContext.Initialize(m_NativeWindowHandle, m_SwapChain);
    return result;
}

bool NativeApplication::InitUI()
{
    ImGui::Initialize(g_MainWindow, m_GraphicsContext, m_SwapChain, ConfigFile.data());
    return true;
}

void NativeApplication::Loop()
{
    m_Counter.Start();

    bool running = true;
    while (running)
    {
        running = GLFW_PollEvents();
        UpdateWindow();
    }
}

void NativeApplication::UpdateWindow()
{
    ImGui::BeginRender();

    auto dt = m_Counter.CountValueAs<DateTime::SecondRatio>();
    Update(dt);
    UpdateUI(dt);

    int width, height;
    glfwGetWindowSize(g_MainWindow, &width, &height);

    PreDraw();
    Clear();

    if (width > 0 && height > 0)
    {
        Draw();
    }
    Render();
}

void NativeApplication::Clear()
{
    auto [RenderBuffer] = m_SwapChain.GetRenderBuffer();
    m_GraphicsContext.SetRenderBuffer(RenderBuffer);
    m_GraphicsContext.ClearRenderBuffers(BackgroundColor);
    m_GraphicsContext.ClearDepthStencilBuffers(1.0f, 0);
}

void NativeApplication::Render()
{
    ImGui::EndRender();
    m_GraphicsContext.Render(m_SwapChain);
}

int NativeApplication::Run()
{
    if(!PreInit())
    {
        return -1;
    }

    if (!GLFW_CreateMainWindow(MainWindowTitle, MainWindowSize, this))
    {
        return -1;
    }

    if (!InitEngine())
    {
        return -1;
    }

    if (!InitUI())
    {
        return -1;
    }

    if (!Init())
    {
        return -1;
    }

    Loop();

    Terminate();

    return 0;
}

void NativeApplication::Quit()
{
    glfwSetWindowShouldClose(g_MainWindow, GLFW_TRUE);
}

int main(int argc, const char** argv)
{
    return CreateApp()->Run();
}
