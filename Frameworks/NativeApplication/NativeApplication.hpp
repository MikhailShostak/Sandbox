#pragma once

#include <BasicMath.hpp>
#include <DeviceContext.h>
#include <RefCntAutoPtr.hpp>
#include <RenderDevice.h>
#include <SwapChain.h>

namespace Diligent
{

class ImGuiImplDiligent;

}

class NativeApplication
{
public:
    template<typename T>
    struct Vec { T x = 0, y = 0, z = 0, w = 0; };

    std::string MainWindowTitle = "Application";
    std::string ConfigFile = "config.ini";
    Vec<int> MainWindowSize = { 1280, 720 };
    Vec<float> BackgroundColor = { 0.2f, 0.2f, 0.2f, 1.00f };

    using Clock   = std::chrono::high_resolution_clock;
    using Seconds = std::chrono::duration<float>;
    Clock::time_point m_LastUpdate = {};

    Diligent::RefCntAutoPtr<Diligent::IRenderDevice>  m_pDevice;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
    Diligent::RefCntAutoPtr<Diligent::ISwapChain>     m_pSwapChain;

    NativeApplication();
    virtual ~NativeApplication();

    virtual bool PreInit() { return true; }
    virtual bool Init() { return true; }
    virtual void Update(float dt) {}
    virtual void UpdateUI(float dt) {}
    virtual void PreDraw() {}
    virtual void Draw() {}
    virtual void Terminate() {}

    int Run();

    bool InitEngine();
    bool InitUI();
    void Loop();
    void UpdateWindow();

    void Clear();
    void Flush();

    void Quit();
};

std::unique_ptr<NativeApplication> CreateApp();

#define DEFINE_MAIN_APPLICATION(name) \
std::unique_ptr<NativeApplication> CreateApp() \
{\
    return std::make_unique<name>();\
}
