//        Author: Insane Team
//          File: _OSBuildingOperation.h
// Creation date: 01/11/17 04:27:46
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <AFoundation>
#include <cstdint>

//       Class: OSBuildingOperation
//        Base: AOperation
//        Link: 
// Description: 

class OSBuildingOperation : public AOperation
{
    typedef OSBuildingOperation This;
    typedef AOperation Super;

    String package;
    uint64_t index;
    String stepType;

public:
    virtual ~OSBuildingOperation() {}

public:
    virtual const String &getPackage() const;
    virtual void setPackage(const String &package);
    virtual void setPackage(String &&package);

public:
    virtual uint64_t getIndex() const;
    virtual void setIndex(uint64_t index);

public:
    virtual const String &getStepType() const;
    virtual void setStepType(const String &stepType);
    virtual void setStepType(String &&stepType);
};


