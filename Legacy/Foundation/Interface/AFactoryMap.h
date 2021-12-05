#pragma once

#include "AMemory.h"
#include "AMeta.h"
#include "AMemory.h"

template<typename Key, typename Type, typename ...Arguments>
class AFactoryMap
{
    static_assert(std::has_virtual_destructor<Type>::value, "The Type has a non-virtual destructor");
public:
    using Constructor = Meta::ConstructorPointer<Type, Arguments...>;
    using SizeType = typename Map<Key, Constructor>::size_type;
private:
    Map<Key, Constructor> data;
public:

    static const AFactoryMap<Key, Type, Arguments...> &EmptyFactoryMap()
    {
        static AFactoryMap<Key, Type, Arguments...> emptyFactoryMap;
        return emptyFactoryMap;
    }

    AFactoryMap() {}

    SizeType size() const { return data.size(); }
    bool isEmpty() const { return data.isEmpty(); }

    template<typename ExtendedType>
    void insert(const Key &key) { data.insert({ key, &CreateAs<ExtendedType, Type, Arguments...> }); }

    Array<Key> keys() const
    {
        return data.keys();
    }

    bool hasKey(const Key &key) const { return data.find(key) != data.end(); }

    void clear() { data.clear(); }

    Type *create(const Key &key, Arguments &&...arguments) const
    {
        //AAssert(hasKey(key), "The factory map has no the key%s", (AMeta::hasObjectDescription<Key>::value ? ": " + AMeta::getObjectDescription(key) : "").toUtf8().data());
        return data.at(key)(std::forward<Arguments>(arguments)...);
    }

    SharedReference<Type> createShared(const Key &key, Arguments &&...arguments) const
    {
        //AAssert(hasKey(key), "The factory map has no the key%s", (AMeta::hasObjectDescription<Key>::value ? ": " + AMeta::getObjectDescription(key) : "").toUtf8().data());
        return SharedReference<Type>(data.at(key)(std::forward<Arguments>(arguments)...));
    }

    explicit operator bool () const { return data.size() > 0; }

};
