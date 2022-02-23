#include <ClassGen.hpp>

namespace
{

struct SandboxReflectionType
{
    SandboxReflectionType()
    {
        Reflection::Add<UI::BaseView>("UI.BaseView");
        Reflection::Add<UI::DemoView>("UI.DemoView");
        Reflection::Add<UI::ViewWindowComponent>("UI.ViewWindowComponent");

        Reflection::Add<SandboxMainSystem>("SandboxMainSystem");
    }
} inline SandboxReflection;

}
