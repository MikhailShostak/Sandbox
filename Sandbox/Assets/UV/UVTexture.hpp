#pragma once

inline DynamicAsset<Graphics::Texture> UVTexture = { "UVTexture", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/UV.jpg");
} };
