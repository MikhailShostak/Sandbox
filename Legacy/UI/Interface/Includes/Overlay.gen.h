#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Foundation"
#include "OverlayData.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Overlay : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Overlay This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    Array<UI::OverlayData> Data;
public:
    Overlay();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<UI::OverlayData> getData() const;
    void setData(Array<UI::OverlayData> const &Data);
    void setData(Array<UI::OverlayData> &&Data);
//CLASSGEN END REGION
    void addData(UI::OverlayData const &data) { Data.push_back(data); }
    void insertDataAt(UI::OverlayData const &data, size_t index) { Data.insert(Data.begin() + index, data); }
    void removeDataAt(size_t index) { Data.erase(Data.begin() + index); }
    Math::IntegerVector getContentSize() const override;
    void onLayout(AUpdateEvent &event) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
