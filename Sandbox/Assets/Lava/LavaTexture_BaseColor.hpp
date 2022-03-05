#pragma once

inline DynamicAsset<Graphics::Texture> LavaTexture_BaseColor = { "LavaTexture_BaseColor", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_COLOR.png");
} };
