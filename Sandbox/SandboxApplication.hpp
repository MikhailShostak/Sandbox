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
- Type: UI.ViewWindowComponent
  Values:
    BackgroundColor:
      w: 1
      x: 1
      y: 0
      z: 0
    Enabled: true
    Size:
      x: 800
      y: 480
    TerminateOnClose: true
    Title: Sandbox (Red)
    Views:
      - Type: UI.DemoView
- Type: UI.ViewWindowComponent
  Values:
    BackgroundColor:
      w: 1
      x: 0
      y: 1
      z: 0
    Enabled: true
    Size:
      x: 800
      y: 480
    Title: Sandbox (Green)
    Views:
      - Type: UI.DemoView
- Type: UI.ViewWindowComponent
  Values:
    BackgroundColor:
      w: 1
      x: 0
      y: 0
      z: 1
    Enabled: true
    Size:
      x: 800
      y: 480
    Title: Sandbox (Blue)
    Views:
      - Type: UI.DemoView
)";
            Serialization::FromString(data, Components);
        }
    }
};
