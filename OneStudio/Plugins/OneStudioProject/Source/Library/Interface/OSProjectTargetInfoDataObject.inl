//        Author: Insane Team
//          File: OSProjectTargetInfoDataObject.inl
// Creation date: 01/11/17 04:51:52
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSProjectTargetInfoDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSProjectTargetInfoDataObject::fetch()
{
    this->fetchPackage();
    this->fetchProductDirectory();
    this->fetchName();
    this->fetchIntermediateDirectory();
    this->fetchRunningCommand();
    this->fetchRunningArguments();
}

inline const String &OSProjectTargetInfoDataObject::getPackage() const
{
    return this->data.package;
}

inline void OSProjectTargetInfoDataObject::setPackage(const String &package)
{
    this->data.package = package;
    this->commitPackage();
}

inline void OSProjectTargetInfoDataObject::setPackage(String &&package)
{
    this->data.package = std::move(package);
    this->commitPackage();
}

inline void OSProjectTargetInfoDataObject::fetchPackage()
{
    this->getContext()->fetchValue<Entity::PackageField>(this, this->data.package);
}

inline void OSProjectTargetInfoDataObject::commitPackage()
{
    this->getContext()->commitValue<Entity::PackageField>(this);
}
inline const String &OSProjectTargetInfoDataObject::getProductDirectory() const
{
    return this->data.productDirectory;
}

inline void OSProjectTargetInfoDataObject::setProductDirectory(const String &productDirectory)
{
    this->data.productDirectory = productDirectory;
    this->commitProductDirectory();
}

inline void OSProjectTargetInfoDataObject::setProductDirectory(String &&productDirectory)
{
    this->data.productDirectory = std::move(productDirectory);
    this->commitProductDirectory();
}

inline void OSProjectTargetInfoDataObject::fetchProductDirectory()
{
    this->getContext()->fetchValue<Entity::ProductDirectoryField>(this, this->data.productDirectory);
}

inline void OSProjectTargetInfoDataObject::commitProductDirectory()
{
    this->getContext()->commitValue<Entity::ProductDirectoryField>(this);
}
inline const String &OSProjectTargetInfoDataObject::getName() const
{
    return this->data.name;
}

inline void OSProjectTargetInfoDataObject::setName(const String &name)
{
    this->data.name = name;
    this->commitName();
}

inline void OSProjectTargetInfoDataObject::setName(String &&name)
{
    this->data.name = std::move(name);
    this->commitName();
}

inline void OSProjectTargetInfoDataObject::fetchName()
{
    this->getContext()->fetchValue<Entity::NameField>(this, this->data.name);
}

inline void OSProjectTargetInfoDataObject::commitName()
{
    this->getContext()->commitValue<Entity::NameField>(this);
}
inline const String &OSProjectTargetInfoDataObject::getIntermediateDirectory() const
{
    return this->data.intermediateDirectory;
}

inline void OSProjectTargetInfoDataObject::setIntermediateDirectory(const String &intermediateDirectory)
{
    this->data.intermediateDirectory = intermediateDirectory;
    this->commitIntermediateDirectory();
}

inline void OSProjectTargetInfoDataObject::setIntermediateDirectory(String &&intermediateDirectory)
{
    this->data.intermediateDirectory = std::move(intermediateDirectory);
    this->commitIntermediateDirectory();
}

inline void OSProjectTargetInfoDataObject::fetchIntermediateDirectory()
{
    this->getContext()->fetchValue<Entity::IntermediateDirectoryField>(this, this->data.intermediateDirectory);
}

inline void OSProjectTargetInfoDataObject::commitIntermediateDirectory()
{
    this->getContext()->commitValue<Entity::IntermediateDirectoryField>(this);
}


inline const String &OSProjectTargetInfoDataObject::getRunningCommand() const
{
    return this->data.runningCommand;
}

inline void OSProjectTargetInfoDataObject::setRunningCommand(const String &runningCommand)
{
    this->data.runningCommand = runningCommand;
    this->commitRunningCommand();
}

inline void OSProjectTargetInfoDataObject::setRunningCommand(String &&runningCommand)
{
    this->data.runningCommand = std::move(runningCommand);
    this->commitRunningCommand();
}

inline void OSProjectTargetInfoDataObject::fetchRunningCommand()
{
    this->getContext()->fetchValue<Entity::RunningCommandField>(this, this->data.runningCommand);
}

inline void OSProjectTargetInfoDataObject::commitRunningCommand()
{
    this->getContext()->commitValue<Entity::RunningCommandField>(this);
}


inline const String &OSProjectTargetInfoDataObject::getRunningArguments() const
{
    return this->data.runningArguments;
}

inline void OSProjectTargetInfoDataObject::setRunningArguments(const String &runningArguments)
{
    this->data.runningArguments = runningArguments;
    this->commitRunningArguments();
}

inline void OSProjectTargetInfoDataObject::setRunningArguments(String &&runningArguments)
{
    this->data.runningArguments = std::move(runningArguments);
    this->commitRunningArguments();
}

inline void OSProjectTargetInfoDataObject::fetchRunningArguments()
{
    this->getContext()->fetchValue<Entity::RunningArgumentsField>(this, this->data.runningArguments);
}

inline void OSProjectTargetInfoDataObject::commitRunningArguments()
{
    this->getContext()->commitValue<Entity::RunningArgumentsField>(this);
}

