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
        imguiContext = ImGui::GetCurrentContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.IniFilename = ConfigFile;

        FontConfig.MergeMode = true;

        ImGui_ImplGlfw_InitForOther(window, false);
    }

    ~ImGuiImplGLFW()
    {
        if (imguiContext)
        {
            ImGui::SetCurrentContext(imguiContext);
            ImGui_ImplGlfw_Shutdown();
        }
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
        Textures.clear();

        VERIFY(SurfacePreTransform == Diligent::SURFACE_TRANSFORM_IDENTITY, "Unexpected surface pre-transform");

        if (RebuildFonts)
        {
            UpdateFontsTexture();
            RebuildFonts = false;
        }

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
    Graphics::SwapChain& SwapChain;

    bool RebuildFonts = false;
    ImGuiContext* imguiContext = nullptr;

    ImFontConfig FontConfig;

    ImFont* DefaultUIFont = nullptr;
    ImFont* DefaultMonospacedFont = nullptr;

    Array<SharedReference<Graphics::Texture>> Textures;
};

Map<void*, UniqueReference<ImGuiImplGLFW>> g_ImGui;
ImGuiImplGLFW* g_CurrentImGui = nullptr;

ImFont* LoadFontInternaly(void* window, const System::Path& Path, const fpixel_t Size, ImFontConfig* Config = nullptr, const ImWchar* GlyphRange = nullptr)
{
    auto& imgui = g_ImGui[window];
    imgui->RebuildFonts = true;
    ImGuiIO& io = ImGui::GetIO();
    return io.Fonts->AddFontFromFileTTF(Path.generic_string().data(), Size, Config, GlyphRange);
}

void Initialize(void *window, Graphics::GraphicsContext &Context, Graphics::SwapChain &SwapChain, const char *ConfigFile)
{
    auto &imgui = g_ImGui[window];
    ImGui::SetCurrentContext(nullptr);
    imgui = std::make_unique<ImGuiImplGLFW>(ReinterpretCast<GLFWwindow>(window), Context, SwapChain, ConfigFile);

#if BOOST_OS_WINDOWS
    imgui->DefaultMonospacedFont = LoadFontInternaly(window, "C:/Windows/Fonts/consola.ttf", 10_pt);
    imgui->DefaultUIFont = LoadFontInternaly(window, "C:/Windows/Fonts/segoeui.ttf", 12_pt);
#else
    ImFont* font = ImGui::GetDefaultFont();
    imgui->DefaultMonospacedFont = font;
    imgui->DefaultUIFont = font;
#endif
}

void Deinitialize(void* window)
{
    auto &imgui = g_ImGui[window];
    imgui.reset();
    g_ImGui.erase(window);
}

void BeginRender(void* window)
{
    g_CurrentImGui = g_ImGui[window].get();
    if (!g_CurrentImGui)
    {
        return;
    }
    ImGui::SetCurrentContext(g_CurrentImGui->imguiContext);

    const auto &SCDesc = g_CurrentImGui->SwapChain.Data->Handle->GetDesc();
    g_CurrentImGui->NewFrame(SCDesc.Width, SCDesc.Height, SCDesc.PreTransform);

    ImGui::PushUIFont();
}

void EndRender()
{
    if (!g_CurrentImGui)
    {
        return;
    }

    ImGui::PopFont();

    g_CurrentImGui->Render(g_CurrentImGui->Context.Data->Handle);

    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
    g_CurrentImGui = nullptr;
}

void CharEvent(void *window, unsigned int c)
{
    auto& imgui = g_ImGui[window];
    SetCurrentContext(imgui->imguiContext);
    ImGui_ImplGlfw_CharCallback(ReinterpretCast<GLFWwindow>(window), c);
    SetCurrentContext(nullptr);
}

void KeyEvent(void *window, int key, int scancode, int state, int mods)
{
    auto& imgui = g_ImGui[window];
    SetCurrentContext(imgui->imguiContext);
    ImGui_ImplGlfw_KeyCallback(ReinterpretCast<GLFWwindow>(window), key, scancode, state, mods);
    ImGuiIO &io = ImGui::GetIO();
    if (!io.WantCaptureKeyboard)
    {
        //TODO: Keyboard Input
        //auto w = static_cast<NativeApplication*>(glfwGetWindowUserPointer(window));
    }
    SetCurrentContext(nullptr);
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
    auto& imgui = g_ImGui[window];
    SetCurrentContext(imgui->imguiContext);
    ImGui_ImplGlfw_ScrollCallback(ReinterpretCast<GLFWwindow>(window), dx, dy);
    SetCurrentContext(nullptr);
}

void PushUIFont()
{
    ImGui::PushFont(g_CurrentImGui->DefaultUIFont);
}

void PushMonospacedFont()
{
    ImGui::PushFont(g_CurrentImGui->DefaultMonospacedFont);
}

ImFont* LoadFont(const System::Path& Path, const fpixel_t Size, ImFontConfig *Config, const ImWchar* GlyphRange)
{
    for (auto &[window, imgui] : g_ImGui)
    {
        LoadFontInternaly(window, Path, Size, Config, GlyphRange);
    }

    return nullptr;
}

ImTextureID TexID(Graphics::Texture &texture)
{
    if(!texture.Data->Handle)
    {
        g_CurrentImGui->Context.Create2DTexture(texture);
    }

    return (ImTextureID)texture.Data->Handle->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE);
}

ImTextureID TexID(SharedReference<Graphics::Texture> &texture)
{
    g_CurrentImGui->Textures.push_back(texture);
    return TexID(*texture.get());
}

}
