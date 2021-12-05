//CLASSGEN GENERATED REGION: Includes
#include "Label.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Graphics>
#include "UIComponent.h"

bool LabelForceRendering = false;

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
Label::Label()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Label::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Text", toJSONValue(Text));
    object.insert("TextAlign", toJSONValue(TextAlign));
    object.insert("TextWrapping", toJSONValue(TextWrapping));
}
void Label::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Text", value);
x    fromJSONValue(value, Text);
    value = AJSONValue();
    object.read("TextAlign", value);
    fromJSONValue(value, TextAlign);
    value = AJSONValue();
    object.read("TextWrapping", value);
    fromJSONValue(value, TextWrapping);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
String Label::getText() const
{
    return this->Text;
}
void Label::setText(String const &Text)
{
    this->Text = Text;
}
void Label::setText(String &&Text)
{
    this->Text = std::move(Text);
}
Core::TextAlign Label::getTextAlign() const
{
    return this->TextAlign;
}
void Label::setTextAlign(Core::TextAlign const &TextAlign)
{
    this->TextAlign = TextAlign;
}
void Label::setTextAlign(Core::TextAlign &&TextAlign)
{
    this->TextAlign = std::move(TextAlign);
}
Core::TextWrapping Label::getTextWrapping() const
{
    return this->TextWrapping;
}
void Label::setTextWrapping(Core::TextWrapping const &TextWrapping)
{
    this->TextWrapping = TextWrapping;
}
void Label::setTextWrapping(Core::TextWrapping &&TextWrapping)
{
    this->TextWrapping = std::move(TextWrapping);
}
//CLASSGEN END REGION
};
*/

