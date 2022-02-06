#pragma once

namespace ImGui
{

void Initialize(void *window, Graphics::GraphicsContext &Context, Graphics::SwapChain &SwapChain, const char *ConfigFile);
void Deinitialize(void* window);

void BeginRender(void* window);
void EndRender();

void CharEvent(void *window, unsigned int c);
void MouseEvent();
void KeyEvent(void *window, int key, int scancode, int state, int mods);
void ScrollEvent(void *window, double dx, double dy);

void PushUIFont();
void PushMonospacedFont();

ImFont* LoadFont(const System::Path& Path, const fpixel_t Size, ImFontConfig* Config = nullptr, const ImWchar* GlyphRange = nullptr);

ImTextureID TexID(Graphics::Texture &texture);
ImTextureID TexID(SharedReference<Graphics::Texture> &texture);

}
