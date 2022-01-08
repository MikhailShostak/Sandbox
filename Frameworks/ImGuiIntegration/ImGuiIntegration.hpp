#pragma once

namespace ImGui
{

void Initialize(void *window, Graphics::GraphicsContext &Context, Graphics::SwapChain &SwapChain, const char *ConfigFile);
void Deinitialize();

void BeginRender();
void EndRender();

void CharEvent(void *window, unsigned int c);
void MouseEvent();
void KeyEvent(void *window, int key, int scancode, int state, int mods);
void ScrollEvent(void *window, double dx, double dy);

ImTextureID TexID(Graphics::Texture &texture);
inline ImTextureID TexID(SharedReference<Graphics::Texture> &texture) { return TexID(*texture.get()); }

}
