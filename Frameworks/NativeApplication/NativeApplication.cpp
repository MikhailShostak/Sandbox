#include "NativeApplication.hpp"

#define PLATFORM_WIN32 1
#define ENGINE_DLL 0
#define VULKAN_SUPPORTED 1

#if PLATFORM_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32 1
#undef GetObject
#elif PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11 1
#elif PLATFORM_MACOS
#define GLFW_EXPOSE_NATIVE_COCOA 1
#endif

#include <EngineFactoryVk.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#if PLATFORM_MACOS
extern void* GetNSWindowView(GLFWwindow* wnd);
#endif

#include <imgui_impl_glfw.h>
#include <ImGuiImplDiligent.hpp>

namespace
{

void GLFW_ResizeCallback(GLFWwindow* window, int width, int height)
{
    auto* w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    if (w->m_pSwapChain != nullptr)
    {
        w->MainWindowSize.x = width;
        w->MainWindowSize.y = height;
        w->m_pSwapChain->Resize(static_cast<Uint32>(width), static_cast<Uint32>(height));
        w->UpdateWindow();
    }
}

void GLFW_CharCallback(GLFWwindow* window, unsigned int c)
{
    ImGui_ImplGlfw_CharCallback(window, c);
}

void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int state, int mods)
{
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, state, mods);
    ImGuiIO& io = ImGui::GetIO();
    if(!io.WantCaptureKeyboard)
    {
        //TODO: Keyboard Input
        //auto w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    }
}

void GLFW_MouseButtonCallback(GLFWwindow* window, int button, int state, int)
{
    ImGuiIO& io = ImGui::GetIO();
    if(!io.WantCaptureMouse)
    {
        //TODO: Mouse Input
        //auto w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    }
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
    ImGui_ImplGlfw_ScrollCallback(window, dx, dy);
}

GLFWwindow* g_MainWindow = nullptr;

bool GLFW_CreateMainWindow(const std::string &title, const NativeApplication::Vec<int> &size, NativeApplication* window)
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

std::unique_ptr<Diligent::ImGuiImplDiligent> g_ImGui;

}

NativeApplication::NativeApplication()
{
}

NativeApplication::~NativeApplication()
{
    if (m_pImmediateContext)
        m_pImmediateContext->Flush();

    g_ImGui.reset();

    m_pSwapChain        = nullptr;
    m_pImmediateContext = nullptr;
    m_pDevice           = nullptr;

    GLFW_DestroyMainWindow();
}

bool NativeApplication::InitEngine()
{
#if PLATFORM_WIN32
    Win32NativeWindow Window{glfwGetWin32Window(g_MainWindow)};
#elif PLATFORM_LINUX
    LinuxNativeWindow Window;
    Window.WindowId = glfwGetX11Window(g_MainWindow);
    Window.pDisplay = glfwGetX11Display();
#elif PLATFORM_MACOS
    MacOSNativeWindow Window;
    Window.pNSView = GetNSWindowView(g_MainWindow);
#endif

    SwapChainDesc SCDesc;

#if EXPLICITLY_LOAD_ENGINE_VK_DLL
    // Load the dll and import GetEngineFactoryVk() function
    auto* GetEngineFactoryVk = LoadGraphicsEngineVk();
#endif
    auto* pFactoryVk = GetEngineFactoryVk();

    EngineVkCreateInfo EngineCI;
    pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);
    pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);

    if (m_pDevice == nullptr || m_pImmediateContext == nullptr || m_pSwapChain == nullptr)
        return false;

    return true;
}

bool NativeApplication::InitUI()
{
    class ImGuiImplGLFW final : public ImGuiImplDiligent
    {
    public:
        ImGuiImplGLFW(GLFWwindow* window,
           const char *config,
           IRenderDevice* pDevice,
           TEXTURE_FORMAT BackBufferFmt,
           TEXTURE_FORMAT DepthBufferFmt,
           Uint32         InitialVertexBufferSize = ImGuiImplDiligent::DefaultInitialVBSize,
           Uint32         InitialIndexBufferSize  = ImGuiImplDiligent::DefaultInitialIBSize):
           ImGuiImplDiligent{pDevice, BackBufferFmt, DepthBufferFmt, InitialVertexBufferSize, InitialIndexBufferSize}
        {
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.IniFilename = config;

            ImGui_ImplGlfw_InitForOther(window, false);
        }

        ~ImGuiImplGLFW()
        {
            ImGui_ImplGlfw_Shutdown();
        }

        //LRESULT Win32_ProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        // clang-format off
        ImGuiImplGLFW             (const ImGuiImplGLFW&)  = delete;
        ImGuiImplGLFW             (      ImGuiImplGLFW&&) = delete;
        ImGuiImplGLFW& operator = (const ImGuiImplGLFW&)  = delete;
        ImGuiImplGLFW& operator = (      ImGuiImplGLFW&&) = delete;
        // clang-format on

        virtual void NewFrame(Uint32 RenderSurfaceWidth, Uint32 RenderSurfaceHeight, SURFACE_TRANSFORM SurfacePreTransform) override final
        {
            VERIFY(SurfacePreTransform == SURFACE_TRANSFORM_IDENTITY, "Unexpected surface pre-transform");

            ImGui_ImplGlfw_NewFrame();
            ImGuiImplDiligent::NewFrame(RenderSurfaceWidth, RenderSurfaceHeight, SurfacePreTransform);

#ifdef DILIGENT_DEBUG
            {
                ImGuiIO& io = ImGui::GetIO();
                VERIFY(io.DisplaySize.x == 0 || io.DisplaySize.x == static_cast<float>(RenderSurfaceWidth),
                       "Render surface width (", RenderSurfaceWidth, ") does not match io.DisplaySize.x (", io.DisplaySize.x, ")");
                VERIFY(io.DisplaySize.y == 0 || io.DisplaySize.y == static_cast<float>(RenderSurfaceHeight),
                       "Render surface height (", RenderSurfaceHeight, ") does not match io.DisplaySize.y (", io.DisplaySize.y, ")");
            }
#endif
        }
    };

    const auto& SCDesc = m_pSwapChain->GetDesc();
    g_ImGui = std::make_unique<ImGuiImplGLFW>(g_MainWindow, ConfigFile.data(), m_pDevice, SCDesc.ColorBufferFormat, SCDesc.DepthBufferFormat);
    return true;
}

void NativeApplication::Loop()
{
    m_LastUpdate = Clock::now();

    bool running = true;
    while (running)
    {
        running = GLFW_PollEvents();
        UpdateWindow();
    }
}

void NativeApplication::UpdateWindow()
{
    const auto time = Clock::now();
    const auto dt   = std::chrono::duration_cast<Seconds>(time - m_LastUpdate).count();
    m_LastUpdate    = time;

    if (g_ImGui)
    {
        const auto SCDesc = m_pSwapChain->GetDesc();
        g_ImGui->NewFrame(SCDesc.Width, SCDesc.Height, SCDesc.PreTransform);
    }

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
    Flush();
}

void NativeApplication::Clear()
{
    ITextureView* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
    m_pImmediateContext->SetRenderTargets(1, &pRTV, nullptr, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    const float ClearColor[4] = {};
    m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_VERIFY);
}

void NativeApplication::Flush()
{
    ITextureView* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
    ITextureView* pDSV = m_pSwapChain->GetDepthBufferDSV();
    m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    if (g_ImGui)
    {
        g_ImGui->Render(m_pImmediateContext);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    m_pImmediateContext->Flush();
    m_pSwapChain->Present();
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
