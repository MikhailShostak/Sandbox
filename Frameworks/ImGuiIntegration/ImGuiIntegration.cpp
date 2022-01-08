#include <PrivateImplementation.hpp>

#include <imgui_impl_glfw.h>
#include <ImGuiImplDiligent.hpp>

#include <GLFW/glfw3.h>

namespace ImGui
{

class ImGuiImplGLFW final : public Diligent::ImGuiImplDiligent
{
public:
    ImGuiImplGLFW(GLFWwindow *window, Graphics::GraphicsContext &Context, Graphics::SwapChain &SwapChain, const char *ConfigFile) :
        Diligent::ImGuiImplDiligent(
            Context.Data->Device,
            SwapChain.Data->Handle->GetDesc().ColorBufferFormat,
            SwapChain.Data->Handle->GetDesc().DepthBufferFormat,
            Diligent::ImGuiImplDiligent::DefaultInitialVBSize,
            Diligent::ImGuiImplDiligent::DefaultInitialIBSize
        ),
        Context(Context),
        SwapChain(SwapChain)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.IniFilename = ConfigFile;

        ImGui_ImplGlfw_InitForOther(window, false);
    }

    ~ImGuiImplGLFW()
    {
        ImGui_ImplGlfw_Shutdown();
    }

    //LRESULT Win32_ProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // clang-format off
    ImGuiImplGLFW(const ImGuiImplGLFW &) = delete;
    ImGuiImplGLFW(ImGuiImplGLFW &&) = delete;
    ImGuiImplGLFW &operator = (const ImGuiImplGLFW &) = delete;
    ImGuiImplGLFW &operator = (ImGuiImplGLFW &&) = delete;
    // clang-format on

    virtual void NewFrame(Diligent::Uint32 RenderSurfaceWidth, Diligent::Uint32 RenderSurfaceHeight, Diligent::SURFACE_TRANSFORM SurfacePreTransform) override final
    {
        VERIFY(SurfacePreTransform == Diligent::SURFACE_TRANSFORM_IDENTITY, "Unexpected surface pre-transform");

        ImGui_ImplGlfw_NewFrame();
        ImGuiImplDiligent::NewFrame(RenderSurfaceWidth, RenderSurfaceHeight, SurfacePreTransform);

#ifdef DILIGENT_DEBUG
        {
            ImGuiIO &io = ImGui::GetIO();
            VERIFY(io.DisplaySize.x == 0 || io.DisplaySize.x == static_cast<float>(RenderSurfaceWidth),
                "Render surface width (", RenderSurfaceWidth, ") does not match io.DisplaySize.x (", io.DisplaySize.x, ")");
            VERIFY(io.DisplaySize.y == 0 || io.DisplaySize.y == static_cast<float>(RenderSurfaceHeight),
                "Render surface height (", RenderSurfaceHeight, ") does not match io.DisplaySize.y (", io.DisplaySize.y, ")");
        }
#endif
    }

    Graphics::GraphicsContext &Context;
    Graphics::SwapChain &SwapChain;
};

UniqueReference<ImGuiImplGLFW> g_ImGui;

void Initialize(void *window, Graphics::GraphicsContext &Context, Graphics::SwapChain &SwapChain, const char *ConfigFile)
{
    g_ImGui = std::make_unique<ImGuiImplGLFW>(ReinterpretCast<GLFWwindow>(window), Context, SwapChain, ConfigFile);
}

void Deinitialize()
{
    g_ImGui.reset();
}

void BeginRender()
{
    if (!g_ImGui)
    {
        return;
    }

    const auto &SCDesc = g_ImGui->SwapChain.Data->Handle->GetDesc();
    g_ImGui->NewFrame(SCDesc.Width, SCDesc.Height, SCDesc.PreTransform);
}

void EndRender()
{
    if (!g_ImGui)
    {
        return;
    }

    g_ImGui->Render(g_ImGui->Context.Data->Handle);

    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void CharEvent(void *window, unsigned int c)
{
    ImGui_ImplGlfw_CharCallback(ReinterpretCast<GLFWwindow>(window), c);
}

void KeyEvent(void *window, int key, int scancode, int state, int mods)
{
    ImGui_ImplGlfw_KeyCallback(ReinterpretCast<GLFWwindow>(window), key, scancode, state, mods);
    ImGuiIO &io = ImGui::GetIO();
    if (!io.WantCaptureKeyboard)
    {
        //TODO: Keyboard Input
        //auto w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    }
}

void MouseEvent()
{
    ImGuiIO &io = ImGui::GetIO();
    if (!io.WantCaptureMouse)
    {
        //TODO: Mouse Input
        //auto w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    }
}

void ScrollEvent(void *window, double dx, double dy)
{
    ImGui_ImplGlfw_ScrollCallback(ReinterpretCast<GLFWwindow>(window), dx, dy);
}

ImTextureID TexID(Graphics::Texture &texture)
{
    return (ImTextureID)texture.Data->Handle->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE);
}

}
