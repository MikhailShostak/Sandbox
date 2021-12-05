#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include "Core/BaseCGType.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Editor : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Editor This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Editor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    ADelegate<void()> onChanged;
    virtual ~Editor() {}
    virtual void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) {}
    virtual void onSave(AJSONObject &data) {}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
