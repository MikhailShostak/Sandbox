#pragma once

inline DynamicAsset<Graphics::Texture> SkyTexture = { "SkyTexture", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Sky-small.jpg");
} };
