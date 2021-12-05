//        Author: Insane Team
//          File: _OSCompilationOperation.inl
// Creation date: 01/11/17 04:27:46
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const String &OSCompilationOperation::getPackage() const
{
    return this->package;
}

inline void OSCompilationOperation::setPackage(const String &package)
{
    this->package = package;
}

inline void OSCompilationOperation::setPackage(String &&package)
{
    this->package = std::move(package);
}

inline uint64_t OSCompilationOperation::getIndex() const
{
    return this->index;
}

inline void OSCompilationOperation::setIndex(uint64_t index)
{
    this->index = index;
}

inline const String &OSCompilationOperation::getStepType() const
{
    return this->stepType;
}

inline void OSCompilationOperation::setStepType(const String &stepType)
{
    this->stepType = stepType;
}

inline void OSCompilationOperation::setStepType(String &&stepType)
{
    this->stepType = std::move(stepType);
}

