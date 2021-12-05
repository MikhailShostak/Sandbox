//        Author: Insane Team
//          File: _OSBuildingOperation.inl
// Creation date: 01/11/17 04:27:46
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const String &OSBuildingOperation::getPackage() const
{
    return this->package;
}

inline void OSBuildingOperation::setPackage(const String &package)
{
    this->package = package;
}

inline void OSBuildingOperation::setPackage(String &&package)
{
    this->package = std::move(package);
}

inline uint64_t OSBuildingOperation::getIndex() const
{
    return this->index;
}

inline void OSBuildingOperation::setIndex(uint64_t index)
{
    this->index = index;
}

inline const String &OSBuildingOperation::getStepType() const
{
    return this->stepType;
}

inline void OSBuildingOperation::setStepType(const String &stepType)
{
    this->stepType = stepType;
}

inline void OSBuildingOperation::setStepType(String &&stepType)
{
    this->stepType = std::move(stepType);
}

