#pragma once

namespace Graphics
{

SharedReference<Graphics::Texture> LoadTexture(const System::Path &path);
void SaveTexture(const SharedReference<Graphics::Texture> &texture, const System::Path &path);

}
