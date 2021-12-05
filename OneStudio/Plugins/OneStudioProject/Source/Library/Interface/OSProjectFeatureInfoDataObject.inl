//        Author: Insane Team
//          File: OSProjectFeatureInfoDataObject.inl
// Creation date: 01/11/17 04:51:51
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSProjectFeatureInfoDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSProjectFeatureInfoDataObject::fetch()
{
    this->fetchPackage();
    this->fetchPath();
}

inline const String &OSProjectFeatureInfoDataObject::getPackage() const
{
    return this->data.package;
}

inline void OSProjectFeatureInfoDataObject::setPackage(const String &package)
{
    this->data.package = package;
    this->commitPackage();
}

inline void OSProjectFeatureInfoDataObject::setPackage(String &&package)
{
    this->data.package = std::move(package);
    this->commitPackage();
}

inline void OSProjectFeatureInfoDataObject::fetchPackage()
{
    this->getContext()->fetchValue<Entity::PackageField>(this, this->data.package);
}

inline void OSProjectFeatureInfoDataObject::commitPackage()
{
    this->getContext()->commitValue<Entity::PackageField>(this);
}
inline const String &OSProjectFeatureInfoDataObject::getPath() const
{
    return this->data.path;
}

inline void OSProjectFeatureInfoDataObject::setPath(const String &path)
{
    this->data.path = path;
    this->commitPath();
}

inline void OSProjectFeatureInfoDataObject::setPath(String &&path)
{
    this->data.path = std::move(path);
    this->commitPath();
}

inline void OSProjectFeatureInfoDataObject::fetchPath()
{
    this->getContext()->fetchValue<Entity::PathField>(this, this->data.path);
}

inline void OSProjectFeatureInfoDataObject::commitPath()
{
    this->getContext()->commitValue<Entity::PathField>(this);
}

