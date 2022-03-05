#pragma once

inline DynamicAsset<Graphics::Texture> LavaTexture_Normals = { "LavaTexture_Normals", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_NORM.png");
} };
