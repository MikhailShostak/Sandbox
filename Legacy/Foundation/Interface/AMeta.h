#pragma once

#include <type_traits>
#include <tuple>

#include "AType.h"

inline Array<void(*)()> &GetGlobalCalls()
{
    static Array<void(*)()> calls;
    return calls;
}

inline void ExecuteGlobalCalls()
{
    for (void(*staticFunction)() : GetGlobalCalls())
    {
        staticFunction();
    }
}

#define AStaticRun(identifier) \
struct __AStaticRun ## identifier ## __ \
{\
    __AStaticRun ## identifier ## __() { GetGlobalCalls().push_back(&__AStaticRun ## identifier ## __::Implementation); } \
    static void Implementation(); \
}; \
static __AStaticRun ## identifier ## __ __staticRun ## identifier ## __; \
\
inline void __AStaticRun ## identifier ## __::Implementation()

#define LinkStaticRun(identifier) \
    (void *)&__staticRun ## identifier ## __

/*template<typename ...Types>
inline String StringFormat(const char *format, const Types &...values);*/

class AMeta final
{

private:

    using False = uint8_t;
    using True = uint16_t;

    template<typename Type>
    struct isTrue : std::integral_constant<bool, std::is_same<Type, True>::value>
    {};

    template<typename Type>
    struct isFalse : std::integral_constant<bool, std::is_same<Type, False>::value>
    {};

    template <typename ObjectType>
    static False checkCallable(...);

    template <typename ObjectType>
    static True checkCallable(decltype(&ObjectType::operator()));

    template <typename ObjectType>
    static False checkConstantCallable(void (ObjectType::*pointer)());

    template <typename ObjectType>
    static True checkConstantCallable(void (ObjectType::*pointer)() const);

    template <typename ObjectType>
    static False checkObjectDescription(...);

    template <typename ObjectType>
    static True checkObjectDescription(decltype(&ObjectType::getObjectDescription));

    struct ObjectDescriptionDetector
    {
        template <typename ObjectType, String(ObjectType::*pointer)() const = &ObjectType::getObjectDescription>
        struct Helper { using Type = True; };

        constexpr static False checkFunction(...);

        template<typename ObjectType>
        constexpr static typename Helper<ObjectType>::Type checkFunction(ObjectType*);

        template<typename Type>
        struct check
        {
            using type = decltype(checkFunction(static_cast<Type*>(0)));
        };

    };

    template<typename Type>
    struct ObjectDescriptionPrinter;

    template<typename Type, bool hasObjectDescription>
    struct ObjectDescriptionWrapper;

    template<typename Type>
    struct ObjectDescriptionWrapper<Type, false>
    {
        static inline String getObjectDescription(const Type &object);
    };

    template<typename Type>
    struct ObjectDescriptionWrapper<Type, true>
    {
        static inline String getObjectDescription(const Type &object);
    };

public:

    AMeta() = delete;

    struct TypeGroup
    {
        struct Void;
        struct Boolean;
        struct Pointers;
        struct Numbers;
        struct Strings;
        struct Objects;
    #ifdef __OBJC__
        struct ObjectiveCObjects;
    #endif
    };

    template<typename CheckedType>
    struct TypeResolver
    {
        using TypeGroup =
        typename std::conditional<
            std::is_same<typename std::remove_reference<std::remove_const<CheckedType>>::type, bool>::value, TypeGroup::Boolean,
        typename std::conditional<
            std::is_arithmetic<typename std::remove_reference<CheckedType>::type>::value, TypeGroup::Numbers,
        typename std::conditional<
            std::is_same<typename std::remove_reference<typename std::remove_const<CheckedType>::type>::type, std::string>::value ||
            std::is_same<typename std::remove_reference<typename std::remove_const<CheckedType>::type>::type, std::wstring>::value ||
            std::is_same<typename std::remove_reference<typename std::remove_const<CheckedType>::type>::type, std::u16string>::value ||
            std::is_same<typename std::remove_reference<typename std::remove_const<CheckedType>::type>::type, std::u32string>::value, TypeGroup::Strings,
        typename std::conditional<
            std::is_pointer<typename std::remove_reference<CheckedType>::type>::value, TypeGroup::Pointers,
        typename std::conditional<
            std::is_class<typename std::remove_reference<std::remove_const<CheckedType>>::type>::value, TypeGroup::Objects,
            TypeGroup::Void
        >::type>::type>::type>::type>::type;
    };

