#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class FunctionManager : public Serializable
//CLASSGEN END REGION
, public ASingleton<FunctionManager>
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FunctionManager This;
    typedef Serializable Super;
    typedef void Interfaces;
protected:
    String Test;
public:
    FunctionManager();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    String getTest() const;
    void setTest(String const &Test);
    void setTest(String &&Test);
    //CLASSGEN END REGION
    Array<LegacyClassGen::FunctionInfo> Cache;
    Array<LegacyClassGen::FunctionInfo> Fetch();
    void ClearIndex();
    void Index();
    void ReIndex();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
