#pragma once

namespace ECS
{

void Load(EScene &scene);
void Unload(EScene& scene);
void Update(EScene& scene);

template<typename Type>
inline Type* FindSystem(EScene& scene)
{
    for (auto& s : scene.Systems)
    {
        if (Type* system = DynamicCast<Type>(s.get()))
        {
            return system;
        }
    }

    return nullptr;
}

template<typename ...Components>
inline std::tuple<Entity, Components &...> CreateEntity(EScene& scene)
{
    const auto entity = scene.Registry.create();
    return { { &scene, entity }, scene.Registry.emplace<Components>(entity)... };
}

template<typename ...Components>
inline std::tuple<Components &...> CreateComponents(EScene& scene)
{
    const auto entity = scene.Registry.create();
    return { scene.Registry.emplace<Components>(entity)... };
}

}
