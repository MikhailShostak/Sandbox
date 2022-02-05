#pragma once

inline DynamicAsset<System::ConfigFile<EditorConfig>> EditorConfigData = { "EditorConfigData", [](auto &instance)
{
Serialization::FromString(R"(
Path: config.yaml
)",
instance);
} };
