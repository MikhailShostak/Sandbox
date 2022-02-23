namespace
{

struct SceneWindowReflectionType
{
    SceneWindowReflectionType()
    {
        Reflection::Add<SceneWindowComponent>("SceneWindowComponent");
    }
} inline SceneWindowReflection;

}
