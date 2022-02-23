#include "PrivateImplementation.hpp"

namespace Graphics
{

Texture::Texture():
    Size(hlslpp::int3{0, 0, 0}),
    Channels(0),
    Filtration(Graphics::TextureFiltration::Bilinear),
    Wrapping(Graphics::TextureWrapping::TiledWrapping)
{

}

Texture::Texture(Texture&& other) = default;
Texture& Texture::operator =(Texture&& other) = default;
Texture::~Texture() = default;

}
