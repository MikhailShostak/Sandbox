#pragma once

namespace System
{
template<typename InterfaceType>
struct ExtensionHandle
{
    using This = ExtensionHandle;
    System::ExtensionInfo Info;
    Meta::ConstructorPointer<InterfaceType> Constructor;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}

#define REGISTER_EXTENSION(InterfaceType, DerivedType, version, package)\
System::ExtensionHandle<InterfaceType> _ ## DerivedType ## _ ## Main()\
{\
    return System::ExtensionHandle<InterfaceType>\
    {\
        System::ExtensionInfo{\
            System::Version{ #version },\
            System::PackageIdentifier{ #package }\
        },\
        &Memory::CreateAs<DerivedType, InterfaceType>\
    };\
}\
\
BOOST_DLL_ALIAS(_ ## DerivedType ## _ ## Main, Main)\
