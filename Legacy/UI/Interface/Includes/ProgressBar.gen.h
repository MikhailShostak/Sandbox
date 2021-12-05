#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

#include "Foundation"

//CLASSGEN END REGION
#include <Data>//TODO:temp include
#include "Includes/BorderImageView.gen.h"//TODO:temp include
#include "Core/AStyle.h"//TODO:temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class ProgressBar : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ProgressBar This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    ProgressBar();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
};
*/
class ProgressBar : public BorderImageView
{
public:
    typedef ProgressBar This;
    typedef BorderImageView Super;
private:
    float progress = 0;
    SharedReference<BorderImageView> progressView;
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual float getProgress() const;
    virtual void setProgress(float progress);
    virtual SharedReference<Legacy::Graphics::Texture> const &getProgressImage() const;
    virtual void setProgressImage(SharedReference<Legacy::Graphics::Texture> const &progressImage);
    virtual UIOffsets const &getProgressBorder() const;
    virtual void setProgressBorder(UIOffsets const &progressBorder);
    ProgressBar():progressView(new BorderImageView()) { addView(progressView); ApplyStyle(*this); }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
