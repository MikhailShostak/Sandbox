#pragma once

#include <typeinfo>

class AType final
{

    friend class AMeta;

public:

    const char *getName() const { return typeInfo.name(); }
    std::size_t getHash() const { return typeInfo.hash_code(); }
    const std::type_info &getInfo() const { return typeInfo; }

    bool operator ==(const AType &type) const { return typeInfo == type.typeInfo; }
    bool operator !=(const AType &type) const { return typeInfo != type.typeInfo; }

private:

    constexpr AType(const std::type_info &info):typeInfo(info) {}

    const std::type_info &typeInfo;

};
