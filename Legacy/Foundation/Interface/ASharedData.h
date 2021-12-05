#pragma once

#include "AVirtualCopyable.h"

template<typename Type>
class ASharedData
{
    template<typename DetachType, bool isVirtualCopyable>
    struct Detach;

    template<typename DetachType>
    struct Detach<DetachType, false>
    {
        static void detach(SharedReference<DetachType> &data)
        {
            data = Create<DetachType>(*data);
        }
    };

    template<typename DetachType>
    struct Detach<DetachType, true>
    {
        static void detach(SharedReference<DetachType> &data)
        {
            data = data->template copyAs<DetachType>();
        }
    };


protected:

    SharedReference<Type> data;

public:

    ASharedData():data(new Type())
    {

    }

    ASharedData(Type *data):data(data)
    {

    }

    bool isDetached() const
    {
        return data.isUnique();
    }

    void detach()
    {
        if(isDetached())
        {
            return;
        }

        Detach<Type, std::is_base_of<Type, AVirtualCopyableData>::value>::detach(data);
    }

    Type &operator *()
    {
        detach();
        return *data;
    }

    Type &operator *() const
    {
        return *data;
    }

    Type *operator ->()
    {
        detach();
        return data.data();
    }

    Type *operator ->() const
    {
        return data.data();
    }

};