    template<typename ...Types>
    struct print
    {
        static void types();
    };

    template<typename Type>
    struct print<Type>
    {
        static void types();
    };

    template<typename Type, typename ...Types>
    struct print<Type, Types...>
    {
        static void types();
    };

    template<typename ...Types>
    struct print<std::tuple<Types...>>
    {
        static void types();
    };

    template<std::size_t size, typename ...Types>
    struct appendImplementation;

    template<typename ...Pack>
    struct appendImplementation<0, std::tuple<Pack...>>
    {
        typedef std::tuple<Pack...> type;
    };

    template<typename ...Pack, typename Type, typename ...Types>
    struct appendImplementation<0, std::tuple<Pack...>, Type, Types...>
    {
        typedef std::tuple<Pack...> type;
    };

    template<std::size_t index, typename ...Pack, typename Type, typename ...Types>
    struct appendImplementation<index, std::tuple<Pack...>, Type, Types...>
    {
        typedef typename appendImplementation<index - 1, std::tuple<Pack..., Type>, Types...>::type type;
    };

    template<typename Tuple, typename ...Types>
    struct append;

    template<typename ...Pack, typename ...Types>
    struct append<std::tuple<Pack...>, Types...>
    {
        typedef typename appendImplementation<sizeof...(Types), std::tuple<Pack...>, Types...>::type type;
    };

    template<typename Tuple, typename Types>
    struct appendTuple;

    template<typename Tuple, typename ...Types>
    struct appendTuple<Tuple, std::tuple<Types...>>
    {
        typedef typename append<Tuple, Types...>::type type;
    };

    template<std::size_t size, typename ...Types>
    struct range
    {
        typedef typename appendImplementation<size, std::tuple<>, Types...>::type type;
    };

    template<std::size_t size, typename Tuple>
    struct rangeFromTuple;

    template<std::size_t size, typename ...Types>
    struct rangeFromTuple<size, std::tuple<Types...>>
    {
        typedef typename appendImplementation<size, std::tuple<>, Types...>::type type;
    };

    template<std::size_t size, typename ...Types>
    struct skip
    {
        typedef std::tuple<> type;
    };

    template<typename Type, typename ...Types>
    struct skip<0, Type, Types...>
    {
        typedef std::tuple<Type, Types...> type;
    };

    template<std::size_t size, typename Type, typename ...Types>
    struct skip<size, Type, Types...>
    {
        typedef typename skip<size - 1, Types...>::type type;
    };

    template<std::size_t size, typename Tuple>
    struct skipInTuple;

    template<std::size_t size, typename ...Types>
    struct skipInTuple<size, std::tuple<Types...>>
    {
        typedef typename skip<size, Types...>::type type;
    };

    template <typename FunctionSignature>
    struct isCallableArguments;

    template <typename FunctionReturnType, typename ...FunctionArguments>
    struct isCallableArguments<FunctionReturnType(FunctionArguments...)>
    {
        template<typename ...Types>
        friend struct call;

    private:

        template<std::size_t index, typename ...Arguments>
        struct checkArgumentsRecursive;

        template<std::size_t index, typename Argument>
        struct checkArgumentsRecursive<index, Argument>
        {
            using type = typename std::tuple_element<index, std::tuple<FunctionArguments...>>::type;
            constexpr static bool value = std::is_convertible<Argument, type>::value;
        };

        template<std::size_t index, typename Argument, typename ...OtherArguments>
        struct checkArgumentsRecursive<index, Argument, OtherArguments...>
        {
            constexpr static bool value = checkArgumentsRecursive<index, Argument>::value && checkArgumentsRecursive<index + 1, OtherArguments...>::value;
        };

        template<bool access, typename ...Arguments>
        struct checkArgumentsRecursiveGuard;

        template<typename ...Arguments>
        struct checkArgumentsRecursiveGuard<false, Arguments...> : public std::false_type
        {};

        template<typename ...Arguments>
        struct checkArgumentsRecursiveGuard<true, Arguments...> : public std::integral_constant<bool, checkArgumentsRecursive<0, Arguments...>::value>
        {};

        template<typename ...Arguments>
        struct checkArguments : public std::integral_constant<bool, sizeof...(FunctionArguments) == 0 || checkArgumentsRecursiveGuard<sizeof...(FunctionArguments) == sizeof...(Arguments), Arguments...>::value>
        {};

