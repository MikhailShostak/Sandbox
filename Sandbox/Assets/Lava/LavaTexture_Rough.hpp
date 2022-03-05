#pragma once

inline DynamicAsset<Graphics::Texture> LavaTexture_Rough = { "LavaTexture_Rough", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_ROUGH.png");
} };
