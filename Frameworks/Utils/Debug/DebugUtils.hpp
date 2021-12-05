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

}
