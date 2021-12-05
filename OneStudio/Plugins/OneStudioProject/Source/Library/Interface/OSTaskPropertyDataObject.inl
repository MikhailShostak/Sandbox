//        Author: Insane Team
//          File: OSTaskPropertyDataObject.inl
// Creation date: 01/11/17 04:51:52
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSTaskPropertyDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSTaskPropertyDataObject::fetch()
{
    this->fetchName();
    this->fetchValue();
    this->fetchTask();
}

inline const String &OSTaskPropertyDataObject::getName() const
{
    return this->data.name;
}

inline void OSTaskPropertyDataObject::setName(const String &name)
{
    this->data.name = name;
    this->commitName();
}

inline void OSTaskPropertyDataObject::setName(String &&name)
{
    this->data.name = std::move(name);
    this->commitName();
}

inline void OSTaskPropertyDataObject::fetchName()
{
    this->getContext()->fetchValue<Entity::NameField>(this, this->data.name);
}

inline void OSTaskPropertyDataObject::commitName()
{
    this->getContext()->commitValue<Entity::NameField>(this);
}
inline const String &OSTaskPropertyDataObject::getValue() const
{
    return this->data.value;
}

inline void OSTaskPropertyDataObject::setValue(const String &value)
{
    this->data.value = value;
    this->commitValue();
}

inline void OSTaskPropertyDataObject::setValue(String &&value)
{
    this->data.value = std::move(value);
    this->commitValue();
}

inline void OSTaskPropertyDataObject::fetchValue()
{
    this->getContext()->fetchValue<Entity::ValueField>(this, this->data.value);
}

inline void OSTaskPropertyDataObject::commitValue()
{
    this->getContext()->commitValue<Entity::ValueField>(this);
}
inline const SharedReference<OSTaskDataObject> &OSTaskPropertyDataObject::getTask() const
{
    return this->data.task;
}

inline void OSTaskPropertyDataObject::setTask(const SharedReference<OSTaskDataObject> &task)
{
    this->data.task = task;
    this->commitTask();
}

inline void OSTaskPropertyDataObject::setTask(SharedReference<OSTaskDataObject> &&task)
{
    this->data.task = std::move(task);
    this->commitTask();
}

inline void OSTaskPropertyDataObject::fetchTask()
{
    this->getContext()->fetchValue<Entity::TaskField>(this, this->data.task);
}

inline void OSTaskPropertyDataObject::commitTask()
{
    this->getContext()->commitValue<Entity::TaskField>(this);
}

