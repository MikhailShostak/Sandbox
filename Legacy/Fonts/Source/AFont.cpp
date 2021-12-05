#include "AFont.h"

namespace Core
{

void Font::reload()
{
    auto &engine = FontEngine::getInstance();
    FontEngine::FontMap::iterator font = engine._fonts.find(_family);
    if (font == engine._fonts.end())
    {
        ALogError("Font", "Family \"%s\" not found", _family.data());
        return;
    }

    FontEngine::DataMap::iterator data = font->second.find(_style);
    if (data == font->second.end())
    {
        ALogError("Font", "Style \"%s\" in family \"%s\" not found", _style.data(), _family.data());
    }
    else
    {
        _chache = data->second->chache(_size);
    }
}

}
