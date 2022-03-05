#pragma once

inline DynamicAsset<Graphics::Texture> LavaTexture_Displacement = { "LavaTexture_Displacement", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Lava/Lava_DISP.png");
} };
