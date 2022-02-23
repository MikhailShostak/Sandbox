#pragma once

inline DynamicAsset<Graphics::Texture> TestTexture = { "TestTexture", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/uv.jpg");
} };
