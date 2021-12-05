#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TestView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
protected:
    typedef TestView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
protected:
    Boolean Test1;
Boolean Test2;
public:
    TestView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Boolean getTest1() const;
    void setTest1(Boolean const &Test1);
    void setTest1(Boolean &&Test1);
    Boolean getTest2() const;
    void setTest2(Boolean const &Test2);
    void setTest2(Boolean &&Test2);
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
