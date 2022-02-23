namespace
{

struct InputReflectionType
{
    InputReflectionType()
    {
        Reflection::Add<ECS::InputSystem>("ECS.InputSystem");
        Reflection::Add<ECS::SceneSystem>("ECS.SceneSystem");
        Reflection::Add<ECS::InputComponent>("ECS.InputComponent");
        Reflection::Add<ECS::UIInputSystem>("ECS.UIInputSystem");
        Reflection::Add<InputHandler>("InputHandler");
        Reflection::Add<FreeCameraInputHandler>("FreeCameraInputHandler");
    }
} inline InputReflection;

}
