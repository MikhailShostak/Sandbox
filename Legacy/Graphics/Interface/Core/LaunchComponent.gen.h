#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <Foundation>

//CLASSGEN END REGION
#include "Core/ApplicationComponent2.gen.h"
#include "Core/Window2.gen.h"
//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class LaunchComponent : public Core::ApplicationComponent2
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef LaunchComponent This;
    typedef Core::ApplicationComponent2 Super;
    typedef void Interfaces;
protected:
    Array<::SharedReference<Core::Window2>> Windows;
public:
    LaunchComponent();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<::SharedReference<Core::Window2>> getWindows() const;
    void setWindows(Array<::SharedReference<Core::Window2>> const &Windows);
    void setWindows(Array<::SharedReference<Core::Window2>> &&Windows);
    void onLoad();
    void onUnload();
    void onUpdate();
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
