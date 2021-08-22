class Sandbox final : public NativeApplication
{
public:

    bool PreInit() override
    {
        MainWindowTitle = "Sandbox";
        return true;
    }

    bool Init() override
    {
        return true;
    }

    void Update(float dt) override
    {

    }

    void UpdateUI(float dt) override
    {
        ImGui::ShowDemoWindow();
    }

    void Draw() override
    {

    }
};

DEFINE_MAIN_APPLICATION(Sandbox)
