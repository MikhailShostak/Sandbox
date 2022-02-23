#pragma once

struct SandboxApplication
    : public Core::Application
{
    using This = SandboxApplication;
    using Super = Core::Application;
    SandboxApplication();

    virtual ~SandboxApplication() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
        Super::Initialize();
        {
            String data =
R"(
- Type: SceneWindowComponent
  Values:
    Enabled: true
    Scene:
      Scenes:
        - Type: SandboxScene
    Size:
      x: 800
      y: 600
    TerminateOnClose: true
    Title: Sandbox
)";
            Serialization::FromString(data, Components);
        }
    }
};
