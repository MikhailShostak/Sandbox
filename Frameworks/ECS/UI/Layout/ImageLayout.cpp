
namespace UI
{
    
bool/*Success*/ ImageLayout::OnPrePass(ECS::Entity &Entity)
{
    auto [view, image] = Entity.FindComponents<ECS::UIViewComponent, ECS::UIImageComponent>();
    if (!image || !image->Texture)
    {
        return false;
    }

    view->PreferedSize = image->Texture->Size.xy;

    return false;
}

}
