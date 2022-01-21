#pragma once

struct WindowComponent
    : public Core::ApplicationComponent
{
    using This = WindowComponent;
    using Super = Core::ApplicationComponent;
    String Title = {};
    Int2 Size = {};
    Color BackgroundColor = {};
    Graphics::GraphicsContext GraphicsContext = {};
    Graphics::SwapChain SwapChain = {};
    DateTime::Counter<DateTime::HighResolution::Clock> FrameCounter = {};
    NativeWindowHandle Handle = {};
    bool TerminateOnClose = {};

    virtual ~WindowComponent() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Title"] & Title;
        data["Size"] & Size;
        data["BackgroundColor"] & BackgroundColor;
        data["TerminateOnClose"] & TerminateOnClose;
    }
    virtual void Load(Core::Application & Application);
    virtual void Unload(Core::Application & Application);
    virtual void Update(Core::Application & Application);
    virtual void CreateWindowHandle();
    virtual void DestroyWindowHandle();
    virtual void CreateGraphicsContext();
    virtual void DestroyGraphicsContext();
    virtual void CreateUI();
    virtual void DestroyUI();
    virtual void Render();
    virtual void Clear();
    virtual void Draw();
    virtual void Flush();
    virtual void Show();
    virtual void Hide();

    void Initialize()
    {
        Super::Initialize();
    }
};
