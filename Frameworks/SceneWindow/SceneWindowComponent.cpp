void CharCallback(WindowComponent* window, unsigned int c)
{
    auto w = DynamicCast<SceneWindowComponent>(window);
    if (!w)
    {
        return;
    }

}

KeyboardInput keyboardInput;

void KeyCallback(WindowComponent* window, int key, int scancode, int action, int mods)
{
    auto w = DynamicCast<SceneWindowComponent>(window);
    if (!w)
    {
        return;
    }

    keyboardInput.Key = key;
    
    if (action == 1)//GLFW_PRESS)
    {
        w->Scene.OnKeyDown(keyboardInput);
    }
    else if (action == 0)//GLFW_RELEASE)
    {
        w->Scene.OnKeyUp(keyboardInput);
    }
}

TouchInput mouseInput;

void MouseButtonCallback(WindowComponent* window, int button, bool isPressed)
{
    mouseInput.Button = button;

    auto w = DynamicCast<SceneWindowComponent>(window);
    if (!w)
    {
        return;
    }

    if (isPressed)
    {
        w->Scene.OnTouchDown(mouseInput);
    }
    else
    {
        w->Scene.OnTouchUp(mouseInput);
    }
}

void CursorPosCallback(WindowComponent* window, double xpos, double ypos)
{
    mouseInput.Position = Int2{ xpos, ypos };

    auto w = DynamicCast<SceneWindowComponent>(window);
    if (!w)
    {
        return;
    }

    w->Scene.OnTouchMove(mouseInput);
}

void MouseWheelCallback(WindowComponent* window, double dx, double dy)
{
    auto w = DynamicCast<SceneWindowComponent>(window);
    if (!w)
    {
        return;
    }

    WheelInput i;
    i.Position = mouseInput.Position;
    i.Delta = dy;
    w->Scene.OnWheelMove(i);
}

EScene g_RootScene; //Hack

void SceneWindowComponent::Load(Core::Application& Application)
{
    Super::Load(Application);

    Initialize();

    Scene.m_GraphicsContext = &this->GraphicsContext;
    Scene.m_Resolution = this->Size;

    Scene.OnLoad(g_RootScene);
}

void SceneWindowComponent::Unload(Core::Application& Application)
{
    Scene.OnUnload(g_RootScene);

    Super::Unload(Application);
}

void SceneWindowComponent::Update(Core::Application& Application)
{
    Super::Update(Application);
}

void SceneWindowComponent::PreDraw()
{
    g_RootScene.DeltaTime = FrameCounter.CountAs<DateTime::SecondRatio>();
    Scene.OnUpdate(g_RootScene);
    Super::Draw();
}
