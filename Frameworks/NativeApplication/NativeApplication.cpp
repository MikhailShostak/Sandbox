#include "NativeApplication.hpp"

#include <BasicMath.hpp>
#include <DeviceContext.h>
#include <RefCntAutoPtr.hpp>
#include <RenderDevice.h>
#include <SwapChain.h>

#include <EngineFactoryVk.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#if PLATFORM_MACOS
extern void* GetNSWindowView(GLFWwindow* wnd);
#endif

#include <imgui_impl_glfw.h>
#include <ImGuiImplDiligent.hpp>

struct NativeApplicationData
{
    Counter<HighResolution::Clock> m_Counter;
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice>  m_pDevice;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
    Diligent::RefCntAutoPtr<Diligent::ISwapChain>     m_pSwapChain;
};

namespace
{

void GLFW_ResizeCallback(GLFWwindow* window, int width, int height)
{
    auto* w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    if (w->m_Data->m_pSwapChain != nullptr)
    {
        w->MainWindowSize.x = width;
        w->MainWindowSize.y = height;
        w->m_Data->m_pSwapChain->Resize(static_cast<Diligent::Uint32>(width), static_cast<Diligent::Uint32>(height));
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
    if (m_Data->m_pImmediateContext)
    {
        m_Data->m_pImmediateContext->Flush();
    }

    g_ImGui.reset();

    m_Data->m_pSwapChain = nullptr;
    m_Data->m_pImmediateContext = nullptr;
    m_Data->m_pDevice = nullptr;

    GLFW_DestroyMainWindow();
}

bool NativeApplication::InitEngine()
{
#if PLATFORM_WIN32
    Diligent::Win32NativeWindow Window{glfwGetWin32Window(g_MainWindow)};
#elif PLATFORM_LINUX
    Diligent::LinuxNativeWindow Window;
    Window.WindowId = glfwGetX11Window(g_MainWindow);
    Window.pDisplay = glfwGetX11Display();
#elif PLATFORM_MACOS
    Diligent::MacOSNativeWindow Window;
    Window.pNSView = GetNSWindowView(g_MainWindow);
#endif

    Diligent::SwapChainDesc SCDesc;

#if EXPLICITLY_LOAD_ENGINE_VK_DLL
    // Load the dll and import GetEngineFactoryVk() function
    auto* GetEngineFactoryVk = Diligent::LoadGraphicsEngineVk();
#endif
    auto* pFactoryVk = Diligent::GetEngineFactoryVk();

    Diligent::EngineVkCreateInfo EngineCI;
    pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_Data->m_pDevice, &m_Data->m_pImmediateContext);
    pFactoryVk->CreateSwapChainVk(m_Data->m_pDevice, m_Data->m_pImmediateContext, SCDesc, Window, &m_Data->m_pSwapChain);

    if (m_Data->m_pDevice == nullptr || m_Data->m_pImmediateContext == nullptr || m_Data->m_pSwapChain == nullptr)
    {
        return false;
    }

    return true;
}

bool NativeApplication::InitUI()
{
    class ImGuiImplGLFW final : public Diligent::ImGuiImplDiligent
    {
    public:
        ImGuiImplGLFW(GLFWwindow* window,
           const char *config,
           Diligent::IRenderDevice* pDevice,
           Diligent::TEXTURE_FORMAT BackBufferFmt,
           Diligent::TEXTURE_FORMAT DepthBufferFmt,
           Diligent::Uint32         InitialVertexBufferSize = Diligent::ImGuiImplDiligent::DefaultInitialVBSize,
           Diligent::Uint32         InitialIndexBufferSize  = Diligent::ImGuiImplDiligent::DefaultInitialIBSize):
           Diligent::ImGuiImplDiligent{pDevice, BackBufferFmt, DepthBufferFmt, InitialVertexBufferSize, InitialIndexBufferSize}
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

        virtual void NewFrame(Diligent::Uint32 RenderSurfaceWidth, Diligent::Uint32 RenderSurfaceHeight, Diligent::SURFACE_TRANSFORM SurfacePreTransform) override final
        {
            VERIFY(SurfacePreTransform == Diligent::SURFACE_TRANSFORM_IDENTITY, "Unexpected surface pre-transform");

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

    const auto& SCDesc = m_Data->m_pSwapChain->GetDesc();
    g_ImGui = std::make_unique<ImGuiImplGLFW>(g_MainWindow, ConfigFile.data(), m_Data->m_pDevice, SCDesc.ColorBufferFormat, SCDesc.DepthBufferFormat);
    return true;
}

void NativeApplication::Loop()
{
    m_Data->m_Counter.Start();

    bool running = true;
    while (running)
    {
        running = GLFW_PollEvents();
        UpdateWindow();
    }
}

void NativeApplication::UpdateWindow()
{
    if (g_ImGui)
    {
        const auto SCDesc = m_Data->m_pSwapChain->GetDesc();
        g_ImGui->NewFrame(SCDesc.Width, SCDesc.Height, SCDesc.PreTransform);
    }

    auto dt = m_Data->m_Counter.CountValueAs<SecondRatio>();
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
    Diligent::ITextureView* pRTV = m_Data->m_pSwapChain->GetCurrentBackBufferRTV();
    m_Data->m_pImmediateContext->SetRenderTargets(1, &pRTV, nullptr, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    m_Data->m_pImmediateContext->ClearRenderTarget(pRTV, &BackgroundColor.x, Diligent::RESOURCE_STATE_TRANSITION_MODE_VERIFY);
}

void NativeApplication::Flush()
{
    Diligent::ITextureView* pRTV = m_Data->m_pSwapChain->GetCurrentBackBufferRTV();
    Diligent::ITextureView* pDSV = m_Data->m_pSwapChain->GetDepthBufferDSV();
    m_Data->m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    if (g_ImGui)
    {
        g_ImGui->Render(m_Data->m_pImmediateContext);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    m_Data->m_pImmediateContext->Flush();
    m_Data->m_pSwapChain->Present();
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
