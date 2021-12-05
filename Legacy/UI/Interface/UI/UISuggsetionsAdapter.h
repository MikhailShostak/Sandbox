#pragma once

#include "Includes/View.gen.h"

namespace UI
{

class SuggestionsAdapter
{
public:
    virtual void requestSuggestions(const String &text) = 0;
    virtual SharedReference<View> getView() const = 0;
};

}