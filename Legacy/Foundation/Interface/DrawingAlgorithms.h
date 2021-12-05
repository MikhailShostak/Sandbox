#pragma once

#include "Blending.h"

template<typename Type>
inline constexpr Type blend(Type source, Type value, const Blending blending)
{
    if (std::numeric_limits<Type>::is_integer)
    {
        Math::FloatType normalizedSource = Math::FloatType(source) / std::numeric_limits<Type>::max();
        Math::FloatType normalizedValue = Math::FloatType(value) / std::numeric_limits<Type>::max();
        Math::FloatType result = blend(normalizedSource, normalizedValue, blending);
        return Math::clamp<Math::FloatType>(result, 0, 1) * std::numeric_limits<Type>::max();
    }

    switch (blending)
    {
    case Add:
        return source + value;
    case Subtract:
        return source - value;
    case Divide:
        return value != 0 ? source / value : std::numeric_limits<Type>::max();
    case Multiply:
        return source * value;
    case Screen:
        return 1 - (1 - source) * (1 - value);
    case Overlay:
        return source < 0.5 / 2 ? 2 * source * value : 1 - 2 * (1 - source) * (1 - value);
    default:
        return value;
    }
}

inline AColor blendRGB(const AColor &source, const AColor &value, Blending blending)
{
    AColor result;

    if (blending == Blending::Replace)
    {
        result = value;
        return result;
    }

    for (size_t i = 0; i < 3; ++i)
    {
        result[i] = blend(source[i], value[i], blending);
    }

    return result;
}

inline AColor blendRGBA(const AColor &source, const AColor &value, Blending blending)
{
    AColor result;

    if (blending == Blending::Replace)
    {
        result = value;
        return result;
    }

    for (size_t i = 0; i < 4; ++i)
    {
        result[i] = blend(source[i], value[i], blending);
    }

    return result;
}

inline AColor &multiplyAlpha(AColor &color)
{
    color.Red *= color.Alpha;
    color.Green *= color.Alpha;
    color.Blue *= color.Alpha;
    return color;
};

inline AColor getColorWithMultipliedAlpha(const AColor &color)
{
    return {
        color.Red * color.Alpha,
        color.Green * color.Alpha,
        color.Blue * color.Alpha,
        color.Alpha
    };
};

inline AColor blendRGBAWithAlphaBlending(const AColor &source, const AColor &value, Blending blending = Blending::Add, bool premultiplied = true)
{
    AColor result;

    float alphaFactor = (1 - value.Alpha);
    if (premultiplied)
    {
        result = blendRGBA(source * alphaFactor, value, blending);
        return result;
    }

    result = blendRGBA(getColorWithMultipliedAlpha(source) * alphaFactor, getColorWithMultipliedAlpha(value), blending);
    return result;
}

inline void drawPoint(APixmap &pixmap, size_t x, size_t y, const AColor &color, const Blending blending = Replace)
{
    size_t i = y * pixmap.getSize().x * pixmap.getChannels() + x * pixmap.getChannels();
    AColor source;
    switch (pixmap.getChannels())
    {
    case 4:
        source.Alpha = pixmap[i + 3] / 255.0f;
    case 3:
        source.Blue = pixmap[i + 2] / 255.0f;
    case 2:
        source.Green = pixmap[i + 1] / 255.0f;
    case 1:
        source.Red = pixmap[i] / 255.0f;
    default:
        break;
    }
    AColor result = blendRGBA(source, color, blending);
    switch (pixmap.getChannels())
    {
    case 4:
        pixmap[i + 3] = result.Alpha * 255.0f;
    case 3:
        pixmap[i + 2] = result.Blue * 255.0f;
    case 2:
        pixmap[i + 1] = result.Green * 255.0f;
    case 1:
        pixmap[i + 0] = result.Red * 255.0f;
    default:
        break;
    }
}

