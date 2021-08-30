#pragma once

class Sandbox final : public NativeApplication
{
public:
    Sandbox();
    ~Sandbox();
    bool PreInit() override;
    bool Init() override;
    void Update(float dt) override;
    void UpdateUI(float dt) override;
    void Draw() override;
};
