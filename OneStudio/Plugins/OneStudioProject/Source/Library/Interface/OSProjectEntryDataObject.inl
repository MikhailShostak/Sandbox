//        Author: Insane Team
//          File: OSProjectEntryDataObject.inl
// Creation date: 01/11/17 04:51:51
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSProjectEntryDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSProjectEntryDataObject::fetch()
{
    this->fetchPackage();
    this->fetchPath();
}

inline const String &OSProjectEntryDataObject::getPackage() const
{
    return this->data.package;
}

inline void OSProjectEntryDataObject::setPackage(const String &package)
{
    this->data.package = package;
    this->commitPackage();
}

inline void OSProjectEntryDataObject::setPackage(String &&package)
{
    this->data.package = std::move(package);
    this->commitPackage();
}

inline void OSProjectEntryDataObject::fetchPackage()
{
    this->getContext()->fetchValue<Entity::PackageField>(this, this->data.package);
}

inline void OSProjectEntryDataObject::commitPackage()
{
    this->getContext()->commitValue<Entity::PackageField>(this);
}
inline const String &OSProjectEntryDataObject::getPath() const
{
    return this->data.path;
}

inline void OSProjectEntryDataObject::setPath(const String &path)
{
    this->data.path = path;
    this->commitPath();
}

inline void OSProjectEntryDataObject::setPath(String &&path)
{
    this->data.path = std::move(path);
    this->commitPath();
}

inline void OSProjectEntryDataObject::fetchPath()
{
    this->getContext()->fetchValue<Entity::PathField>(this, this->data.path);
}

inline void OSProjectEntryDataObject::commitPath()
{
    this->getContext()->commitValue<Entity::PathField>(this);
}

