#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

#include "Foundation"
#include "ClassGenExtensions"
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ClassSuggestionsComponent.h"
#include "ClassPicker.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ImagePropertyEditor : public UI::FlexBox, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ImagePropertyEditor This;
    typedef UI::FlexBox Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    ImagePropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<LegacyClassGen::ClassPicker> classPicker;
    SharedReference<UI::ImageView> previewImageView;
    void onHierarchyCreate();
//CLASSGEN END REGION
    AJSONValue value;
    UI::ClassSuggestionsComponent suggestionsComponent;
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        suggestionsComponent.findAsset = true;
        suggestionsComponent.addView(*classPicker->textField);

        classPicker->textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            updatePreview();
            notifyValueChange();
        });
    }

    void updatePreview()
    {
        return;
        /*Map<String, SharedReference<LegacyClassGen::ClassDataInstance>> &types = LegacyClassGen::ClassRepository::getInstance().indexedTypes;
        auto it = types.find(textField->getText());
        if (it == types.end())
        {
            return;
        }

        SharedReference<Graphics::Texture> texture;

        String path;
        if (it->second->type->data.read("Path", path))
        {
            APixmap pixmap = APixmapLoader::getInstance().load(path);
            if (pixmap.getBufferSize() == 0)
            {
                return;
            }

            texture = Create<Graphics::Texture>();
            texture->setPixmap(pixmap);
        }

        if (texture)
        {
            texture->load();
            previewImageView->setImage(texture);
        }*/
    }

    void onSerialize(const AJSONValue &value) override
    {
        classPicker->textField->setText(value.toString());
        updatePreview();
    }

    AJSONValue onDeserialize() override { return classPicker->textField->getText(); }

    FieldEditorLayoutType getLayoutType() const { return Multiline; }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
