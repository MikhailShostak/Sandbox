//CLASSGEN GENERATED REGION: Includes
#include "ProgressBar.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION
#include "MetaObject.h"//TODO:temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
ProgressBar::ProgressBar()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ProgressBar::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ProgressBar::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ProgressBar::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ProgressBar");
}
//CLASSGEN END REGION
*/

AStaticRun(ProgressBarMetaObject)
{
    CLASSGEN_GENERATED_REGION_META_OBJECT
        MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<ProgressBar>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const ProgressBar&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<ProgressBar&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<BorderImageView>();
    object.registerMetaProperty<ProgressBar, float>("Progress", &ProgressBar::getProgress, &ProgressBar::setProgress, true);
    object.registerMetaProperty<ProgressBar, SharedReference<Legacy::Graphics::Texture>>("ProgressImage", &ProgressBar::getProgressImage, &ProgressBar::setProgressImage, false);
    object.registerMetaProperty<ProgressBar, UIOffsets>("ProgressBorder", &ProgressBar::getProgressBorder, &ProgressBar::setProgressBorder, false);
    manager.registerMetaObject("UI.ProgressBar", object);
    CLASSGEN_END_REGION
}

CLASSGEN_GENERATED_REGION_OBJECT
void ProgressBar::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Progress", toJSONValue(progress));
}
void ProgressBar::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Progress", value);
    fromJSONValue(value, progress);

}
float ProgressBar::getProgress() const
{
    return this->progress;
}
CLASSGEN_END_REGION

void ProgressBar::setProgress(float progress)
{
    this->progress = progress;

    Math::IntegerVector s = getSize();

    const size_t mainDirection = s.getXYAspectRatio() > 1 ? 0 : 1;

    s[mainDirection] = s[mainDirection] * progress;
    progressView->setSize(s);
}

SharedReference<Legacy::Graphics::Texture> const &ProgressBar::getProgressImage() const
{
    return progressView->getImage();
}

void ProgressBar::setProgressImage(SharedReference<Legacy::Graphics::Texture> const &progressImage)
{
    progressView->setImage(progressImage);
}

UIOffsets const &ProgressBar::getProgressBorder() const
{
    return progressView->getBorder();
}

void ProgressBar::setProgressBorder(UIOffsets const &progressBorder)
{
    progressView->setBorder(progressBorder);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
