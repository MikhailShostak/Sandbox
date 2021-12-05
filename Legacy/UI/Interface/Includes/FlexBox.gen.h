#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Foundation"
#include "FlexBoxData.gen.h"
#include "Direction.gen.h"
#include "Math"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class FlexBox : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FlexBox This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    Array<UI::FlexBoxData> Data;
UI::Direction Direction;
SignedInteger Spacing;
Math::Offsets Padding;
public:
    FlexBox();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<UI::FlexBoxData> getData() const;
    void setData(Array<UI::FlexBoxData> const &Data);
    void setData(Array<UI::FlexBoxData> &&Data);
    UI::Direction getDirection() const;
    void setDirection(UI::Direction const &Direction);
    void setDirection(UI::Direction &&Direction);
    SignedInteger getSpacing() const;
    void setSpacing(SignedInteger const &Spacing);
    void setSpacing(SignedInteger &&Spacing);
    Math::Offsets getPadding() const;
    void setPadding(Math::Offsets const &Padding);
    void setPadding(Math::Offsets &&Padding);
//CLASSGEN END REGION
    void addData(UI::FlexBoxData const &data) { Data.push_back(data); }
    void insertDataAt(UI::FlexBoxData const &data, size_t index) { Data.insert(Data.begin() + index, data); }
    void removeDataAt(size_t index) { Data.erase(Data.begin() + index); }
public:
    Math::IntegerVector getContentSize() const override;
protected:
    void onLayout(AUpdateEvent &event) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
