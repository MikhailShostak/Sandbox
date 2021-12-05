#pragma once

inline const ADataEntity &OSTaskDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSTaskDataObject::fetch()
{
    this->fetchPackage();
    this->fetchIndex();
    this->fetchStepType();
    this->fetchDescription();
}

inline const String &OSTaskDataObject::getPackage() const
{
    return this->data.package;
}

inline void OSTaskDataObject::setPackage(const String &package)
{
    this->data.package = package;
    this->commitPackage();
}

inline void OSTaskDataObject::setPackage(String &&package)
{
    this->data.package = std::move(package);
    this->commitPackage();
}

inline void OSTaskDataObject::fetchPackage()
{
    this->getContext()->fetchValue<Entity::PackageField>(this, this->data.package);
}

inline void OSTaskDataObject::commitPackage()
{
    this->getContext()->commitValue<Entity::PackageField>(this);
}

inline uint64_t OSTaskDataObject::getIndex() const
{
    return this->data.index;
}

inline void OSTaskDataObject::setIndex(uint64_t index)
{
    this->data.index = index;
    this->commitIndex();
}

inline void OSTaskDataObject::fetchIndex()
{
    this->getContext()->fetchValue<Entity::IndexField>(this, this->data.index);
}

inline void OSTaskDataObject::commitIndex()
{
    this->getContext()->commitValue<Entity::IndexField>(this);
}

inline const String &OSTaskDataObject::getStepType() const
{
    return this->data.stepType;
}

inline void OSTaskDataObject::setStepType(const String &stepType)
{
    this->data.stepType = stepType;
    this->commitStepType();
}

inline void OSTaskDataObject::setStepType(String &&stepType)
{
    this->data.stepType = std::move(stepType);
    this->commitStepType();
}

inline void OSTaskDataObject::fetchStepType()
{
    this->getContext()->fetchValue<Entity::StepTypeField>(this, this->data.stepType);
}

inline void OSTaskDataObject::commitStepType()
{
    this->getContext()->commitValue<Entity::StepTypeField>(this);
}

inline const String &OSTaskDataObject::getDescription() const
{
    return this->data.description;
}

inline void OSTaskDataObject::setDescription(const String &description)
{
    this->data.description = description;
    this->commitDescription();
}

inline void OSTaskDataObject::setDescription(String &&description)
{
    this->data.description = std::move(description);
    this->commitDescription();
}

inline void OSTaskDataObject::fetchDescription()
{
    this->getContext()->fetchValue<Entity::DescriptionField>(this, this->data.description);
}

inline void OSTaskDataObject::commitDescription()
{
    this->getContext()->commitValue<Entity::DescriptionField>(this);
}

