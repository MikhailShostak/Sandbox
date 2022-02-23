#pragma once

namespace ECS
{

void MovementSystem::OnUpdate(EScene& Scene)
{
    auto v = Scene.Registry.view<ECS::TransformComponent, ECS::MovementComponent>();
    v.each([&](auto& transform, auto& movement) {
        movement.Velocity += movement.Acceleration;
        transform.Transform.Position += movement.Velocity * Scene.DeltaTime.count();
    });

    auto v2 = Scene.Registry.view<ECS::CameraComponent, ECS::MovementComponent>();
    v2.each([&](auto& camera, auto& movement) {
        movement.Velocity += movement.Acceleration;
        camera.Camera.Transform.Position += movement.Velocity * Scene.DeltaTime.count();
    });
}

}
