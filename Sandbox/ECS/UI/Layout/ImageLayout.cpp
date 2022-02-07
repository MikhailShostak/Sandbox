
namespace UI
{
    
std::tuple<bool/*Success*/> ImageLayout::OnPrePass(const ECS::Entity &Entity)
{
    auto [view, image] = ECS::g_Registry.try_get<ECS::UIViewComponent, ECS::UIImageComponent>(Entity);
    if (!image || !image->Texture)
    {
        return { false };
    }

    view->PreferedSize = image->Texture->Size.xy;

    return { false };
}

}
