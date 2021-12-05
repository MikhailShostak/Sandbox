#pragma once

#include "String.h"

class AError
{

    uint64_t errorCode = 0;
    String message;

public:

    static const AError &getEmptyError()
    {
        static AError error;
        return error;
    }

    AError() {}

    AError(const uint64_t &errorCode, const String &message):
        errorCode(errorCode),
        message(message)
    {

    }

    uint64_t getErrorCode() const { return errorCode; }
    String getMessage() const { return message; }

    bool isValid() const { return errorCode != 0; }
    explicit operator bool() const { return errorCode != 0; }

};
