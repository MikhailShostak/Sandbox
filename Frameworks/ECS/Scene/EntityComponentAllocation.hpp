#pragma once

namespace ECS
{

inline thread_local ECS::Entity g_AllocationEntity;

}

namespace Memory
{

template<typename Type>
struct Constructor<Type, ECS::EntityComponent>
{
    inline static Type* Create()
    {
        auto &component = ECS::g_AllocationEntity.AddComponent<Type>();
        component.Initialize();
        return &component;
    }
};

}

namespace Serialization
{

template<>
struct ObjectSerializer<ECS::Entity>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        auto& persistentComponent = ECS::g_AllocationEntity.GetComponent<ECS::PersistentComponent>();

        //Asset Instance
        //TODO

        //Local reference
        auto it = data.m_Data.find("Type");
        if (it != data.m_Data.end())
        {
            Serialization::InputValue typeData{};
            String localRefName;
            it->second & localRefName;
            if (!localRefName.empty() && localRefName.back() == '$')
            {
                localRefName.resize(localRefName.size() - 1);
                auto v = ECS::g_AllocationEntity.Scene->Registry.view<ECS::PersistentComponent>();
                for (const auto &[e, c] : v.each())
                {
                    if (c.Name == localRefName)
                    {
                        value = { ECS::g_AllocationEntity.Scene, e };
                    }
                }
            }

            return;
        }

        //Local Instance
        Array<UniqueReference<ECS::EntityComponent>> components;
        data["Components"] & components;
        persistentComponent.Components.reserve(components.size());
        for (auto& c : components)
        {
            persistentComponent.Components.push_back(c.release());
        }
    }
};

template<>
struct ObjectSerializer<EScene>
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType&& data, ValueType&& value)
    {
        Array<Serialization::Data> entities;
        data["Entities"] & entities;

        size_t i = 0;
        Array<entt::entity> IDs;
        IDs.reserve(entities.size());
        for (auto& entity : entities)
        {
            auto id = value.Registry.create();
            auto& component = value.Registry.emplace<ECS::PersistentComponent>(id);
            Serialization::Deserialize(entity, component);
            if (component.Name.empty())
            {
                component.Name = fmt::format("Entity_{}", i++);
            }
            IDs.push_back(id);
        }

        ECS::g_AllocationEntity.Scene = &value;
        for (size_t i = 0; i < entities.size(); ++i)
        {
            ECS::g_AllocationEntity.ID = IDs[i];
            ECS::Entity entity;
            Serialization::Deserialize(entities[i], entity);
        }

        value.Serialize(data);
        ECS::g_AllocationEntity.Scene = nullptr;
    }
};

}
