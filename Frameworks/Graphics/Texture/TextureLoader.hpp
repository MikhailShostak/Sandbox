#pragma once

namespace Graphics
{

SharedReference<Graphics::Texture> CreateTextureBuffer(const Int3& size);
SharedReference<Graphics::Texture> CreateTexture(const Color& color, const Int3& size = { 1, 1, 1 });

void LoadTexture(Graphics::Texture& texture, const System::Path& path);
SharedReference<Graphics::Texture> LoadTexture(const System::Path &path);
void SaveTexture(const SharedReference<Graphics::Texture> &texture, const System::Path &path);

}
