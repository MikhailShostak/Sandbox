#pragma once

#include <Experimental>

#include "Includes/Editor.gen.h"
#include "EditableProperty.h"

namespace LegacyClassGen
{

class TextureEditor : public UI::FlexBox, public LegacyClassGen::Editor
{
    SharedReference<UI::TextField> textField = CreateShared<UI::TextField>();
    SharedReference<UI::EditableProperty> filtrationProperty = CreateShared<UI::EditableProperty>();
    SharedReference<UI::EditableProperty> wrappingProperty = CreateShared<UI::EditableProperty>();
    SharedReference<UI::EditableProperty> compilationProperty = CreateShared<UI::EditableProperty>();
    SharedReference<UI::ImageView> imageView = CreateShared<UI::ImageView>();

    SharedReference<LegacyClassGen::BaseCGType> type;
public:

    TextureEditor()
    {
        auto changed = [this]() {
            onChanged();
        };

        setData({{}, {}, {}, {}, {}});
        setDirection(UI::Direction::Vertical);
        setPadding({ 4, 4, 4, 4 });
        setSpacing(4);

        addView(textField);
        textField->setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            loadImage();
        });

        filtrationProperty->typeInfo.Name = "Graphics.TextureFiltration";
        filtrationProperty->propertyName = "Filtration";
        filtrationProperty->createEditor();
        filtrationProperty->onValueChanged = changed;
        addView(filtrationProperty->propertyEditorView);

        wrappingProperty->typeInfo.Name = "Graphics.TextureWrapping";
        wrappingProperty->propertyName = "Wrapping";
        wrappingProperty->createEditor();
        wrappingProperty->onValueChanged = changed;
        addView(wrappingProperty->propertyEditorView);

        compilationProperty->typeInfo.Name = "ClassGen.TextureCompilation";
        compilationProperty->propertyName = "Compilation";
        compilationProperty->createEditor();
        compilationProperty->onValueChanged = changed;
        addView(compilationProperty->propertyEditorView);

        addView(imageView);
    }

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        this->type = type;
        String path;
        if (data.read("Path", path))
        {
            textField->setText(path);
        }
        AJSONValue filtration;
        if (data.read("Filtration", filtration))
        {
            filtrationProperty->editor->serialize(filtration);
        }
        AJSONValue wrapping;
        if (data.read("Wrapping", wrapping))
        {
            wrappingProperty->editor->serialize(wrapping);
        }
        AJSONValue compilation;
        if (data.read("Compilation", compilation))
        {
            compilationProperty->editor->serialize(compilation);
        }
        loadImage();
    }

    void onSave(AJSONObject &data) override
    {
        data.insert("Path", APath(textField->getText()).toUnixPathString());
		data.insert("Filtration", filtrationProperty->editor->deserializeValue());
		data.insert("Wrapping", wrappingProperty->editor->deserializeValue());
		data.insert("Compilation", compilationProperty->editor->deserializeValue());
    }

    void loadImage()
    {
        imageView->setImage(nullptr);
        APathInfo pathInfo(type ? APath(textField->getText()).resolveWithDirectory(type->path.directory()) : APath(textField->getText()));
        if (!pathInfo.isExists())
        {
            return;
        }

        APixmap pixmap = APixmapLoader::getInstance().load(pathInfo.path());
        if (pixmap.getBufferSize() == 0)
        {
            return;
        }

        SharedReference<Graphics::Texture> texture = CreateShared<Graphics::Texture>();
        texture->setPixmap(pixmap);
        texture->load();
        imageView->setImage(texture);
    }
};

}
