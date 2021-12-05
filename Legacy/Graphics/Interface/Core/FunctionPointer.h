#pragma once

template<typename ReturnType, typename ...Types>
using FunctionPointer = ReturnType(*)(Types...);

template<typename ObjectType, typename ReturnType, typename ...Types>
using MethodPointer = ReturnType(ObjectType::*)(Types...);

template<typename ObjectType, typename ReturnType, typename ...Types>
using ConstantMethodPointer = ReturnType(ObjectType::*)(Types...) const;

using VoidFunctionPointer = FunctionPointer<void>;

template<typename ObjectType>
using VoidMethodPointer = MethodPointer<ObjectType, void>;

template<typename ObjectType>
using VoidConstantMethodPointer = ConstantMethodPointer<ObjectType, void>;
