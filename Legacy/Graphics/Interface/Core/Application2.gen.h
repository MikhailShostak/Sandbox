#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include "ApplicationComponent2.gen.h"
#include <system_error>
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Application2 : public Serializable
//CLASSGEN END REGION
{
    struct ApplicationStorage : ASingleton<ApplicationStorage>
    {
        Application2 *instance = nullptr;
    };
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Application2 This;
    typedef Serializable Super;
    typedef void Interfaces;
protected:
    Array<::SharedReference<Core::ApplicationComponent2>> Components;
public:
    Application2();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<::SharedReference<Core::ApplicationComponent2>> getComponents() const;
    void setComponents(Array<::SharedReference<Core::ApplicationComponent2>> const &Components);
    void setComponents(Array<::SharedReference<Core::ApplicationComponent2>> &&Components);
    SignedInteger /*ExitCode*/ execute();
//CLASSGEN END REGION
    static Application2 &getInstance() { return *ApplicationStorage::getInstance().instance; }

    bool running = true;
    std::error_code error;
    void exit() { running = false; }

    template<typename T>
    ::SharedReference<T> FindComponent() const
    {
        auto it = rng::find_if(Components, [this](const auto &component){ return DynamicCast<T>(component) != nullptr; });
        
        if(it == Components.end())
        {
            return nullptr;
        }

        return StaticCast<T>(*it);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
