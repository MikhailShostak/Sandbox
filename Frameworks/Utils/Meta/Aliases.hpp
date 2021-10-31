#pragma once

namespace Meta
{

using Null = std::nullptr_t;
using False = std::false_type;
using True = std::true_type;

template<typename ReturnType, typename ...ArgumentTypes>
using FunctionPointer = ReturnType(*)(ArgumentTypes...);

template<typename ...ArgumentTypes>
using VoidFunctionPointer = FunctionPointer<void, ArgumentTypes...>;

template<typename ClassType, typename ReturnType, typename ...ArgumentTypes>
using MethodPointer = ReturnType(ClassType:: *)(ArgumentTypes...);

template<typename ClassType, typename ...ArgumentTypes>
using VoidMethodPointer = MethodPointer<ClassType, void, ArgumentTypes...>;

template<typename ValueType, typename ClassType>
using MemberPointer = ValueType ClassType:: *;

template<typename Type, typename ...Arguments>
using ConstructorPointer = FunctionPointer<Type *, Arguments...>;

template<typename Type>
using DestructorPointer = FunctionPointer<void, Type *>;

template<typename ...Arguments>
using AbstractConstructorPointer = ConstructorPointer<void, Arguments...>;

using AbstractDestructorPointer = DestructorPointer<void>;

namespace Details
{

template<typename ReturnType, typename ...ArgumentTypes>
ReturnType FunctionReturnType(FunctionPointer<ReturnType, ArgumentTypes...>);

template<typename ReturnType, typename ...ArgumentTypes>
std::tuple<ArgumentTypes...> FunctionArgumentTypes(FunctionPointer<ReturnType, ArgumentTypes...>);


template<typename ClassType, typename ReturnType, typename ...ArgumentTypes>
ClassType MethodClassType(MethodPointer<ClassType, ReturnType, ArgumentTypes...>);

template<typename ClassType, typename ReturnType, typename ...ArgumentTypes>
ReturnType MethodReturnType(MethodPointer<ClassType, ReturnType, ArgumentTypes...>);

template<typename ClassType, typename ReturnType, typename ...ArgumentTypes>
std::tuple<ArgumentTypes...> MethodArgumentTypes(MethodPointer<ClassType, ReturnType, ArgumentTypes...>);


template<typename ValueType, typename ClassType>
ValueType MemberValueType(ValueType ClassType::*);

template<typename ValueType, typename ClassType>
ClassType MemberClassType(ValueType ClassType::*);

}

template<auto Function>
using FunctionReturnType = decltype(Details::FunctionReturnType(Function));

template<auto Function>
using FunctionArgumentTypes = decltype(Details::FunctionArgumentTypes(Function));

template<auto Method>
using MethodClassType = decltype(Details::MethodClassType(Method));

template<auto Method>
using MethodReturnType = decltype(Details::MethodReturnType(Method));

template<auto Method>
using MethodArgumentTypes = decltype(Details::MethodArgumentTypes(Method));


template<auto MemberPointer>
using MemberPointerValueType = decltype(Details::MemberValueType(MemberPointer));

template<auto MemberPointer>
using MemberPointerClassType = decltype(Details::MemberClassType(MemberPointer));

template<typename ReturnType, typename ...ArgumentTypes>
using Function = std::function<ReturnType(ArgumentTypes...)>;

}
