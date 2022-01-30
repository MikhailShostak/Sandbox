#pragma once

struct EditorApplication
    : public Core::Application
{
    using This = EditorApplication;
    using Super = Core::Application;
    EditorApplication();

    virtual ~EditorApplication() {}
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
- Type: EditorWindow
  Values:
    Enabled: true
    Size:
      x: 1900
      y: 1000
    TerminateOnClose: true
    Title: Editor
)";
            Serialization::FromString(data, Components);
        }
    }
};