namespace
{

enum InsertBlending
{
    Replace,
    Add,
    Subtract,
    Multiply
};

enum InsertClipping
{
    Repeat,
    Clip
};

template<typename Type>
Type addWithoutOverflow(Type x, Type y)
{
    Type res = x + y;
    res |= -(res < x);

    return res;
}

template<typename Type>
Type subtractWithoutOverflow(Type x, Type y)
{
    Type res = x - y;
    res &= -(res <= x);

    return res;
}

void drawPixmap(APixmap &sourcePixmap, const APixmap &pixmap, const Math::IntegerVector &position, InsertBlending blending = Replace, InsertClipping clipping = Clip)
{
    if (sourcePixmap.getBufferSize() > 0 && pixmap.getBufferSize() > 0 && pixmap.getSize().x <= sourcePixmap.getSize().x && pixmap.getSize().y <= sourcePixmap.getSize().y)
    {
        if (sourcePixmap.getFormat() != pixmap.getFormat())
        {
            //ALogError("Pixmap", "Invalid format %s != %s", sourcePixmap.formatName().toUtf8().data(), pixmap.formatName().toUtf8().data());
            return;
        }

        switch (clipping)
        {
        case Clip:
        {
            auto iteratePixmaps = [&](uint8_t(*delegate)(uint8_t source, uint8_t value))
            {
                const Math::IntegerVector size = pixmap.getSize();
                const Math::IntegerVector sourceSize = sourcePixmap.getSize();
                const uint8_t channels = pixmap.getChannels();
                const size_t maxWidth = subtractWithoutOverflow<size_t>(size.x, subtractWithoutOverflow<size_t>(position.x + size.x, sourceSize.x));
                const size_t maxHeight = subtractWithoutOverflow<size_t>(size.y, subtractWithoutOverflow<size_t>(position.y + size.y, sourceSize.y));
                for (size_t i = 0; i < maxHeight; ++i)
                {
                    for (size_t j = 0; j < maxWidth; ++j)
                    {
                        for (size_t k = 0; k < channels; ++k)
                        {
                            const size_t sourcePosition = ((position.y + i) * sourceSize.x + (position.x + j)) * channels + k;
                            const size_t valuePosition = (i * size.x + j) * channels + k;
                            sourcePixmap[sourcePosition] = delegate(sourcePixmap[sourcePosition], pixmap[valuePosition]);
                        }
                    }
                }
            };

            switch (blending)
            {
            case Replace:
                iteratePixmaps([](uint8_t source, uint8_t value) { return value; });
                break;
            case Add:
                iteratePixmaps([](uint8_t source, uint8_t value) { return addWithoutOverflow(source, value); });
                break;
            case Subtract:
                iteratePixmaps([](uint8_t source, uint8_t value) { return subtractWithoutOverflow(source, value); });
                break;
            case Multiply:
                iteratePixmaps([](uint8_t source, uint8_t value) { return std::min<uint8_t>(uint16_t(source) * uint16_t(value), 255); });
                break;
            }
            break;
        }
        case Repeat:
        {

            auto iteratePixmaps = [&](uint8_t(*delegate)(uint8_t source, uint8_t value))
            {
                const Math::IntegerVector size = pixmap.getSize();
                const Math::IntegerVector sourceSize = sourcePixmap.getSize();
                const uint8_t channels = pixmap.getChannels();

                for (size_t i = 0; i < size.y; ++i)
                {
                    for (size_t j = 0; j < size.x; ++j)
                    {
                        const size_t sourcePosition = ((position.y + i) % sourceSize.y) * sourceSize.x + (((position.x + j) % sourceSize.x));
                        const size_t valuePosition = i * size.x + j;
                        sourcePixmap[sourcePosition] = delegate(sourcePixmap[sourcePosition], pixmap[valuePosition]);
                    }
                }
            };

            switch (blending)
            {
            case Replace:
                iteratePixmaps([](uint8_t source, uint8_t value) { return value; });
                break;
            case Add:
                iteratePixmaps([](uint8_t source, uint8_t value) { return addWithoutOverflow(source, value); });
                break;
            case Subtract:
                iteratePixmaps([](uint8_t source, uint8_t value) { return subtractWithoutOverflow(source, value); });
                break;
            case Multiply:
                iteratePixmaps([](uint8_t source, uint8_t value) { return std::min<uint8_t>(uint16_t(source) * uint16_t(value), 255); });
                break;
            }
            break;
        }
        }
    }
}

Atlas<256> createAtlas(const Core::Font &font)
{    
    Atlas<256> atlas;
    const Core::FontEngine::FontChache *fontCache = font._chache;
    if (!fontCache)
    {
        return atlas;
    }

    Math::IntegerVector cellSize{};
    size_t range_min = 0;
    size_t range_max = 256;
    
    for(size_t i = range_min; i < range_max; ++i)
    {
        const Core::FontEngine::GlyphData *glyph = fontCache->glyph((char)(i));
        cellSize = Math::getMax2(cellSize, Math::IntegerVector{ static_cast<int32_t>(glyph->metrics.horiAdvance), static_cast<int32_t>(fontCache->height())});
    }

    Math::IntegerVector pixmapSize = cellSize * Math::IntegerVector{ 16, 16 };

    Array<uint8_t> array;
    array.resize(pixmapSize.getArea2(), 0);
    atlas.pixmap.setBuffer(array, pixmapSize, APixmapDataFormat::Gray);

    for(size_t i = range_min; i < range_max; ++i)
    {
        const Core::FontEngine::GlyphData *glyph = fontCache->glyph((char)(i));

        atlas.slices[i].Position = (Math::IntegerVector{ static_cast<int32_t>(i % 16), static_cast<int32_t>(i / 16) } * pixmapSize) / Math::IntegerVector{ 16, 16, 1, 1 };
        atlas.slices[i].Size = glyph->pixmap.getSize();
        drawPixmap(atlas.pixmap, glyph->pixmap, atlas.slices[i].Position /*+ Math::IntegerVector{ glyph->metrics.horiBearingX, fontCache->ascent() - glyph->metrics.horiBearingY }*/);
    }

    return atlas;
}

TextMetrics getMetrics(const String &text, const Core::Font &font, int32_t max_line_width = std::numeric_limits<int32_t>::max())
{
    TextMetrics metrics;

    metrics.lineSize = font._chache->height();

    Math::IntegerVector position{};

    metrics.chars.resize(text.size());

    for (size_t i = 0; i < text.size(); ++i)
    {
        char ch = (char)(text[i]);
        const Core::FontEngine::GlyphData *glyph = font._chache->glyph(ch);
        size_t advance = glyph->metrics.horiAdvance;
        if(ch == ' ')
        {
            position.X += advance;
            continue;
        }
        else if(ch == '\t')
        {
            position.X += advance * 4;
            continue;
        }
        else if(ch == '\n')
        {
            position.X = 0;
            position.Y += metrics.lineSize;
            continue;
        }
        
        if(max_line_width > 0 && (position.X + advance) > max_line_width)
        {
            position.X = 0;
            position.Y += metrics.lineSize;
        }

        metrics.chars[i] = {
            ch,
            Math::IntegerRectangle{
                (position + Math::IntegerVector{
                    static_cast<int32_t>(glyph->metrics.horiBearingX),
                    static_cast<int32_t>(font._chache->ascent() - glyph->metrics.horiBearingY)
                }),
                Math::IntegerVector{
                    static_cast<int32_t>(glyph->metrics.width),
                    static_cast<int32_t>(glyph->metrics.height)
                },
            }
        };

        //float fhadvance = glyph->metrics.horiAdvance;
        //float fvadvance = glyph->metrics.vertAdvance;

        position.X += advance;
    }

    metrics.size = Math::IntegerVector{
        static_cast<int32_t>(position.X),
        static_cast<int32_t>(position.Y + metrics.lineSize),
    };

    return metrics;
}

template<typename Functor>
SharedReference<Legacy::Graphics::Mesh> generateQuads(size_t count, const Functor &vertexFunctor)
{
    SharedReference<Legacy::Graphics::Mesh> mesh = CreateShared<Legacy::Graphics::Mesh>();

    Array<AVertex> vertices;
    Array<AFace> faces;
    for (size_t i = 0; i < count; ++i)
    {
        size_t n = vertices.size();
        faces.push_back({ static_cast<int16_t>(n + 0), static_cast<int16_t>(n + 2), static_cast<int16_t>(n + 1) });
        faces.push_back({ static_cast<int16_t>(n + 1), static_cast<int16_t>(n + 2), static_cast<int16_t>(n + 3) });

        vertexFunctor(i, vertices);
    }
        
    mesh->setVertices(vertices);
    mesh->setFaces(faces);

    return mesh;
}

SharedReference<Legacy::Graphics::Mesh> generateTextMesh(const TextMetrics &metrics, const Atlas<256> &atlas)
{
    return generateQuads(metrics.chars.size(), [&](size_t index, auto &vertices){
        auto ch = metrics.chars[index].first;
        Math::Rectangle v = metrics.getNormalizedCharMetrics(index);
        Math::Rectangle UV = atlas.getUV(ch);

        vertices.push_back({ v.Position.X, v.Position.Y + v.Size.Y,  0.0f, 0.0f, 0.0f, 1.0f, UV.getLeft(), UV.getBottom() });
        vertices.push_back({ v.Position.X + v.Size.X,  v.Position.Y + v.Size.Y,  0.0f, 0.0f, 0.0f, 1.0f, UV.getRight(), UV.getBottom() });
        vertices.push_back({ v.Position.X, v.Position.Y, 0.0f, 0.0f, 0.0f, 1.0f, UV.getLeft(), UV.getTop() });
        vertices.push_back({ v.Position.X + v.Size.X,  v.Position.Y, 0.0f, 0.0f, 0.0f, 1.0f, UV.getRight(), UV.getTop() });
    });
}

class AtlasManager : public ASingleton<AtlasManager>
{
public:
    Map<Core::FontEngine::FontChache *, APair<Atlas<256>, SharedReference<Legacy::Graphics::Texture>>> cache;

