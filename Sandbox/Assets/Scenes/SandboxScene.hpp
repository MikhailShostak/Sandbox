#pragma once

inline DynamicAsset<EScene> SandboxScene = { "SandboxScene", [](auto &instance)
{
Serialization::FromString(R"(
Systems:
  - Type: ECS.GraphicsSystem
  - Type: SandboxMainSystem
  - Type: ECS.LayoutSystem
    Values:
      Layouts:
        - Type: UI.ImageLayout
        - Type: UI.TextLayout
        - Type: UI.FlexBoxLayout
  - Type: ECS.ImGuiSystem
  - Type: ECS.UIInputSystem
    Values:
      Sensetivity:
        x: 0.100000001
        y: 0.100000001
      Speed: 0.0399999991
      SprintFactor: 5
  - Type: ECS.PawnSystem
  - Type: ECS.MovementSystem
)",
instance);
} };