    public:

        template <typename FunctionSignature>
        struct withArguments;

        template <typename ReturnType>
        struct withArguments<ReturnType()> : public std::integral_constant<bool,
            (std::is_same<ReturnType, void>::value || std::is_convertible<FunctionReturnType, ReturnType>::value) &&
            sizeof...(FunctionArguments) == 0>
        {};

        template <typename ReturnType, typename ...Arguments>
        struct withArguments<ReturnType(Arguments...)> : public std::integral_constant<bool,
            (std::is_same<ReturnType, void>::value || std::is_convertible<FunctionReturnType, ReturnType>::value) &&
            (checkArguments<Arguments...>::value)>
        {};
    };

    template<typename Type>
    struct isCallable : public std::integral_constant<bool, isTrue<decltype(checkCallable<Type>(0))>::value>
    {
        constexpr static bool constant = std::is_const<Type>::value;
    };

    template<typename ReturnType, typename Tuple>
    struct functionFromTuple;

    template<typename ReturnType, typename ...Arguments>
    struct functionFromTuple<ReturnType, std::tuple<Arguments...>>
    {
        typedef ReturnType (*type)(Arguments...);
    };

    template<typename Object, typename ReturnType, typename Tuple>
    struct methodFromTuple;

    template<typename Object, typename ReturnType, typename ...Arguments>
    struct methodFromTuple<Object, ReturnType, std::tuple<Arguments...>>
    {
        typedef ReturnType (Object::*type)(Arguments...);
    };

    template<typename ...Types>
    struct call;

    template<typename ...FunctionArguments>
    struct call<void(FunctionArguments...)>
    {

        template<typename FunctionSignature>
        struct withType;

        template<typename ...Arguments>
        struct withType<void(Arguments...)>
        {
            static void andArguments(void(*functionPointer)(FunctionArguments...), Arguments ...arguments);

            template<typename Object>
            static void andArguments(Object *object, void(Object::*methodPointer)(FunctionArguments...), Arguments ...arguments);
        };
    };

    template<typename FunctionReturnType, typename ...FunctionArguments>
    struct call<FunctionReturnType(FunctionArguments...)>
    {
        template<typename FunctionSignature>
        struct withType;

        template<typename ReturnType, typename ...Arguments>
        struct withType<ReturnType(Arguments ...arguments)>
        {
            constexpr static ReturnType andArguments(FunctionReturnType(*functionPointer)(FunctionArguments...), Arguments ...arguments);

            template<typename Object>
            constexpr static ReturnType andArguments(Object *object, FunctionReturnType(Object::*methodPointer)(FunctionArguments...), Arguments ...arguments);
        };

        template<typename ...Arguments>
        struct withType<void(Arguments ...arguments)>
        {
            static void andArguments(FunctionReturnType(*functionPointer)(FunctionArguments...), Arguments ...arguments);

            template<typename Object>
            static void andArguments(Object *object, FunctionReturnType(Object::*methodPointer)(FunctionArguments...), Arguments ...arguments);
        };
    };

    template<typename Type>
    static const AType &getStaticType();

    template<typename Type>
    static const char *getStaticTypeName();

    template<typename Type>
    static std::size_t getStaticTypeHash();

    template<typename Type>
    static AType getDynamicType(const Type &object);

    template<typename Type>
    static const char *getDynamicTypeName(const Type &object);

    template<typename Type>
    static std::size_t getDynamicTypeHash(const Type &object);

    template<typename Type>
    struct hasObjectDescription : public std::integral_constant<bool, isTrue<decltype(checkObjectDescription<Type>(0))>::value>
    {
        constexpr static bool constant = std::is_const<Type>::value;
    };

    /*template<typename Type>
    struct hasObjectDescription : public std::integral_constant<bool, isTrue<typename ObjectDescriptionDetector::check<Type>::type>::value>
    {};*/

    template<typename Type>
    static String getObjectDescription(const Type &object);

};

#include <sstream>
#include "AMemory.h"
#include "String.h"

//*******************************************************

template<typename Type>
inline String AMeta::ObjectDescriptionWrapper<Type, false>::getObjectDescription(const Type &object) { return fmt::format("{}({})", getStaticType<Type>().getName(), static_cast<const void *>(&object)); }