    const APair<Atlas<256>, SharedReference<Legacy::Graphics::Texture>> &getAtlas(const Core::Font &font)
    {
        auto it = cache.find(font._chache);
        if(it == cache.end())
        {
            cache.insert({ font._chache, { createAtlas(font), CreateShared<Legacy::Graphics::Texture>() } });
        }

        return cache.at(font._chache);
    }
};

}

AStaticRun(LabelMetaObject)
{
    CLASSGEN_GENERATED_REGION_META_OBJECT
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<Label>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const Label&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<Label&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<Label, SharedReference<DynamicLabelMaterial>>("Material", &Label::getMaterial, &Label::setMaterial, false);
    object.registerMetaProperty<Label, Core::Font>("Font", &Label::getFont, &Label::setFont, false);
    object.registerMetaProperty<Label, Core::TextAlign>("TextAlign", &Label::getTextAlign, &Label::setTextAlign, false);
    object.registerMetaProperty<Label, Core::TextWrapping>("TextWrapping", &Label::getTextWrapping, &Label::setTextWrapping, false);
    object.registerMetaProperty<Label, String>("Text", &Label::getText, &Label::setText, false);
    object.registerMetaProperty<Label, AColor>("Color", &Label::getColor, &Label::setColor, false);
    object.registerMetaProperty<Label, Math::IntegerVector>("Size", &Label::getSize, &Label::setSize, false);
    object.registerMetaProperty<Label, Math::IntegerVector>("ContentSize", &Label::getContentSize, static_cast<void(Label::*)(Math::IntegerVector const &)>(nullptr), false);
    manager.registerMetaObject("UI.Label", object);
    CLASSGEN_END_REGION
}

