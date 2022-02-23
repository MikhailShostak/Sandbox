#pragma once

namespace ECS
{

void PawnSystem::OnUpdate(EScene& Scene)
{
    auto v = Scene.Registry.view<ECS::PawnComponent, ECS::MovementComponent>();
    v.each([](auto& pawn, auto& movement) {
        if (pawn.Mobility > 0.0f)
        {
            auto desiredVelocity = pawn.InputVector * pawn.Speed;
            if (pawn.RelativeInput)
            {
                desiredVelocity = pawn.Rotation * desiredVelocity;
            }
            movement.Velocity = hlslpp::lerp(movement.Velocity, desiredVelocity, pawn.Mobility);
        }
    });
}

}
