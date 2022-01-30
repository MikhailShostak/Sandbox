#include "Components/EditorWindow.hpp"

namespace
{

struct EditorReflectionType
{
    EditorReflectionType()
    {
        Reflection::Add<EditorWindow>("EditorWindow");
    }
} inline EditorReflection;

}
