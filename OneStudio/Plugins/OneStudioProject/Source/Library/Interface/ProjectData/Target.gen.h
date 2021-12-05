#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "RunningData.gen.h"
#include "Action.gen.h"
#include "Settings.gen.h"

//CLASSGEN END REGION
#include "OSSettings.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct Target : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
protected:
    typedef Target This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Name;
    OneStudioProject2::RunningData Run;
    Array<OneStudioProject2::Action> Actions;
    Array<OneStudioProject2::Settings> Settings;
public:
    Target();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    StringHashMap<size_t> settingsMap;
    StringHashMap<SharedReference<OSSettings>> settings;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
