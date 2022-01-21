namespace
{

struct NativeApplicationReflectionType
{
    NativeApplicationReflectionType()
    {
        Reflection::Add<WindowComponent>("WindowComponent");
    }
} inline NativeApplicationReflection;

}
