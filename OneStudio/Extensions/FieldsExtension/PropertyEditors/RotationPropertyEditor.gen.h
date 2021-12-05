#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class RotationPropertyEditor : public UI::FlexBox, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef RotationPropertyEditor This;
    typedef UI::FlexBox Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    RotationPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::DropDownList> type;
    SharedReference<UI::TextField> x;
    SharedReference<UI::TextField> y;
    SharedReference<UI::TextField> z;
    void onHierarchyCreate();
//CLASSGEN END REGION
    AJSONValue value;
    Math::Quaternion rotation;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        type->setElements({ "XYZ", "XZY", "YXZ", "YZX", "ZXY", "ZYX" });
        type->setCurrentIndex(5);

        type->eventChannel.registerDelegate([this](UI::CurrentIndexChangedEvent &event) {
            notifyValueChange();
        });

        x->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            notifyValueChange();
        });

        y->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            notifyValueChange();
        });

        z->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            notifyValueChange();
        });
    }

    void onSerialize(const AJSONValue &value) override
    {
        fromJSONValue(value, rotation);

        type->setElements({ "XYZ", "XZY", "YXZ", "YZX", "ZXY", "ZYX" });
        type->setCurrentIndex(5);

        float roll, pitch, yaw;

        // roll (x-axis rotation)
        double sinr_cosp = +2.0 * (rotation.w * rotation.x + rotation.y * rotation.z);
        double cosr_cosp = +1.0 - 2.0 * (rotation.x * rotation.x + rotation.y * rotation.y);
        roll = atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = +2.0 * (rotation.w * rotation.y - rotation.z * rotation.x);
        if (fabs(sinp) >= 1)
            pitch = copysign(Math::Constants::Pi / 2, sinp); // use 90 degrees if out of range
        else
            pitch = asin(sinp);

        // yaw (z-axis rotation)
        double siny_cosp = +2.0 * (rotation.w * rotation.z + rotation.x * rotation.y);
        double cosy_cosp = +1.0 - 2.0 * (rotation.y * rotation.y + rotation.z * rotation.z);
        yaw = atan2(siny_cosp, cosy_cosp);

        x->setText(Str::ToString(roll * Math::Constants::RadiansToDegreeRatio));
        y->setText(Str::ToString(pitch * Math::Constants::RadiansToDegreeRatio));
        z->setText(Str::ToString(yaw * Math::Constants::RadiansToDegreeRatio));
    }

    AJSONValue onDeserialize() override
    {
        rotation = Math::Quaternion::getEulerRotation(
            !x->getText().empty() ? Str::To<float>(x->getText()) : 0.0f,
            !y->getText().empty() ? Str::To<float>(y->getText()) : 0.0f,
            !z->getText().empty() ? Str::To<float>(z->getText()) : 0.0f,
            type->getCurrentIndex() != -1 ? Math::RotationOrder(type->getElements()[type->getCurrentIndex()]) : Math::RotationOrder(Math::RotationOrder::ZYX));
        return toJSONValue(rotation);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
