#pragma once

inline DynamicAsset<Graphics::Texture> GridTexture = { "GridTexture", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Grid.png");
} };