CLASSGEN_GENERATED_REGION_OBJECT
void Label::serialize(AJSONObject &object) const
{
    object.insert("Text", toJSONValue(text));
    object.insert("TextAlign", toJSONValue(textAlign));
    object.insert("TextWrapping", toJSONValue(textWrapping));
    object.insert("Color", toJSONValue(color));
    Super::serialize(object);
}
void Label::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);

    AJSONValue value;

    value = AJSONValue();
    object.read("Text", value);
    fromJSONValue(value, text);

    value = AJSONValue();
    object.read("TextAlign", value);
    fromJSONValue(value, textAlign);

    value = AJSONValue();
    object.read("TextWrapping", value);
    fromJSONValue(value, textWrapping);

    value = AJSONValue();
    object.read("Color", value);
    fromJSONValue(value, color);
}
SharedReference<DynamicLabelMaterial> const &Label::getMaterial() const
{
    return this->material;
}
void Label::setMaterial(SharedReference<DynamicLabelMaterial> const &material)
{
    this->material = material;
}
Core::Font const &Label::getFont() const
{
    return this->font;
}
void Label::setFont(Core::Font const &font)
{
    this->font = font;
    UpdateTextTexture();
}
Core::TextAlign Label::getTextAlign() const
{
    return this->textAlign;
}
void Label::setTextAlign(Core::TextAlign const &textAlign)
{
    this->textAlign = textAlign;
    UpdateTextTexture();
}
Core::TextWrapping Label::getTextWrapping() const
{
    return this->textWrapping;
}
void Label::setTextWrapping(Core::TextWrapping const &textWrapping)
{
    this->textWrapping = textWrapping;
    UpdateTextTexture();
}
String const &Label::getText() const
{
    return this->text;
}
void Label::setText(String const &text)
{
    this->text = text;
    UpdateTextTexture();
}
AColor const &Label::getColor() const
{
    return material->data.Color;
}
void Label::setColor(AColor const &color)
{
    material->data.Color = color;
}
CLASSGEN_END_REGION

const Math::IntegerVector &Label::getSize() const
{
    return Super::getSize();
}

void Label::setSize(const Math::IntegerVector &size)
{
    if (getSize().x == size.x && getSize().y == size.y)
    {
        return;
    }
    Super::setSize(size);
    UpdateTextTexture();
}

Math::IntegerVector Label::getContentSize() const
{
    if (!text.empty() && font.isValid())
    {
        switch (getTextWrapping())
        {
        case Core::TextWrapping::Inline:
        {
            auto m = getMetrics(getText(), font);
            return Math::IntegerVector{m.size.X, m.size.Y};
        }
            //return Core::FontEngine::getInstance().getTextSize(getText(), getFont(), getTextWrapping());
        case Core::TextWrapping::WordWrap:
        case Core::TextWrapping::Wrap:
        {
            auto m = getMetrics(getText(), font, getSize().X);
            return Math::IntegerVector{getSize().X, m.size.Y};
        }
            //return Core::FontEngine::getInstance().getTextSize(getText(), getFont(), getTextWrapping(), getSize().x);
        }
    }

    return Math::IntegerVector{ 0, font.isValid() ? Core::FontEngine::getInstance().getLineHeight(font) : 0 };
}

