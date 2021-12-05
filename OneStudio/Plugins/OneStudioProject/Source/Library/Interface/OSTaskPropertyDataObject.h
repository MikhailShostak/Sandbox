//        Author: Insane Team
//          File: OSTaskPropertyDataObject.h
// Creation date: 01/11/17 04:50:15
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <Data>
#include <Foundation>

#include "OSTaskDataObject.h"

//       Class: OSTaskPropertyDataObject
//        Base: ADataObject
//        Link: 
// Description: 

class OSTaskPropertyDataObject : public ADataObject
{
public:
    typedef OSTaskPropertyDataObject This;
    typedef ADataObject Super;
    typedef class OSTaskPropertyDataObjectEntity Entity;

    struct Data
    {
        String name;
        String value;
        SharedReference<OSTaskDataObject> task;
    };

private:
    Data data;

public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    void fetch() override;

public:
    const String &getName() const;
    void setName(const String &name);
    void setName(String &&name);
    void fetchName();
private:
    void commitName();

public:
    const String &getValue() const;
    void setValue(const String &value);
    void setValue(String &&value);
    void fetchValue();
private:
    void commitValue();

public:
    const SharedReference<OSTaskDataObject> &getTask() const;
    void setTask(const SharedReference<OSTaskDataObject> &task);
    void setTask(SharedReference<OSTaskDataObject> &&task);
    void fetchTask();
private:
    void commitTask();
};

class OSTaskPropertyDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;

    static String NameFieldName;
    static String ValueFieldName;
    static String TaskFieldName;

public:
    typedef OSTaskPropertyDataObject DataType;

    static const String &getNameFieldName();
    typedef StringDataField<DataType, NameFieldName, &OSTaskPropertyDataObject::getName, &OSTaskPropertyDataObject::setName> NameField;

    static const String &getValueFieldName();
    typedef StringDataField<DataType, ValueFieldName, &OSTaskPropertyDataObject::getValue, &OSTaskPropertyDataObject::setValue> ValueField;

    static const String &getTaskFieldName();
    typedef AEntityDataField<DataType, SharedReference<OSTaskDataObject>, TaskFieldName, &OSTaskPropertyDataObject::getTask, &OSTaskPropertyDataObject::setTask> TaskField;
};

