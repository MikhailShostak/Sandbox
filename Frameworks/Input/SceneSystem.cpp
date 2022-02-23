namespace ECS
{

void SceneSystem::OnLoad(EScene& Scene)
{
    for (auto &scene : Scenes)
    {
        for (auto& system : scene->Systems)
        {
            system->m_GraphicsContext = m_GraphicsContext;
            system->m_Resolution = m_Resolution;
        }
    }

    for (auto& scene : Scenes)
    {
        ECS::Load(*scene);
    }
}

void SceneSystem::OnUnload(EScene& Scene)
{
    for (auto& scene : Scenes)
    {
        ECS::Unload(*scene);
    }
}

void SceneSystem::OnUpdate(EScene& Scene)
{
    for (auto& scene : Scenes)
    {
        scene->DeltaTime = Scene.DeltaTime;
        ECS::Update(*scene);
    }

    //TODO: rework scene composition
    ECS::GraphicsSystem* graphics = ECS::FindSystem<ECS::GraphicsSystem>(Scene);
    if (graphics)
    {
        for (auto& scene : Scenes)
        {
            graphics->Render(*scene);
        }
    }
}

bool/*Handled*/ SceneSystem::OnTouchDown(const TouchInput& Input)
{
    for (auto& scene : Scenes)
    {
        if (auto input = ECS::FindSystem<ECS::InputSystem>(*scene))
        {
            if (input->OnTouchDown(Input))
            {
                return true;
            }
        }
    }
    return false;
}

bool/*Handled*/ SceneSystem::OnTouchMove(const TouchInput& Input)
{
    for (auto& scene : Scenes)
    {
        if (auto input = ECS::FindSystem<ECS::InputSystem>(*scene))
        {
            if (input->OnTouchMove(Input))
            {
                return true;
            }
        }
    }
    return false;
}

bool/*Handled*/ SceneSystem::OnTouchUp(const TouchInput& Input)
{
    for (auto& scene : Scenes)
    {
        if (auto input = ECS::FindSystem<ECS::InputSystem>(*scene))
        {
            if (input->OnTouchUp(Input))
            {
                return true;
            }
        }
    }
    return false;
}

bool/*Handled*/ SceneSystem::OnWheelMove(const WheelInput& Input)
{
    for (auto& scene : Scenes)
    {
        if (auto input = ECS::FindSystem<ECS::InputSystem>(*scene))
        {
            if (input->OnWheelMove(Input))
            {
                return true;
            }
        }
    }
    return false;
}

bool/*Handled*/ SceneSystem::OnKeyDown(const KeyboardInput& Input)
{
    for (auto& scene : Scenes)
    {
        if (auto input = ECS::FindSystem<ECS::InputSystem>(*scene))
        {
            if (input->OnKeyDown(Input))
            {
                return true;
            }
        }
    }
    return false;
}

bool/*Handled*/ SceneSystem::OnKeyUp(const KeyboardInput& Input)
{
    for (auto& scene : Scenes)
    {
        if (auto input = ECS::FindSystem<ECS::InputSystem>(*scene))
        {
            if (input->OnKeyUp(Input))
            {
                return true;
            }
        }
    }
    return false;
}

}
