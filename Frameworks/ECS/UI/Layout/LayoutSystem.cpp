
namespace ECS
{

void PrePass(ECS::Entity &entity)
{

}

void Layout(ECS::Entity &entity)
{
    auto [view, h] = entity.FindComponents<UIViewComponent, HirerachyComponent>();
    if (!view || !h)
    {
        return;
    }

    for (auto &child : h->Children)
    {
        auto& c = child.GetComponent<UIViewComponent>();
        c.GlobalPosition = view->GlobalPosition + c.Position;
        Layout(child);
    }
}

void LayoutSystem::OnUpdate(EScene& scene)
{
    auto v = scene.Registry.view<ECS::RootComponent>();
    for (const auto &[id, c] : v.each())
    {
        ECS::Entity entity = { &scene, id };
        WalkFromChildren(entity, [this](ECS::Entity& entity)
        {
            for (auto &layout : Layouts)
            {
                if (layout->OnPrePass(entity))
                {
                    break;
                }
            }
            return false;
        });

        WalkFromParent(entity, [this](ECS::Entity &entity)
        {
            for (auto &layout : Layouts)
            {
                if (layout->OnLayout(entity))
                {
                    break;
                }
            }
            return false;
        });
    }
}

}
