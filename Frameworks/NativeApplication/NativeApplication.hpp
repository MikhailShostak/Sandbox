#pragma once

#include <Utils.hpp>

class NativeApplication
{
public:
    template<typename T>
    struct Vec { T x = 0, y = 0, z = 0, w = 0; };

    std::string MainWindowTitle = "Application";
    std::string ConfigFile = "config.ini";
    Vec<int> MainWindowSize = { 1280, 720 };
    Vec<float> BackgroundColor = { 0.2f, 0.2f, 0.2f, 1.00f };

    NativeApplication();
    virtual ~NativeApplication();

    virtual bool PreInit() { return true; }
    virtual bool Init() { return true; }
    virtual void Update([[maybe_unused]] float dt) {}
    virtual void UpdateUI([[maybe_unused]] float dt) {}
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

    InplaceStorage<struct NativeApplicationData, 32, 8> m_Data;
};

std::unique_ptr<NativeApplication> CreateApp();

#define DEFINE_MAIN_APPLICATION(name) \
std::unique_ptr<NativeApplication> CreateApp() \
{\
    return std::make_unique<name>();\
}
