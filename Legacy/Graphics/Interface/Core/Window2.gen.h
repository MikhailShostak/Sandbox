#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "MathClasses"

//CLASSGEN END REGION
#include "Core/AWindowEvents.h"
//#include "Graphics/GraphicsComponents/Composition.gen.h"
using Color = AColor;
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class Window2 : public AObject
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Window2 This;
    typedef AObject Super;
    typedef void Interfaces;
protected:
    //::SharedReference<Graphics::Composition> Composition;
String Title;
Color BackgroundColor;
Math::IntegerVector InitialSize;
public:
    Window2();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    /*::SharedReference<Graphics::Composition> getComposition() const;
    void setComposition(::SharedReference<Graphics::Composition> const &Composition);
    void setComposition(::SharedReference<Graphics::Composition> &&Composition);*/
    String getTitle() const;
    void setTitle(String const &Title);
    void setTitle(String &&Title);
    Color getBackgroundColor() const;
    void setBackgroundColor(Color const &BackgroundColor);
    void setBackgroundColor(Color &&BackgroundColor);
    Math::IntegerVector getInitialSize() const;
    void setInitialSize(Math::IntegerVector const &InitialSize);
    void setInitialSize(Math::IntegerVector &&InitialSize);
//CLASSGEN END REGION
    ~Window2();

    struct
    {
        Math::IntegerVector MousePosition = {};
        ATouchModifier TouchModifier = ATouchModifier::Undefined;
    } InputState;
    
    bool IsActive() const;
    
    virtual void OnCreate();
    virtual void OnUpdate();

    //InplaceStorage<struct WindowPrivateData, 352, 8> data;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

namespace Memory
{

template<typename Type>
struct Constructor<Type, Core::Window2>
{
    inline static Type *Create()
    {
        Type *window = Constructor<Type, Core::Window2::Super>::Create();
        window->OnCreate();
        return window;
    }
};

}
