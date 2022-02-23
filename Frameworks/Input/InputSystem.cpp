namespace ECS
{
bool/*Accept*/ InputSystem::OnTouchDown(const TouchInput& Input) { return false; }
bool/*Accept*/ InputSystem::OnTouchMove(const TouchInput& Input) { return false; }
bool/*Accept*/ InputSystem::OnTouchUp(const TouchInput& Input) { return false; }
bool/*Accept*/ InputSystem::OnTouch(const TouchInput& Input) { return false; }
bool/*Accept*/ InputSystem::OnWheelMove(const WheelInput& Input) { return false; }
bool/*Accept*/ InputSystem::OnKeyDown(const KeyboardInput& Input) { return false; }
bool/*Accept*/ InputSystem::OnKeyUp(const KeyboardInput& Input) { return false; }
}
