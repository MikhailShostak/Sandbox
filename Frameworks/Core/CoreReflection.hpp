namespace
{

struct CoreReflectionType
{
    CoreReflectionType()
    {
        Reflection::Add<Core::Application>("Core.Application");
        Reflection::Add<Core::ApplicationComponent>("Core.ApplicationComponent");
    }
} inline CoreReflection;

}
