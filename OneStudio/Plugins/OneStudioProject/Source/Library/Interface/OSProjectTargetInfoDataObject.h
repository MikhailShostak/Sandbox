//        Author: Insane Team
//          File: OSProjectTargetInfoDataObject.h
// Creation date: 01/11/17 04:50:15
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <Data>
#include <Foundation>

//       Class: OSProjectTargetInfoDataObject
//        Base: ADataObject
//        Link: 
// Description: 

class OSProjectTargetInfoDataObject : public ADataObject
{
public:
    typedef OSProjectTargetInfoDataObject This;
    typedef ADataObject Super;
    typedef class OSProjectTargetInfoDataObjectEntity Entity;

    struct Data
    {
        String package;
        String productDirectory;
        String name;
        String intermediateDirectory;
        String runningCommand;
        String runningArguments;
    };

private:
    Data data;

public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    void fetch() override;

public:
    const String &getPackage() const;
    void setPackage(const String &package);
    void setPackage(String &&package);
    void fetchPackage();
private:
    void commitPackage();

public:
    const String &getProductDirectory() const;
    void setProductDirectory(const String &productDirectory);
    void setProductDirectory(String &&productDirectory);
    void fetchProductDirectory();
private:
    void commitProductDirectory();

public:
    const String &getName() const;
    void setName(const String &name);
    void setName(String &&name);
    void fetchName();
private:
    void commitName();

public:
    const String &getIntermediateDirectory() const;
    void setIntermediateDirectory(const String &intermediateDirectory);
    void setIntermediateDirectory(String &&intermediateDirectory);
    void fetchIntermediateDirectory();
private:
    void commitIntermediateDirectory();

public:
    const String &getRunningCommand() const;
    void setRunningCommand(const String &runningCommand);
    void setRunningCommand(String &&runningCommand);
    void fetchRunningCommand();
private:
    void commitRunningCommand();

public:
    const String &getRunningArguments() const;
    void setRunningArguments(const String &runningArguments);
    void setRunningArguments(String &&runningArguments);
    void fetchRunningArguments();
private:
    void commitRunningArguments();
};

class OSProjectTargetInfoDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;

    static String PackageFieldName;
    static String ProductDirectoryFieldName;
    static String NameFieldName;
    static String IntermediateDirectoryFieldName;
    static String RunningCommandFieldName;
    static String RunningArgumentsFieldName;

public:
    typedef OSProjectTargetInfoDataObject DataType;

    static const String &getPackageFieldName();
    typedef StringDataField<DataType, PackageFieldName, &OSProjectTargetInfoDataObject::getPackage, &OSProjectTargetInfoDataObject::setPackage> PackageField;

    static const String &getProductDirectoryFieldName();
    typedef StringDataField<DataType, ProductDirectoryFieldName, &OSProjectTargetInfoDataObject::getProductDirectory, &OSProjectTargetInfoDataObject::setProductDirectory> ProductDirectoryField;

    static const String &getNameFieldName();
    typedef StringDataField<DataType, NameFieldName, &OSProjectTargetInfoDataObject::getName, &OSProjectTargetInfoDataObject::setName> NameField;

    static const String &getIntermediateDirectoryFieldName();
    typedef StringDataField<DataType, IntermediateDirectoryFieldName, &OSProjectTargetInfoDataObject::getIntermediateDirectory, &OSProjectTargetInfoDataObject::setIntermediateDirectory> IntermediateDirectoryField;
    
    static const String &getRunningCommandFieldName();
    typedef StringDataField<DataType, RunningCommandFieldName, &OSProjectTargetInfoDataObject::getRunningCommand, &OSProjectTargetInfoDataObject::setRunningCommand> RunningCommandField;
    
    static const String &getRunningArgumentsFieldName();
    typedef StringDataField<DataType, RunningArgumentsFieldName, &OSProjectTargetInfoDataObject::getRunningArguments, &OSProjectTargetInfoDataObject::setRunningArguments> RunningArgumentsField;
};

