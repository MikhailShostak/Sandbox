#pragma once

namespace Debug
{

template<typename Lambda>
inline void ExecuteOnce(Lambda &&lambda)
{
    static bool executed = false;
    if (!executed)
    {
        executed = true;
        lambda();
    }
}

template<typename Type, typename ...Types>
void CheckTypesInternally()
{
    static_assert(sizeof(Type) < 0);
}

template<typename ...Types>
void CheckTypes()
{
    CheckTypesInternally<Types...>();
}

}
