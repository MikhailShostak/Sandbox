
namespace ECS
{

void PrePass(const ECS::Entity &entity)
{

}

void Layout(const ECS::Entity &entity)
{
    auto [view, h] = g_Registry.try_get<UIViewComponent, HirerachyComponent>(entity);
    if (!view || !h)
    {
        return;
    }

    for (auto &child : h->Children)
    {
        auto &c = g_Registry.get<UIViewComponent>(child);
        c.GlobalPosition = view->GlobalPosition + c.Position;
        Layout(child);
    }
}

void LayoutSystem::OnUpdate()
{
    auto v = g_Registry.view<ECS::RootComponent>();
    for (const auto &[e, c] : v.each())
    {
        WalkFromChildren(e, [this](const ECS::Entity &entity)
        {
            for (auto &layout : Layouts)
            {
                auto [success] = layout->OnPrePass(entity);
                if (success)
                {
                    break;
                }
            }
        });

        WalkFromParent(e, [this](const ECS::Entity &entity)
        {
            for (auto &layout : Layouts)
            {
                auto [success] = layout->OnLayout(entity);
                if (success)
                {
                    break;
                }
            }
        });
    }
}

}