template<typename Type>
inline String AMeta::ObjectDescriptionWrapper<Type, true>::getObjectDescription(const Type &object) { return object.getObjectDescription(); }

template<typename Type>
inline void AMeta::print<Type>::types() { std::cout << "Type: " << getStaticTypeName<Type>() << "\n"; }

template<typename Type, typename ...Types>
inline void AMeta::print<Type, Types...>::types() { print<Type>::types(); print<Types...>::types(); }

template<typename ...Types>
inline void AMeta::print<std::tuple<Types...>>::types() { print<Types...>::types(); }

template<typename ...FunctionArguments>
template<typename ...Arguments>
inline void AMeta::call<void(FunctionArguments...)>::withType<void(Arguments...)>::andArguments(void(*functionPointer)(FunctionArguments...), Arguments ...arguments)
{
    typedef typename isCallableArguments<void(FunctionArguments...)>:: template withArguments<void(Arguments...)> expression;
    static_assert(expression::value, "Arguments of the function is not convertible");
    typedef typename skip<sizeof...(FunctionArguments), Arguments...>::type UnusedArguments;
    typedef typename appendTuple<std::tuple<FunctionArguments...>, UnusedArguments>::type AllArguments;
    typedef typename functionFromTuple<void, AllArguments>::type NewFunctionType;
    reinterpret_cast<NewFunctionType>(functionPointer)(std::forward<FunctionArguments>(arguments)...);
}

template<typename ...FunctionArguments>
template<typename ...Arguments>
template<typename Object>
inline void AMeta::call<void(FunctionArguments...)>::withType<void(Arguments...)>::andArguments(Object *object, void(Object::*methodPointer)(FunctionArguments...), Arguments ...arguments)
{
    typedef typename isCallableArguments<void(FunctionArguments...)>:: template withArguments<void(Arguments...)> expression;
    static_assert(expression::value, "Arguments of the method is not convertible");
    typedef typename skip<sizeof...(FunctionArguments), Arguments...>::type UnusedArguments;
    typedef typename appendTuple<std::tuple<FunctionArguments...>, UnusedArguments>::type AllArguments;
    typedef typename methodFromTuple<Object, void, AllArguments>::type NewMethodType;
    (object->*reinterpret_cast<NewMethodType>(methodPointer))(std::forward<FunctionArguments>(arguments)...);
}

