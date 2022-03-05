#pragma once

namespace ECS
{

void Load(EScene &scene);
void Unload(EScene& scene);
void Update(EScene& scene);

template<typename SystemType>
inline SystemType* FindSystem(EScene& scene)
{
    for (auto& s : scene.Systems)
    {
        if (SystemType* system = DynamicCast<SystemType>(s.get()))
        {
            return system;
        }
    }

    return nullptr;
}

template<typename SystemType>
inline SystemType* FindSystems(EScene& scene)
{
    Array<SystemType*> systems;

    for (auto& s : scene.Systems)
    {
        if (SystemType* system = DynamicCast<SystemType>(s.get()))
        {
            systems.push_back(system);
        }
    }

    return systems;
}

template<typename ...ComponentTypes>
inline std::tuple<Entity, ComponentTypes &...> CreateEntity(EScene& scene)
{
    const auto entity = scene.Registry.create();
    return { { &scene, entity }, scene.Registry.emplace<ComponentTypes>(entity)... };
}

template<typename ...ComponentTypes>
inline std::tuple<ComponentTypes &...> CreateComponents(EScene& scene)
{
    const auto entity = scene.Registry.create();
    return { scene.Registry.emplace<ComponentTypes>(entity)... };
}

inline decltype(auto) FindPersistentEntity(EScene& Scene, const String& EntityName)
{
    std::tuple<ECS::Entity, ECS::PersistentComponent*> result{};
    auto v = Scene.Registry.view<ECS::PersistentComponent>();
    for (const auto& [id, component] : v.each())
    {
        if (component.Name == EntityName)
        {
            result = { { &Scene, id }, &component };
        }
    }
    return result;
};

template<typename ComponentType>
inline decltype(auto) FindPersistentComponent(EScene& Scene, const String& EntityName)
{
    auto [Entity, PersistentComponent] = FindPersistentEntity(Scene, EntityName);
    ComponentType* result = PersistentComponent ? Entity.FindComponent<ComponentType>() : nullptr;
    return result;
};

template<typename ...ComponentTypes>
inline decltype(auto) FindPersistentComponents(EScene& Scene, const String& EntityName)
{
    auto [Entity, PersistentComponent] = FindPersistentEntity(Scene, EntityName);
    std::tuple<ComponentTypes*...> result = PersistentComponent ? Entity.FindComponents<ComponentTypes...>() : std::tuple<ComponentTypes*...>{};
    return result;
};

}
