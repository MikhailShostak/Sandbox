#pragma once

#include "UI/UIDialogLayout.g.h"

namespace UI
{

class DialogView : public View
{
CLASSGEN_GENERATED_REGION_OBJECT
public:
    typedef DialogView This;
    typedef View Super;
private:
    Array<String> buttons;
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual AColor getColor() const;
    virtual void setColor(AColor const &color);
    virtual UIOffsets getBorder() const;
    virtual void setBorder(UIOffsets const &border);
    virtual SharedReference<Legacy::Graphics::Texture> getImage() const;
    virtual void setImage(SharedReference<Legacy::Graphics::Texture> const &image);
    virtual String getTitle() const;
    virtual void setTitle(String const &title);
    virtual Array<String> getButtons() const;
    virtual void setButtons(Array<String> const &buttons);
CLASSGEN_END_REGION
    DialogLayout *dialogLayout = new DialogLayout(*this);
public:
    DialogView();
};

}
