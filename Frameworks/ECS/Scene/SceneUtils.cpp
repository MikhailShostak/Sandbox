namespace ECS
{

void Load(EScene &scene)
{
    for (auto& system : scene.Systems)
    {
        system->OnLoad(scene);
    }
}

void Unload(EScene& scene)
{
    for (auto& system : scene.Systems)
    {
        system->OnUnload(scene);
    }
}

void Update(EScene& scene)
{
    for (auto& system : scene.Systems)
    {
        system->OnUpdate(scene);
    }
}

}