void Label::onCreate()
{
    setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);

    textAlign = Core::TextAlign::Left;
    textWrapping = Core::TextWrapping::Inline;

    material = CreateShared<DynamicLabelMaterial>();
    material->setOpaque(false);

    ApplyStyle(*this);
}

void Label::UpdateTextTexture()
{
    if (!text.empty() && font.isValid())
    {
        //this->material = Create<DynamicLabelMaterial>();
        //this->material->load();

        //font = Core::Font("Noto Sans UI", "Regular", 12);
        const auto &pair = AtlasManager::getInstance().getAtlas(font);
        material->data.TextMask = pair.second;
        atlas = &pair.first;

        if (!this->material->data.TextMask->isLoaded())
        {
            this->material->data.TextMask->setPixmap(std::move(atlas->pixmap));
        }
        //if (!this->material->data.TextMask->isLoaded() && !material->data.TextMask->getSize().isEmpty())
        //{
        //    this->material->data.TextMask->load();
        //}

        /*material->data.TextMask->unload();
        material->data.TextMask->setPixmap(Core::FontEngine::getInstance().renderText(getText(), getFont(), getTextAlign(), getTextWrapping(), getSize().x));
        if (!material->data.TextMask->isLoaded() && !material->data.TextMask->getSize().isEmpty())
        {
            material->data.TextMask->load();
        }*/
        switch (getTextWrapping())
        {
        case Core::TextWrapping::Inline:
        {
            metrics = getMetrics(getText(), font);
            break;
        }
        case Core::TextWrapping::WordWrap:
        case Core::TextWrapping::Wrap:
        {
            metrics = getMetrics(getText(), font, getSize().X);
            break;
        }
        }
        Super::setSize(Math::IntegerVector{getSize().X, metrics.size.Y});
        this->mesh = generateTextMesh(metrics, *atlas);
        this->mesh->load();
    }
    else
    {
        material->data.TextMask = Legacy::Graphics::Texture::getWhiteTexture();
    }
    requestLayoutUpdate();
}

void Label::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    if (getSize().isEmpty())
    {
        setSize(getContentSize());
    }
    //TODO: investigate why it's called not once
    if (!material->isLoaded())
    {
        material->load();
    }
    if (material->data.TextMask && !material->data.TextMask->isLoaded() && !material->data.TextMask->getSize().isEmpty())
    {
        material->data.TextMask->load();
    }
}

void Label::onDraw(AUpdateEvent &event)
{
    Super::onDraw(event);

    if(LabelForceRendering || mesh && mesh->isLoaded() && material && material->isLoaded())
    {
        material->data.ModelViewProjectionMatrix = Math::Matrix::getScale2({ metrics.lineSize, metrics.lineSize }) * getGlobalMatrix()/* ACamera::getCurrentCamera()->getMatrix()*/;
        //UIVisualDebug().drawMeshWireframe(getGraphicsMatrix(), Component::getSprite(), AColor(AColorName::Green));
        //UIVisualDebug().drawMeshWireframe(material->data.ModelViewProjectionMatrix, mesh, AColor(AColorName::White));
        //UIVisualDebug().drawMeshWireframe(material->data.ModelViewProjectionMatrix, Component::getSprite(), AColor(AColorName::Yellow));
        material->data.ModelViewProjectionMatrix = material->data.ModelViewProjectionMatrix * ACamera::getCurrentCamera()->getMatrix();
        Legacy::Graphics::GraphicsContext::getCurrent().draw(mesh, material);
    }
    
    /*
    Math::IntegerVector textSize = material->data.TextMask->getSize();

    Math::Vector offset;
    switch (getTextAlign())
    {
    case Core::TextAlign::Center:
        offset.x = (getSize().x - textSize.x) / 2;
        break;
    case Core::TextAlign::Right:
        offset.x = getSize().x - textSize.x;
        break;
    default:
        break;
    }

    Math::Matrix textMatrix = Math::Matrix::getScale2({ textSize.x, textSize.y }) * Math::Matrix::getTranslation(offset) * getGlobalMatrix();
    material->data.ModelViewProjectionMatrix = textMatrix * ACamera::getCurrentCamera()->getMatrix();
    Legacy::Graphics::GraphicsContext::getCurrent().draw(Component::getSprite(), material);*/
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
