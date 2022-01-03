#include "PrivateImplementation.hpp"

namespace Graphics
{

Texture::Texture():
    Size(hlslpp::int3{0, 0, 0}),
    Channels(0),
    Filtration(Graphics::TextureFiltration::Bilinear),
    Wrapping(Graphics::TextureWrapping::WrapToBorder)
{

}

Texture::~Texture()
{

}

}
