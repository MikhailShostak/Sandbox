#pragma once

inline DynamicAsset<Graphics::Texture> SymbolMask = { "SymbolMask", [](auto &instance)
{
Graphics::LoadTexture(instance, "C:/Assets/Rock/SymbolMask.jpg");
} };
