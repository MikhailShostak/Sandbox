#pragma once

#include "AMemory.h"

class AApplicationContext
{
public:

    class Data
    {
        static SharedReference<Stack<AApplicationContext *>> &getContextsData()
        {
            static SharedReference<Stack<AApplicationContext *>> contexts;
            return contexts;
        }

    public:

        static const SharedReference<Stack<AApplicationContext *>> &getSharedContexts()
        {
            auto &data = getContextsData();
            if(!data)
            {
                data = std::make_shared<Stack<AApplicationContext *>>();
            }
            return data;
        }

        static Stack<AApplicationContext *> &getContexts()
        {
            return *getSharedContexts();
        }

        static void setContexts(const SharedReference<Stack<AApplicationContext *>> &contexts)
        {
            auto &data = getContextsData();
            data = contexts;
        }
    };

    static AApplicationContext &getContext()
    {
        AAssert(Data::getContexts().size() > 0, "Context unavailable");
        return *Data::getContexts().back();
    }

    template<typename Type>
    static Type &getContextAs()
    {
        AAssert(Data::getContexts().size() > 0, "Context unavailable");
        return static_cast<Type &>(*Data::getContexts().back());
    }

    static void pushContext(AApplicationContext *context)
    {
        Data::getContexts().push_back(context);
    }

    static void popContext()
    {
        Data::getContexts().pop_back();
    }
};
