#pragma once

#include "AMemory.h"
#include "AMemory.h"

template<typename Type, typename ...Arguments>
class AFactoryList final
{
    static_assert(std::has_virtual_destructor<Type>::value, "The Type has a non-virtual destructor");
public:
    using Constructor = Memory::Constructor<Type, Arguments...>;
    using SizeType = typename Array<Constructor>::SizeType;
private:
    Array<Constructor> data;
public:
    static const AFactoryList<Type, Arguments...> &EmptyFactoryList()
    {
        static AFactoryList<Type, Arguments...> emptyFactoryList;
        return emptyFactoryList;
    }

    AFactoryList() {}

    SizeType size() const { return data.size(); }
    bool isEmpty() const { return data.empty(); }

    template<typename ExtendedType>
    void append() { data.push_back(&CreateAs<ExtendedType, Type, Arguments...>); }

    template<typename ...ExtendedTypes>
    void set() { data = {&CreateAs<ExtendedTypes, Type, Arguments...>...}; }

    void clear() { return data.clear(); }

    Type *create(SizeType index, Arguments &&...arguments) const
    {
        AAssert(index < data.size(), "The index %lu is out of range, the size of the factory list is %lu", index, data.size());
        return data.at(index)(std::forward<Arguments>(arguments)...);
    }

    SharedReference<Type> *createShared(SizeType index, Arguments &&...arguments) const
    {
        AAssert(index < data.size(), "The index %lu is out of range, the size of the factory list is %lu", index, data.size());
        return SharedReference<Type>(data.at(index)(std::forward<Arguments>(arguments)...));
    }

};
