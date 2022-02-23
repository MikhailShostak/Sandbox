
void CaptureMouse(bool Capture);

bool/*Handled*/ FreeCameraInputHandler::OnTouchDown(EScene& Scene, const TouchInput& Input, bool Intersected)
{
    LastPosition = Input.Position;
    Captured = Intersected;
    if (Captured)
    {
        CaptureMouse(true);
    }
    return Intersected;
}

bool/*Handled*/ FreeCameraInputHandler::OnTouchMove(EScene& Scene, const TouchInput& Input, bool Intersected)
{
    if (!CurrentCamera || !Captured)
    {
        return false;
    }

    auto delta = Input.Position - LastPosition;
    LastPosition = Input.Position;

    Rotation.y += delta.x * Sensetivity.x;
    Rotation.x += delta.y * Sensetivity.y;

    Rotation.y = std::fmod(Rotation.y, 360);
    Rotation.x = std::clamp<float>(Rotation.x, -90, 90);

    auto [cameraComponent, pawn] = CurrentCamera.GetComponents<ECS::CameraComponent, ECS::PawnComponent>();
    cameraComponent.Camera.Transform.Rotation = Rotation;
    /*    hlslpp::axisangle(Float3{ 1, 0, 0 }, 90 * (3.14 / 180)) * // hack
        hlslpp::axisangle({ 0, 1, 0 }, (float)Rotation.y * (3.14 / 180)) *
        hlslpp::axisangle({ 1, 0, 0 }, (float)Rotation.x * (3.14 / 180));*/

    pawn.Rotation = hlslpp::axisangle({ 0, 1, 0 }, (float)Rotation.y * (3.14 / 180));

    return false;
}

bool/*Handled*/ FreeCameraInputHandler::OnTouchUp(EScene& Scene, const TouchInput& Input, bool Intersected)
{
    if (Captured)
    {
        CaptureMouse(false);
    }
    Captured = false;
    return false;
}

bool/*Handled*/ FreeCameraInputHandler::OnKeyDown(EScene& Scene, const KeyboardInput& Input)
{
    auto &pawn = CurrentCamera.GetComponent<ECS::PawnComponent>();
    switch (Input.Key)
    {
    case 87: //W
        pawn.InputVector += Float3(0, 0, 1);
        return true;
    case 65: //A
        pawn.InputVector += -Float3(1, 0, 0);
        return true;
    case 83: //S
        pawn.InputVector += -Float3(0, 0, 1);
        return true;
    case 68: //D
        pawn.InputVector += Float3(1, 0, 0);
        return true;
    case 69: //E
        pawn.InputVector += Float3(0, 1, 0);
        return true;
    case 81: //Q
        pawn.InputVector += -Float3(0, 1, 0);
        return true;
    }

    return false;
}

bool/*Handled*/ FreeCameraInputHandler::OnKeyUp(EScene& Scene, const KeyboardInput& Input)
{
    auto &pawn = CurrentCamera.GetComponent<ECS::PawnComponent>();
    switch (Input.Key)
    {
    case 87: //W
        pawn.InputVector -= Float3(0, 0, 1);
        return true;
    case 65: //A
        pawn.InputVector -= -Float3(1, 0, 0);
        return true;
    case 83: //S
        pawn.InputVector -= -Float3(0, 0, 1);
        return true;
    case 68: //D
        pawn.InputVector -= Float3(1, 0, 0);
        return true;
    case 69: //E
        pawn.InputVector -= Float3(0, 1, 0);
        return true;
    case 81: //Q
        pawn.InputVector -= -Float3(0, 1, 0);
        return true;
    }

    return false;
}
