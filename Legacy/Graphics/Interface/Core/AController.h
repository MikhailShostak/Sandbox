#pragma once

#include <AMemory.h>
#include <String.h>

template<typename Type>
class AController
{

    static Map<String, AController<Type>*> &controllers()
    {
        static Map<String, AController<Type>*> map;
        return map;
    }

public:

    template<typename ExtendedType>
    static void append(const String &name)
    {
        if(controllers().hasKey(name))
        {
            return;
        }
        controllers().insert(name, new ExtendedType());
    }

    static void remove(const String &name)
    {
        typename Map<String, AController<Type>*>::Iterator it = controllers().find(name);
        if(it == controllers().end())
        {
            return;
        }
        delete it->second;
        controllers().erase(it);
    }

    static Type *allocate(const String &name)
    {
        typename Map<String, AController<Type>*>::Iterator it = controllers().find(name);
        if(it == controllers().end())
        {
            return nullptr;
        }
        Type *value = new Type();
        it->second->setup(value);
        return value;
    }

    static ::SharedReference<Type> allocateShared(const String &name) { return allocate(name); }

    static void setup(const String &name, Type *value)
    {
        typename Map<String, AController<Type>*>::Iterator it = controllers().find(name);
        if(it != controllers().end())
        {
            it->second->setup(value);
        }
    }

protected:

    AController() {}
    virtual ~AController() {}

    virtual void setup(Type *value) = 0;

};
