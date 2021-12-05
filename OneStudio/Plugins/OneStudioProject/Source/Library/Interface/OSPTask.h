#pragma once

#include <Foundation>

namespace OneStudioProject
{
    class Task
    {
    public:

        virtual ~Task() {}

        virtual String getPackage() const { return "com.Example.Task"; }
        virtual String getVersion() const { return "1.0.0"; }
        String getName() const { return getPackage().split('.').last(); }

    };
}