inline void drawGrid(APixmap &pixmap, const Math::IntegerVector &step, const Math::IntegerVector &offset, const AColor &color, const Blending blending = Replace)
{
    AAssert(step.x != 0 && step.y != 0, "Step must be set");
    Math::IntegerVector clampedOffset = Math::IntegerVector{ offset.x % step.x, offset.y % step.y };
    Math::IntegerVector inversedOffset = step - clampedOffset;
    for (size_t y = 0; y < pixmap.getSize().y; ++y)
    {
        if ((y + inversedOffset.y) % step.y == 0)
        {
            for (size_t x = 0; x < pixmap.getSize().x; ++x)
            {
                drawPoint(pixmap, x, y, color, blending);
            }
        }
        else
        {
            for (size_t x = clampedOffset.x; x < pixmap.getSize().x; x += step.x)
            {
                drawPoint(pixmap, x, y, color, blending);
            }
        }
    }
}

inline void drawGrid(APixmap &pixmap, size_t step, size_t offset, const AColor &color, const Blending blending = Replace)
{
    //TODO: fix unsign to sign conversion
	drawGrid(pixmap, { int32_t(step), int32_t(step) }, { int32_t(offset), int32_t(offset) }, color, blending);
}

inline void drawCheck(APixmap &pixmap, const Math::IntegerVector &step, const Math::IntegerVector &offset, const AColor &color, const Blending blending = Replace)
{
    AAssert(step.x != 0 && step.y != 0, "Step must be set");
    Math::IntegerVector step2 = step * 2;
    Math::IntegerVector clampedOffset = Math::IntegerVector{ offset.x % step2.x, offset.y % step2.y };
    Math::IntegerVector inversedOffset = step - clampedOffset;
    for (size_t y = 0; y < pixmap.getSize().y; ++y)
    {
        bool firstRow = (y + inversedOffset.y) % step2.y >= step.y;
        for (int64_t x = firstRow ? clampedOffset.x - (clampedOffset.x > step.x ? step2.x : 0) : (-step.x + clampedOffset.x); x < pixmap.getSize().x; x += step.x)
        {
            const int64_t end = Math::getMin<int64_t>(x + step.x - ((x + inversedOffset.x) % step.x), pixmap.getSize().x);
            for (x = Math::getMax<int64_t>(x, 0); x < end; ++x)
            {
                drawPoint(pixmap, x, y, color, blending);
            }
        }
    }
}

inline void drawCheck(APixmap &pixmap, const Math::IntegerVector &step, const Math::IntegerVector &offset, const AColor &color1, const AColor &color2, const Blending blending = Replace)
{
    AAssert(step.x != 0 && step.y != 0, "Step must be set");

    if (color2.Alpha == 0)
    {
        drawCheck(pixmap, step, step, color2, blending);
        return;
    }
    else if (color1.Alpha == 0)
    {
        drawCheck(pixmap, step, offset + step, color1, blending);
        return;
    }

    Math::IntegerVector step2 = step * 2;
    Math::IntegerVector clampedOffset = Math::IntegerVector{ offset.x % step2.x, offset.y % step2.y };
    Math::IntegerVector inversedOffset = step - clampedOffset;
    for (size_t y = 0; y < pixmap.getSize().y; ++y)
    {
        for (size_t x = 0; x < pixmap.getSize().x; x += step.x)
        {
            const AColor &c = (x + inversedOffset.x) % step2.x < step.x != (y + inversedOffset.y) % step2.y < step.y ? color2 : color1;
            const size_t end = Math::getMin<size_t>(x + step.x, pixmap.getSize().x);
            for (size_t i = x; i < end; ++i)
            {
                drawPoint(pixmap, i, y, c, blending);
            }
        }
    }
}

inline void drawCheck(APixmap &pixmap, size_t step, size_t offset, const AColor &color, const Blending blending = Replace)
{
    //TODO: fix unsign to sign conversion
    drawCheck(pixmap, { int32_t(step), int32_t(step) }, { int32_t(offset), int32_t(offset), }, color, blending);
}

inline void drawCheck(APixmap &pixmap, size_t step, size_t offset, const AColor &color1, const AColor &color2, const Blending blending = Replace)
{
    //TODO: fix unsign to sign conversion
    drawCheck(pixmap, { int32_t(step), int32_t(step) }, { int32_t(offset), int32_t(offset), }, color1, color2, blending);
}