template<typename FunctionReturnType, typename ...FunctionArguments>
template<typename ReturnType, typename ...Arguments>
inline constexpr ReturnType AMeta::call<FunctionReturnType(FunctionArguments...)>::withType<ReturnType(Arguments ...arguments)>::andArguments(FunctionReturnType(*functionPointer)(FunctionArguments...), Arguments ...arguments)
{
    static_assert(std::is_convertible<FunctionReturnType, ReturnType>::value, "Return types is not convertible");
    typedef typename isCallableArguments<FunctionReturnType(FunctionArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
    static_assert(expression::value, "Arguments of the function is not convertible");
    typedef typename skip<sizeof...(FunctionArguments), Arguments...>::type UnusedArguments;
    typedef typename appendTuple<std::tuple<FunctionArguments...>, UnusedArguments>::type AllArguments;
    typedef typename functionFromTuple<FunctionReturnType, AllArguments>::type NewFunctionType;
    return reinterpret_cast<NewFunctionType>(functionPointer)(std::forward<FunctionArguments>(arguments)...);
}

template<typename FunctionReturnType, typename ...FunctionArguments>
template<typename ReturnType, typename ...Arguments>
template<typename Object>
inline constexpr ReturnType AMeta::call<FunctionReturnType(FunctionArguments...)>::withType<ReturnType(Arguments ...arguments)>::andArguments(Object *object, FunctionReturnType(Object::*methodPointer)(FunctionArguments...), Arguments ...arguments)
{
    static_assert(std::is_convertible<FunctionReturnType, ReturnType>::value, "Return types is not convertible");
    typedef typename isCallableArguments<FunctionReturnType(FunctionArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
    static_assert(expression::value, "Arguments of the method is not convertible");
    typedef typename skip<sizeof...(FunctionArguments), Arguments...>::type UnusedArguments;
    typedef typename appendTuple<std::tuple<FunctionArguments...>, UnusedArguments>::type AllArguments;
    typedef typename methodFromTuple<Object, FunctionReturnType, AllArguments>::type NewMethodType;
    return (object->*reinterpret_cast<NewMethodType>(methodPointer))(std::forward<FunctionArguments>(arguments)...);
}

template<typename FunctionReturnType, typename ...FunctionArguments>
template<typename ...Arguments>
inline void AMeta::call<FunctionReturnType(FunctionArguments...)>::withType<void(Arguments ...arguments)>::andArguments(FunctionReturnType(*functionPointer)(FunctionArguments...), Arguments ...arguments)
{
    typedef typename isCallableArguments<FunctionReturnType(FunctionArguments...)>:: template withArguments<void(Arguments...)> expression;
    static_assert(expression::value, "Arguments of the function is not convertible");
    typedef typename skip<sizeof...(FunctionArguments), Arguments...>::type UnusedArguments;
    typedef typename appendTuple<std::tuple<FunctionArguments...>, UnusedArguments>::type AllArguments;
    typedef typename functionFromTuple<FunctionReturnType, AllArguments>::type NewFunctionType;
    reinterpret_cast<NewFunctionType>(functionPointer)(std::forward<FunctionArguments>(arguments)...);
}

template<typename FunctionReturnType, typename ...FunctionArguments>
template<typename ...Arguments>
template<typename Object>
inline void AMeta::call<FunctionReturnType(FunctionArguments...)>::withType<void(Arguments ...arguments)>::andArguments(Object *object, FunctionReturnType(Object::*methodPointer)(FunctionArguments...), Arguments ...arguments)
{
    typedef typename isCallableArguments<FunctionReturnType(FunctionArguments...)>:: template withArguments<void(Arguments...)> expression;
    static_assert(expression::value, "Arguments of the method is not convertible");
    typedef typename skip<sizeof...(FunctionArguments), Arguments...>::type UnusedArguments;
    typedef typename appendTuple<std::tuple<FunctionArguments...>, UnusedArguments>::type AllArguments;
    typedef typename methodFromTuple<Object, FunctionReturnType, AllArguments>::type NewMethodType;
    (object->*reinterpret_cast<NewMethodType>(methodPointer))(std::forward<FunctionArguments>(arguments)...);
}

template<typename Type>
inline const AType &AMeta::getStaticType() { static AType type(typeid(Type)); return type; }

template<typename Type>
inline const char *AMeta::getStaticTypeName() { return getStaticType<Type>().getName(); }

template<typename Type>
inline std::size_t AMeta::getStaticTypeHash() { return getStaticType<Type>().getHash(); }

template<typename Type>
inline AType AMeta::getDynamicType(const Type &object) { return AType(typeid(object)); }

template<typename Type>
inline const char *AMeta::getDynamicTypeName(const Type &object) { return getDynamicType(object).getName(); }

template<typename Type>
inline std::size_t AMeta::getDynamicTypeHash(const Type &object) { return getDynamicType(object).getHash(); }

template<typename Type>
inline String AMeta::getObjectDescription(const Type &object) { return ObjectDescriptionWrapper<Type, hasObjectDescription<Type>::value>::getObjectDescription(object); }

//*******************************************************

template<>
struct AMeta::ObjectDescriptionPrinter<AMeta::TypeGroup::Boolean>
{
    template<typename Type>
    static inline void print(std::stringstream &stream, Type value)
    {
        stream << std::boolalpha << value;
    }
};

template<>
struct AMeta::ObjectDescriptionPrinter<AMeta::TypeGroup::Pointers>
{
    template<typename Type>
    static inline void print(std::stringstream &stream, Type value)
    {
        stream << std::hex << value;
    }
};

template<>
struct AMeta::ObjectDescriptionPrinter<AMeta::TypeGroup::Numbers>
{
    template<typename Type>
    static inline void print(std::stringstream &stream, Type value)
    {
        stream << std::dec << value;
    }
};

template<>
struct AMeta::ObjectDescriptionPrinter<AMeta::TypeGroup::Strings>
{
    template<typename Type>
    static inline void print(std::stringstream &stream, const Type &value)
    {
        stream << "\"" << value << "\"";
    }
};
/*
namespace AFormat
{

    inline String CreateFormatedString(const char *format, ... )
    {
        constexpr static std::size_t buffer = 1024 * 64;
        va_list list;
        Array<char> string(buffer, 0);
        va_start(list, format);
        vsnprintf(string.data(), buffer, format, list);
        va_end(list);
        return string.data();
    }

    template<typename Type, typename TypeGroup>
    struct ValueResolver
    {
        static std::string convert(const Type &object)
        {
            return AMeta::getObjectDescription(object);
        }

        static const char *resolve(const std::string &description)
        {
            return description.data();
        }
    };

    template<>
    struct ValueResolver<bool, AMeta::TypeGroup::Boolean>
    {
        static bool convert(bool value)
        {
            return value;
        }

        static const char *resolve(bool value)
        {
            return value ? "true" : "false";
        }
    };

    template<typename Type>
    struct ValueResolver<SharedReference<Type>, AMeta::TypeGroup::Objects>
    {
        static std::string convert(const SharedReference<Type> &pointer)
        {
            if(!pointer)
            {
                return "null";
            }

            return fmt::format("Shared({}, s = {})", AMeta::getObjectDescription(*pointer), pointer.use_count()).toUtf8();
        }

        static const char *resolve(const std::string &description)
        {
            return description.data();
        }
    };

    template<typename Type>
    struct ValueResolver<WeakReference<Type>, AMeta::TypeGroup::Objects>
    {
        static std::string convert(const WeakReference<Type> &pointer)
        {
            if(!pointer)
            {
                return "null";
            }

            return StringFormat("Weak(%s, s = %d, w = %d)", AMeta::getObjectDescription(*pointer), pointer.countSharedPointers(), pointer.countWeakPointers()).toUtf8();
        }

        static const char *resolve(const std::string &description)
        {
            return description.data();
        }
    };

    template<typename Type>
    struct ValueResolver<UniqueReference<Type>, AMeta::TypeGroup::Objects>
    {
        static std::string convert(const UniqueReference<Type> &pointer)
        {
            if(!pointer)
            {
                return "null";
            }

            return StringFormat("Unique(%s)", AMeta::getObjectDescription(*pointer)).toUtf8();
        }

        static const char *resolve(const std::string &description)
        {
            return description.data();
        }
    };

    template<>
    struct ValueResolver<void, AMeta::TypeGroup::Pointers>
    {
        static std::string convert(const void *pointer)
        {
            if(pointer == nullptr)
            {
                return "null";
            }

            return CreateFormatedString("0x%016x", pointer);
        }

        static const char *resolve(const std::string &description)
        {
            return description.data();
        }
    };

    template<typename Type>
    struct ValueResolver<Type, AMeta::TypeGroup::Pointers>
    {
        static std::string convert(const Type *pointer)
        {
            if(pointer == nullptr)
            {
                return "null";
            }

            return AMeta::getObjectDescription(*pointer);
        }

        static const char *resolve(const std::string &description)
        {
            return description.data();
        }
    };

    template<>
    struct ValueResolver<char, AMeta::TypeGroup::Pointers>
    {
        static const char *convert(const char *string)
        {
            return string;
        }

        static const char *resolve(const char *string)
        {
            return string;
        }
    };

    template<>
    struct ValueResolver<char16_t, AMeta::TypeGroup::Pointers>
    {
        static const char16_t *convert(const char16_t *string)
        {
            AAssert(false, "not implemented");
            return string;
        }
    };

    template<>
    struct ValueResolver<char32_t, AMeta::TypeGroup::Pointers>
    {
        static const char32_t *convert(const char32_t *string)
        {
            AAssert(false, "not implemented");
            return string;
        }
    };

    template<>
    struct ValueResolver<wchar_t, AMeta::TypeGroup::Pointers>
    {
        static const wchar_t *convert(const wchar_t *string)
        {
            AAssert(false, "not implemented");
            return string;
        }
    };

    template<typename Type>
    struct ValueResolver<Type, AMeta::TypeGroup::Numbers>
    {
        static Type convert(const Type &type)
        {
            return type;
        }

        static Type resolve(const Type &type)
        {
            return type;
        }
    };
}

template<typename ...Types>
inline String StringFormat(const char *format, const Types &...values)
{
    return AFormat::CreateFormatedString(format, (
        AFormat::ValueResolver<typename std::remove_const<typename std::remove_pointer<Types>::type>::type, typename AMeta::TypeResolver<Types>::TypeGroup>::resolve(
             AFormat::ValueResolver<typename std::remove_const<typename std::remove_pointer<Types>::type>::type, typename AMeta::TypeResolver<Types>::TypeGroup>::convert(values)
        )
    )...);
}*/
