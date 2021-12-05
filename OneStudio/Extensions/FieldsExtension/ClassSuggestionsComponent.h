#pragma once

#include <Experimental>

//#include "ClassDataInstance.h"
//#include "ClassRepository.h"

namespace UI
{

class ClassSuggestionsComponent : public BaseSuggestionsComponent
{
public:
    String baseType;
    bool findAsset = false;
    bool findTemplates = false;

    void updateSuggestions(const String &text) override
    {
        /*Map<String, SharedReference<LegacyClassGen::ClassDataInstance>> &types = LegacyClassGen::ClassRepository::getInstance().indexedTypes;
        suggestions.clear();
        Array<String> words = text.split(' ');
        for (const APair<String, SharedReference<LegacyClassGen::ClassDataInstance>> &item : types)
        {
            if (findAsset != (item.second->type->group == LegacyClassGen::CGTypeGroup::Asset))
            {
                continue;
            }

            if (baseType && item.second->type->getBaseType() != baseType)
            {
                continue;
            }

            if (findTemplates != item.second->type->data.hasKey("TemplateTypes"))
            {
                continue;
            }

            if (!hasWords(item.first, words))
            {
                continue;
            }

            suggestions.append(item.first);
        }*/
    }
};

}
