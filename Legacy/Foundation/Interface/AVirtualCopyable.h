#pragma once

class AVirtualCopyableData
{
public:

    virtual ~AVirtualCopyableData() {}

    virtual AVirtualCopyableData *copy() const = 0;

    template<typename Type>
    Type *copyAs() const
    {
        return static_cast<Type *>(copy());
    }

    template<typename Type>
    Type *dynamicCopy() const
    {
        if(typeid(Type) != typeid(*this))
        {
            return nullptr;
        }

        return static_cast<Type *>(copy());
    }

};
