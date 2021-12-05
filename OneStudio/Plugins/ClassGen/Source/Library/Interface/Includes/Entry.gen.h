#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Entry
//CLASSGEN END REGION
    : public Serializable
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Entry This;
    typedef void Super;
    typedef void Interfaces;
public:
    virtual ~Entry(){}
    virtual String /*Code*/ generate(Array<String> const& Parameters) = 0;
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
