namespace ECS
{

bool ProcessTouchInput(EScene *scene, Meta::MethodPointer<InputHandler, bool, EScene &, const TouchInput &, bool> method, const TouchInput &Input)
{
    if (!scene)
    {
        return false;
    }

    auto v = scene->Registry.view<ECS::RootComponent>();
    for (const auto& [id, c] : v.each())
    {
        ECS::Entity entity = { scene, id };

        if (WalkFromParent(entity, [&](ECS::Entity& entity)
        {
            auto [view, input] = entity.FindComponents<UIViewComponent, ECS::InputComponent>();
            if (!view || !input)
            {
                return false;
            }

            bool inside =
                (float)view->GlobalPosition.x <= (float)Input.Position.x && (float)Input.Position.x <= (float)(view->GlobalPosition.x + view->Size.x) &&
                (float)view->GlobalPosition.y <= (float)Input.Position.y && (float)Input.Position.y <= (float)(view->GlobalPosition.y + view->Size.y);

            for (auto& handler : input->Handlers)
            {
                if ((*handler.*method)(*scene, Input, inside))
                {
                    return true;
                }
            }

            return false;
        }))
        {
            return true;
        }
    }
    return false;
}

bool ProcessKeyboardInput(EScene* scene, Meta::MethodPointer<InputHandler, bool, EScene&, const KeyboardInput&> method, const KeyboardInput& Input)
{
    if (!scene)
    {
        return false;
    }

    auto v = scene->Registry.view<ECS::RootComponent>();
    for (const auto& [id, c] : v.each())
    {
        ECS::Entity entity = { scene, id };

        if (WalkFromParent(entity, [&](ECS::Entity& entity)
        {
            auto [view, input] = entity.FindComponents<UIViewComponent, ECS::InputComponent>();
            if (!view || !input)
            {
                return false;
            }

            for (auto& handler : input->Handlers)
            {
                if ((*handler.*method)(*scene, Input))
                {
                    return true;
                }
            }

            return false;
        }))
        {
            return true;
        }
    }
    return false;
}

bool/*Handled*/ UIInputSystem::OnTouchDown(const TouchInput& Input)
{
    return ProcessTouchInput(m_Scene, &InputHandler::OnTouchDown, Input);
}

bool/*Handled*/ UIInputSystem::OnTouchMove(const TouchInput & Input)
{
    return ProcessTouchInput(m_Scene, &InputHandler::OnTouchMove, Input);
}

bool/*Handled*/ UIInputSystem::OnTouchUp(const TouchInput& Input)
{
    return ProcessTouchInput(m_Scene, &InputHandler::OnTouchUp, Input);
}

bool/*Handled*/ UIInputSystem::OnKeyDown(const KeyboardInput& Input)
{
    return ProcessKeyboardInput(m_Scene, &InputHandler::OnKeyDown, Input);
}

bool/*Handled*/ UIInputSystem::OnKeyUp(const KeyboardInput& Input)
{
    return ProcessKeyboardInput(m_Scene, &InputHandler::OnKeyUp, Input);
}

void UIInputSystem::OnUpdate(EScene& Scene)
{
    m_Scene = &Scene;
}

}
