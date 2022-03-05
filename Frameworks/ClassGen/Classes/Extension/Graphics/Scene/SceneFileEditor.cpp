namespace ClassGen
{

template<typename Type>
auto SamePointer(const Type& value)
{
    return [&value](auto& item)
    {
        return &item == value;
    };
}

struct SceneEditorComponent
{
    String Name;
    Map<String, ECS::EntityComponent*> Components;

    ECS::EntityComponent *FindComponent(const String &name)
    {
        auto it = Components.find(name);
        if (it != Components.end())
        {
            return it->second;
        }
        return nullptr;
    }
};

void SceneFileEditor::RenderFile()
{
    auto sceneInfo = DynamicCast<ClassGen::SceneInfo>(Data.Instance);
    Viewport.Draw([&]() {
        if (ImGui::Button((Simulation ? ICON_PAUSE : ICON_PLAY_ARROW).data()))
        {
            Simulation = !Simulation;
            Outdated = false;
            Viewport.ContentScene->Registry.clear();
        }
    });

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("Add System"))
        {
            ClassGen::InstanceInfo s;
            s.Type = "ECS.System";
            sceneInfo->Systems.push_back(std::move(s));
            MarkFileDirty(Path);
            Outdated = false;
        }
        if (ImGui::MenuItem("Add Entity"))
        {
            ClassGen::EntityInfo e;
            e.Name = "NewEntity";
            sceneInfo->Entities.push_back(std::move(e));
            MarkFileDirty(Path);
            Outdated = false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::Begin("Systems"))
    {
        if (!SystemDataEditor.Changed)
        {
            Serialization::Convert(sceneInfo->Systems, SystemDataEditor.Value);
            SystemDataEditor.Changed = [&]()
            {
                Serialization::Convert(SystemDataEditor.Value, sceneInfo->Systems);
                MarkFileDirty(Path);
            };
            Serialization::FromString("Array<UniqueReference<ECS.System>>", SystemDataEditor.TypeInfo);
            SystemDataEditor.FileInfo = FindClassByName(SystemDataEditor.TypeInfo.Name);
            SystemDataEditor.ID = fmt::format("##SystemValue{}", fmt::ptr(&DataEditor));
        }

        ImGui::Columns(2);
        ImGui::Text("Systems");
        ImGui::NextColumn();
        SystemDataEditor.Draw();
        ImGui::Columns(1);
    }
    ImGui::End();

    static ClassGen::EntityInfo* selectedEntity = nullptr;
    if (ImGui::Begin("Entities"))
    {
        ClassGen::EntityInfo* entityToDelete = nullptr;
        bool selection = false;
        size_t i = 0;
        for (auto& entity : sceneInfo->Entities)
        {
            bool selected = selectedEntity == &entity;
            if (ImGui::Selectable(fmt::format("{}##Entity", entity.Name).data(), &selected))
            {
                selectedEntity = &entity;

                //HACK: come up with a proper way to reset ObjectPropertyEditor
                ComponentDataEditor.Changed = nullptr;
                ComponentDataEditor.PropertyEditors.clear();
            }
            selection |= selected;

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::Selectable(fmt::format("Remove##Entity{}", fmt::ptr(&entity)).data()))
                {
                    entityToDelete = &entity;
                }
                ImGui::EndPopup();
            }
        }

        if (entityToDelete)
        {
            boost::remove_erase_if(sceneInfo->Entities, SamePointer(entityToDelete));
            if (entityToDelete == selectedEntity)
            {
                selectedEntity = nullptr;
            }
            MarkFileDirty(Path);
        }
        if (!selection)
        {
            selectedEntity = nullptr;
        }

        if (ImGui::Begin("Components"))
        {
            if (selectedEntity)
            {
                /*SceneEditorComponent* selectedEditorComponent = nullptr;
                auto view = Viewport.ContentScene->Registry.view<SceneEditorComponent>();
                view.each([&](const auto& id, auto& sceneEditorComponent) {
                    if (selectedEntity->Name == sceneEditorComponent.Name)
                    {
                        selectedEditorComponent = &sceneEditorComponent;
                    }
                });*/

                if (!ComponentDataEditor.Changed)
                {
                    Serialization::Convert(selectedEntity->Components, ComponentDataEditor.Value);
                    ComponentDataEditor.Changed = [&]()
                    {
                        Serialization::Convert(ComponentDataEditor.Value, selectedEntity->Components);
                        MarkFileDirty(Path);

                        for (auto& componentInfo : selectedEntity->Components)
                        {
                            auto [entity, component] = ECS::FindPersistentEntity(*Viewport.ContentScene, selectedEntity->Name);
                            ECS::PersistentComponent* comp = component;
                            auto FindComponent = [&](const String& name) -> ECS::EntityComponent*
                            {
                                auto componentClass = Reflection::Find<ECS::EntityComponent>(name);
                                auto it = ranges::find_if(comp->Components, [&](auto& c) { return Reflection::Find<ECS::EntityComponent>(*c) == componentClass; });
                                if (it != comp->Components.end())
                                {
                                    return *it;
                                }
                                return nullptr;
                            };
                            ECS::EntityComponent* selectedComponentInstance = FindComponent(componentInfo.Type);
                            Reflection::Deserialize(Serialization::Serialize(componentInfo.Values), *selectedComponentInstance);
                        }
                    };
                    Serialization::FromString("Array<UniqueReference<ECS.EntityComponent>>", ComponentDataEditor.TypeInfo);
                    ComponentDataEditor.FileInfo = FindClassByName(ComponentDataEditor.TypeInfo.Name);
                    ComponentDataEditor.ID = fmt::format("##ComponentValue{}", fmt::ptr(&DataEditor));
                }

                ImGui::Columns(2);
                ImGui::Text("Components");
                ImGui::NextColumn();
                ComponentDataEditor.Draw();
                ImGui::Columns(1);
            }
        }
        ImGui::End();
    }
    ImGui::End();

    if (!Outdated)
    {
        Outdated = true;

        /*if (Simulation)
        {
            ECS::g_AllocationEntity.Scene = Viewport.ContentScene.get();
            for (auto& systemInfo : sceneInfo->Systems)
            {
                auto ref = Serialization::Convert<UniqueReference<ECS::System>>(systemInfo);
                if (!ref)
                {
                    continue;
                }

                ref->m_GraphicsContext = g_GraphicsContext;
                ref->m_Resolution = Viewport.Texture->Size.xy;
                Viewport.ContentScene->Systems.push_back(std::move(ref));
            }
            ECS::g_AllocationEntity.Scene = nullptr;
        }*/

        Viewport.ContentScene->Registry.clear();
        Serialization::Convert(*sceneInfo, *Viewport.ContentScene);
        if (!Simulation)
        {
            Viewport.ContentScene->Systems.clear();
        }

        /*Map<String, ECS::Entity> entities;
        auto view = Viewport.ContentScene->Registry.view<SceneEditorComponent>();
        view.each([&](const auto& id, auto &sceneEditorComponent) {
            entities.insert({ sceneEditorComponent.Name, ECS::Entity{ Viewport.ContentScene.get(), id } });
        });

        for (auto &entityInfo : sceneInfo->Entities)
        {
            auto it = entities.find(entityInfo.Name);
            if (it == entities.end())
            {
                auto [entity, sceneEditorComponent] = ECS::CreateEntity<SceneEditorComponent>(*Viewport.ContentScene);
                sceneEditorComponent.Name = entityInfo.Name;
                ECS::g_AllocationEntity = entity;
                for (auto &componentInfo : entityInfo.Components)
                {
                    //TODO: UniqueReference is used to apply polymorphic serialization, come up with better solution
                    auto ref = Serialization::Convert<UniqueReference<ECS::EntityComponent>>(componentInfo);
                    sceneEditorComponent.Components.insert({ componentInfo.Type, ref.release() });
                }
                ECS::g_AllocationEntity = {};

                auto meshComponent = DynamicCast<ECS::MeshComponent>(sceneEditorComponent.FindComponent("ECS.MeshComponent"));
                if (meshComponent)
                {
                    auto fileInfo = ClassGen::FindClassByName("TestMesh");
                    if (auto meshInfo = DynamicCast<ClassGen::MeshInfo>(fileInfo.Instance))
                    {
                        auto graphics = ECS::FindSystem<ECS::GraphicsSystem>(*Viewport.ViewportScene);
                        if (graphics)
                        {
                            meshComponent->Mesh = meshInfo->Load(*g_GraphicsContext, graphics->GBuffer.GetBuffer());
                            meshComponent->Material = meshInfo->MaterialInstance;
                        }
                    }
                }
            }

        }*/
    }
}

}
