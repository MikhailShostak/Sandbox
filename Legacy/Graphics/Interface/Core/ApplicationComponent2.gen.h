#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationComponent2 : public AObject
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationComponent2 This;
    typedef AObject Super;
    typedef void Interfaces;
protected:
    Array<String> Tags;
Boolean Active;
public:
    ApplicationComponent2();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<String> getTags() const;
    void setTags(Array<String> const &Tags);
    void setTags(Array<String> &&Tags);
    Boolean getActive() const;
    void setActive(Boolean const &Active);
    void setActive(Boolean &&Active);
    void load();
    void unload();
    void update();
//CLASSGEN END REGION
    virtual void onLoad() {}
    virtual void onUnload() {}
    virtual void onUpdate() {}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
