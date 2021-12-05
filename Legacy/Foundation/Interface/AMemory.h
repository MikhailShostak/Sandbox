#pragma once

#include <memory>

#include "AAssert.h"

#include <type_traits>

#define DECLARE_NESTED_TYPE_CHECKS(get_name, check_name, typedef_name)\
    template<typename Type> constexpr static std::false_type __## declaration_name ##_impl__(...);\
    template<typename Type> constexpr static typename Type::typedef_name __## declaration_name ##_impl__(Type*);\
    template<typename Type> struct get_name { using type = decltype(__## declaration_name ##_impl__<Type>(0)); };\
    template<typename Type> struct check_name { constexpr static bool value = !std::is_same<typename get_name<Type>::type, std::false_type>::value; }

DECLARE_NESTED_TYPE_CHECKS(GetBaseType, HasBaseType, Super);

using std::size_t;

namespace Legacy
{

template<typename Type>
class SharedReference;

template<typename Type>
class WeakReference;

struct SharedReferenceCounter
{
    using SizeType = std::size_t;
    SizeType share = 1;
    SizeType weak = 0;
};

template<typename Type>
class SharedReference final
{

    template<typename PointerType>
    friend class SharedReference;
    template<typename PointerType>
    friend class WeakReference;

    SharedReferenceCounter *counter = nullptr;
    Type *dataPointer = nullptr;

public:

    using PointerType = Type;
    using SizeType = typename SharedReferenceCounter::SizeType;

    static const SharedReference<Type> &EmptySharedPointer()
    {
        static SharedReference<Type> emptySharedPointer;
        return emptySharedPointer;
    }

    SharedReference();
    SharedReference(std::nullptr_t);
    SharedReference(const SharedReference<Type> &pointer);
    SharedReference(SharedReference<Type> &&pointer);

    template<typename PointerType>
    SharedReference(PointerType *pointer);
    template<typename PointerType>
    SharedReference(const SharedReference<PointerType> &pointer);
    template<typename PointerType>
    SharedReference(SharedReference<PointerType> &&pointer);
    template<typename PointerType>
    SharedReference(const WeakReference<PointerType> &pointer);
    template<typename PointerType>
    SharedReference(WeakReference<PointerType> &&pointer);

    SharedReference<Type> &operator =(const SharedReference<Type> &pointer);
    SharedReference<Type> &operator =(SharedReference<Type> &&pointer);

    template<typename PointerType>
    SharedReference<Type> &operator =(PointerType *pointer);
    template<typename PointerType>
    SharedReference<Type> &operator =(const SharedReference<PointerType> &pointer);
    template<typename PointerType>
    SharedReference<Type> &operator =(SharedReference<PointerType> &&pointer);
    template<typename PointerType>
    SharedReference<Type> &operator =(const WeakReference<PointerType> &pointer);
    template<typename PointerType>
    SharedReference<Type> &operator =(WeakReference<PointerType> &&pointer);

    ~SharedReference() { free(); }

    bool isNull() const { return dataPointer == nullptr; }
    bool isValid() const { return dataPointer != nullptr; }
    bool isUnique() const { return (countSharedPointers() + countWeakPointers()) < 2; }

    SizeType countSharedPointers() const { if (counter) return counter->share; return 0; }
    SizeType countWeakPointers() const { if (counter) return counter->weak; return 0; }

    WeakReference<Type> weak() const;

    Type &operator *() const
    {
        AAssert(isValid(), "Bad access, pointer is null");
        return (*dataPointer);
    }

    Type *operator ->() const
    {
        AAssert(isValid(), "Bad access, pointer is null");
        return dataPointer;
    }

    Type *data() const { return dataPointer; }
    Type *raw() const { return dataPointer; }

    void reset()
    {
        free();
        counter = nullptr;
        dataPointer = nullptr;
    }

    explicit operator bool() const { return isValid(); }

    template<typename PointerType>
    SharedReference<PointerType> cast() const
    {
        if (!dataPointer)
        {
            return nullptr;
        }
        SharedReference<PointerType> pointer;
        pointer.dataPointer = dynamic_cast<PointerType *>(dataPointer);
        if (pointer.dataPointer)
        {
            pointer.counter = counter;
            ++counter->share;
        }
        return pointer;
    }

    template<typename PointerType>
    SharedReference<PointerType> as() const
    {
        AAssert(isValid(), "Pointer is null");
        SharedReference<PointerType> pointer;
        pointer.dataPointer = static_cast<PointerType *>(const_cast<Type *>(dataPointer));
        pointer.counter = counter;
        ++(counter->share);
        return pointer;
    }

    bool operator ==(const Type *pointer) const;
    bool operator ==(const SharedReference<Type> &pointer) const;
    bool operator ==(const WeakReference<Type> &pointer) const;

    bool operator !=(const Type *pointer) const;
    bool operator !=(const SharedReference<Type> &pointer) const;
    bool operator !=(const WeakReference<Type> &pointer) const;

private:

    void free();

};

template<typename Type>
class WeakReference final
{

    template<typename PointerType>
    friend class SharedReference;
    template<typename PointerType>
    friend class WeakReference;

    SharedReferenceCounter *counter = nullptr;
    Type *dataPointer = nullptr;
    bool locked = false;

public:

    using SizeType = typename SharedReferenceCounter::SizeType;

    static const WeakReference<Type> &EmptyWeakPointer()
    {
        static WeakReference<Type> emptyWeakPointer;
        return emptyWeakPointer;
    }

    WeakReference();
    WeakReference(std::nullptr_t);
    WeakReference(const WeakReference<Type> &pointer);
    WeakReference(WeakReference<Type> &&pointer);

    template<typename PointerType>
    WeakReference(const WeakReference<PointerType> &pointer);
    template<typename PointerType>
    WeakReference(WeakReference<PointerType> &&pointer);
    template<typename PointerType>
    WeakReference(const SharedReference<PointerType> &pointer);
    template<typename PointerType>
    WeakReference(SharedReference<PointerType> &&pointer);

    WeakReference<Type> &operator =(const WeakReference<Type> &pointer);
    WeakReference<Type> &operator =(WeakReference<Type> &&pointer);

    template<typename PointerType>
    WeakReference<Type> &operator =(const WeakReference<PointerType> &pointer);
    template<typename PointerType>
    WeakReference<Type> &operator =(WeakReference<PointerType> &&pointer);
    template<typename PointerType>
    WeakReference<Type> &operator =(const SharedReference<PointerType> &pointer);
    template<typename PointerType>
    WeakReference<Type> &operator =(SharedReference<PointerType> &&pointer);

    ~WeakReference() { free(); }

    bool isNull() const { return !(counter && counter->share > 0); }
    bool isValid() const { return counter && counter->share > 0; }

    bool isLocked() const { return locked; }
    void lock();
    void unlock();

    SizeType countSharedPointers() const { if (counter) return counter->share; return 0; }
    SizeType countWeakPointers() const { if (counter) return counter->weak; return 0; }

    SharedReference<Type> shared() const;

    Type &operator *() const { AAssert(isValid(), "Bad access, pointer is null"); return (*dataPointer); }
    Type *operator ->() const { AAssert(isValid(), "Bad access, pointer is null"); return dataPointer; }

    Type *data() const { if (isNull()) return nullptr; return dataPointer; }

    void reset() { free(); counter = nullptr; }

    explicit operator bool() const { return isValid(); }

    bool operator ==(const Type *pointer) const;
    bool operator ==(const SharedReference<Type> &pointer) const;
    bool operator ==(const WeakReference<Type> &pointer) const;

    bool operator !=(const Type *pointer) const;
    bool operator !=(const SharedReference<Type> &pointer) const;
    bool operator !=(const WeakReference<Type> &pointer) const;

private:

    void free();

};

template<typename Type>
class UniqueReference
{

    Type *dataPointer = nullptr;

public:

    UniqueReference();

    UniqueReference(const UniqueReference<Type> &pointer) = delete;
    UniqueReference(UniqueReference<Type> &&pointer);

    explicit UniqueReference(Type *pointer);

    ~UniqueReference();

    bool isValid() const;
    bool isNull() const;

    Type *getData() const;

    Type &operator *() const;
    Type *operator ->() const;

    explicit operator bool() const;

    UniqueReference &operator =(const UniqueReference<Type> &pointer) = delete;
    UniqueReference &operator =(UniqueReference<Type> &&pointer);

    bool operator ==(Type *pointer) const;
    bool operator !=(Type *pointer) const;

};

}









namespace Memory
{

template<typename Type>
inline void *AllocateAsVoid()
{
    return Allocate<Type>();
}

template<typename Type>
inline Type *AllocateArray(size_t size)
{
    return new Type[size];
}

template<typename Type, typename ...Items>
inline Type *CreateArray(size_t size, Items &&...items)
{
    return new Type[size]{ std::forward<Items>(items)... };
}

template<typename Type>
inline void DestroyArray(Type *array)
{
    delete[] array;
}

template<typename Type>
inline void Copy(const Type &sourceObject, Type &destinationObject)
{
    AAssert(false, "Deep copy isn't implemented for the Type");
}

//template<typename Type, typename ...Arguments>
//using Constructor = Type * (*)(Arguments &&...arguments);

template<typename Type>
using Destructor = void(*)(Type *);

template<typename ...Arguments>
using AbstractConstructor = Constructor<void, Arguments...>;
using AbstractDestructor = Destructor<void>;
}

// template<typename DerivedType, typename BaseType = DerivedType>
// struct Constructor
// {
//     template<typename ...Arguments>
//     inline static DerivedType *Create(Arguments &&...arguments)
//     {
//         return Constructor<DerivedType, typename GetBaseType<BaseType>::type>::Create(std::forward<Arguments>(arguments)...);
//     }
// };
// 
// template<typename Type>
// struct Constructor<Type, std::false_type>
// {
//     template<typename ...Arguments>
//     inline static Type *Create(Arguments &&...arguments)
//     {
//         Type *object = Memory::Create<Type>(std::forward<Arguments>(arguments)...);
// //         #if ADebugBuild
// //             AMemoryObjectInfo objectInfo;
// //             objectInfo.pointer = object;
// //             objectInfo.name = typeid(Type).name();
// //             objectInfo.size = sizeof(Type);
// //             objectInfo.vtable = std::is_polymorphic<Type>::value ? reinterpret_cast<void **>(object)[0] : nullptr;
// //             AMemoryManager::getInstance().addObject(objectInfo);
// //         #endif
//         return object;
//     }
// };

/*template<typename Type, typename ...Arguments>
inline Type *Create(Arguments &&...arguments)
{
    return Constructor<Type>::Create(std::forward<Arguments>(arguments)...);
}

template<typename Type, typename ReturnType, typename ...Arguments>
inline ReturnType *CreateAs(Arguments &&...arguments)
{
    return Create<Type>(std::forward<Arguments>(arguments)...);
}*/

// template<typename Type, typename ...Arguments>
// inline Type *createNew(Arguments &&...arguments) //TODO: deprecated
// {
//     return Create<Type>(std::forward<Arguments>(arguments)...);
// }

template<typename ReturnType, typename Type>
inline ReturnType raw_cast(Type &&value)
{
    union {
        Type input;
        ReturnType output;
    };
    input = std::forward(value);
    return output;
}

















namespace Legacy
{

template<typename Type>
inline SharedReference<Type>::SharedReference() {}

template<typename Type>
inline SharedReference<Type>::SharedReference(std::nullptr_t) {}

template<typename Type>
inline SharedReference<Type>::SharedReference(const SharedReference<Type> &pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    if (counter) ++counter->share;
}

template<typename Type>
inline SharedReference<Type>::SharedReference(SharedReference<Type> &&pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    pointer.counter = nullptr; pointer.dataPointer = nullptr;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type>::SharedReference(OtherPointerType *pointer) :
    counter(Create<SharedReferenceCounter>()),
    dataPointer(pointer)
{}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type>::SharedReference(const SharedReference<OtherPointerType> &pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    if (counter) ++counter->share;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type>::SharedReference(SharedReference<OtherPointerType> &&pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    pointer.counter = nullptr; pointer.dataPointer = nullptr;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type>::SharedReference(const WeakReference<OtherPointerType> &pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    if (counter) ++counter->share;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type>::SharedReference(WeakReference<OtherPointerType> &&pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    pointer.counter == nullptr; pointer.dataPointer == nullptr; if (!pointer.locked) ++counter->share; pointer.locked = false;
}

template<typename Type>
inline SharedReference<Type> &SharedReference<Type>::operator =(const SharedReference<Type> &pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        ++counter->share;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
inline SharedReference<Type> &SharedReference<Type>::operator =(SharedReference<Type> &&pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        pointer.counter = nullptr;
        pointer.dataPointer = nullptr;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type> &SharedReference<Type>::operator =(OtherPointerType *pointer)
{
    if (dataPointer == pointer)
        return *this;
    if (pointer)
    {
        free();
        counter = Create<SharedReferenceCounter>();
        dataPointer = pointer;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type> &SharedReference<Type>::operator =(const SharedReference<OtherPointerType> &pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        ++counter->share;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type> &SharedReference<Type>::operator =(SharedReference<OtherPointerType> &&pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        pointer.counter = nullptr;
        pointer.dataPointer = nullptr;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type> &SharedReference<Type>::operator =(const WeakReference<OtherPointerType> &pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter && pointer.counter->share > 0)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        ++counter->share;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename OtherPointerType>
inline SharedReference<Type> &SharedReference<Type>::operator =(WeakReference<OtherPointerType> &&pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter && pointer.counter->share > 0)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        pointer.counter == nullptr;
        pointer.dataPointer == nullptr;
        if (!pointer.locked)
            ++counter->share;
        pointer.locked = false;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
inline WeakReference<Type> SharedReference<Type>::weak() const
{
    return *this;
}

template<typename Type>
inline bool SharedReference<Type>::operator ==(const Type *pointer) const
{
    return dataPointer == pointer;
}

template<typename Type>
inline bool SharedReference<Type>::operator ==(const SharedReference<Type> &pointer) const
{
    return dataPointer == pointer.dataPointer;
}

template<typename Type>
inline bool SharedReference<Type>::operator ==(const WeakReference<Type> &pointer) const
{
    return dataPointer == pointer.dataPointer;
}


template<typename Type>
inline bool SharedReference<Type>::operator !=(const Type *pointer) const
{
    return dataPointer != pointer;
}

template<typename Type>
inline bool SharedReference<Type>::operator !=(const SharedReference<Type> &pointer) const
{
    return dataPointer != pointer.dataPointer;
}

template<typename Type>
inline bool SharedReference<Type>::operator !=(const WeakReference<Type> &pointer) const
{
    return dataPointer != pointer.dataPointer;
}

template<typename Type>
inline void SharedReference<Type>::free()
{
    if (counter)
    {
        --counter->share;
        if (counter->share == 0)
        {
            if (counter->weak == 0)
                delete counter;
            delete dataPointer;
        }
    }
}

template<typename Type>
inline WeakReference<Type>::WeakReference() {}

template<typename Type>
inline WeakReference<Type>::WeakReference(std::nullptr_t) {}

template<typename Type>
inline WeakReference<Type>::WeakReference(const WeakReference<Type> &pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    if (counter) ++counter->weak;
}

template<typename Type>
inline WeakReference<Type>::WeakReference(WeakReference<Type> &&pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    pointer.counter = nullptr; pointer.dataPointer = nullptr;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type>::WeakReference(const WeakReference<PointerType> &pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    if (counter) ++counter->weak;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type>::WeakReference(WeakReference<PointerType> &&pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    pointer.counter = nullptr; pointer.dataPointer = nullptr;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type>::WeakReference(const SharedReference<PointerType> &pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer)
{
    if (counter) ++counter->weak;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type>::WeakReference(SharedReference<PointerType> &&pointer) : counter(pointer.counter), dataPointer(pointer.dataPointer), locked(true)
{
    pointer.counter = nullptr; pointer.dataPointer = nullptr; ++counter->weak;
}


template<typename Type>
inline WeakReference<Type> &WeakReference<Type>::operator =(const WeakReference<Type> &pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        ++counter->weak;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
inline WeakReference<Type> &WeakReference<Type>::operator =(WeakReference<Type> &&pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        pointer.counter = nullptr;
        pointer.dataPointer = nullptr;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type> &WeakReference<Type>::operator =(const WeakReference<PointerType> &pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        ++counter->weak;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type> &WeakReference<Type>::operator =(WeakReference<PointerType> &&pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        pointer.counter = nullptr;
        pointer.dataPointer = nullptr;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type> &WeakReference<Type>::operator =(const SharedReference<PointerType> &pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        ++counter->weak;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
template<typename PointerType>
inline WeakReference<Type> &WeakReference<Type>::operator =(SharedReference<PointerType> &&pointer)
{
    if (counter == pointer.counter)
        return *this;
    if (pointer.counter)
    {
        free();
        locked = true;
        counter = pointer.counter;
        dataPointer = pointer.dataPointer;
        pointer.counter = nullptr;
        pointer.dataPointer = nullptr;
    }
    else
    {
        reset();
    }
    return *this;
}

template<typename Type>
inline void WeakReference<Type>::lock()
{
    if (!locked && counter && counter->share > 0)
    {
        locked = true;
        ++counter->share;
    }
}

template<typename Type>
inline void WeakReference<Type>::unlock()
{
    if (locked)
    {
        locked = false;
        --counter->share;
        if (counter->share == 0)
        {
            delete dataPointer;
            if (counter->weak == 1)
                delete counter;
        }
    }
}

template<typename Type>
inline SharedReference<Type> WeakReference<Type>::shared() const
{
    return *this;
}

template<typename Type>
inline bool WeakReference<Type>::operator ==(const Type *pointer) const
{
    return dataPointer == pointer;
}


template<typename Type>
inline bool WeakReference<Type>::operator ==(const SharedReference<Type> &pointer) const
{
    return dataPointer == pointer.dataPointer;
}

template<typename Type>
inline bool WeakReference<Type>::operator ==(const WeakReference<Type> &pointer) const
{
    return dataPointer == pointer.dataPointer;
}

template<typename Type>
inline bool WeakReference<Type>::operator !=(const Type *pointer) const
{
    return dataPointer != pointer;
}

template<typename Type>
inline bool WeakReference<Type>::operator !=(const SharedReference<Type> &pointer) const
{
    return dataPointer != pointer.dataPointer;
}

template<typename Type>
inline bool WeakReference<Type>::operator !=(const WeakReference<Type> &pointer) const
{
    return dataPointer != pointer.dataPointer;
}

template<typename Type>
inline void WeakReference<Type>::free()
{
    if (counter)
    {
        if (locked && counter->share == 1)
        {
            if (locked)
                delete dataPointer;
            if (counter->weak == 1)
                delete counter;
        }
        else
            --counter->weak;
    }
}

template<typename Type>
inline UniqueReference<Type>::UniqueReference() :
    dataPointer(nullptr)
{

}

template<typename Type>
inline UniqueReference<Type>::UniqueReference(UniqueReference<Type> &&pointer) :
    dataPointer(pointer.dataPointer)
{
    pointer.dataPointer = nullptr;
}

template<typename Type>
inline UniqueReference<Type> &UniqueReference<Type>::operator =(UniqueReference<Type> &&pointer)
{
    dataPointer = pointer.dataPointer;
    pointer.dataPointer = nullptr;
    return *this;
}

template<typename Type>
inline UniqueReference<Type>::UniqueReference(Type *pointer) :
    dataPointer(pointer)
{

}

template<typename Type>
inline UniqueReference<Type>::~UniqueReference()
{
    if (dataPointer)
    {
        delete dataPointer;
    }
}

template<typename Type>
inline bool UniqueReference<Type>::isValid() const
{
    return dataPointer;
}

template<typename Type>
inline bool UniqueReference<Type>::isNull() const
{
    return !dataPointer;
}

template<typename Type>
inline Type &UniqueReference<Type>::operator *() const
{
    AAssert(isValid(), "Bad access, pointer is null");
    return *dataPointer;
}

template<typename Type>
inline Type *UniqueReference<Type>::operator ->() const
{
    AAssert(isValid(), "Bad access, pointer is null");
    return dataPointer;
}

template<typename Type>
UniqueReference<Type>::operator bool() const
{
    return dataPointer;
}

}
