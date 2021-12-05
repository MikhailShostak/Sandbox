#pragma once

#include "String.h"

class AMIMETypeDataBase
{
public:



};

class AMIMEType
{

    String contentType;
    String parentType;

public:

    AMIMEType(const String &contentType = String(), const String &parentType = "text/plain"):
        contentType(contentType),
        parentType(parentType)
    {}

    const String &getContentType() const
    {
        return contentType;
    }

    const String &getParentType() const
    {
        return parentType;
    }

};
