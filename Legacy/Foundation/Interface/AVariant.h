#pragma once

#include "AMeta.h"

class AVariant final
{

    friend std::ostream &operator<<(std::ostream &stream, const AVariant &variant);

public:

    static const AVariant &EmptyVariant()
    {
        static AVariant emptyVariant;
        return emptyVariant;
    }

    AVariant() {}

    AVariant(const AVariant &variant);
    AVariant(AVariant &&variant);

    template<typename Type>
    AVariant(Type &&value);

    template<size_t size>
    AVariant(const char (&string)[size]);

    bool isEmpty() const { return data == nullptr; }
    bool isValid() const { return data != nullptr; }

    template<typename Type>
    Type &asValue();

    template<typename Type>
    const Type &asValue() const;

    template<typename Type>
    bool isValue() const;

    template<typename Type>
    Type toValue() const;

    void setValue(const AVariant &variant);
    void setValue(AVariant &&variant);

    template<typename Type>
    void setValue(Type &&value);

    template<size_t size>
    void setValue(const char (&string)[size]);

    void setValue(std::nullptr_t) { clear(); }

    bool operator ==(const AVariant &variant) const;
    bool operator !=(const AVariant &variant) const;

    void clear()
    {
        data.reset();
    }

    AVariant &operator =(const AVariant &variant);
    AVariant &operator =(AVariant &&variant);
    
    template<typename Type>
    AVariant &operator =(Type &&value) { setValue(std::forward<Type>(value)); return *this; }

    AVariant &operator =(std::nullptr_t) { clear(); return *this; }

private:

    class AVariantData
    {
    public:
        using This = AVariantData;
        using TypeInfo = std::type_info;
        virtual ~AVariantData() {}
        virtual const AType &getType() const = 0;
        virtual UniqueReference<AVariantData> copy() const = 0;
        const char *getTypeName() const { return getType().getName(); }
        size_t getTypeHash() const { return getType().getHash(); }
    };

    template<typename Type>
    class AVariantValueData : public AVariantData
    {
        Type data;
    public:
        using This = AVariantValueData<Type>;
        using Super = AVariantData;
        AVariantValueData(const Type &value): AVariantData(), data(value) {}
        AVariantValueData(Type &&value): AVariantData(), data(std::move(value)) {}
        Type &getValue() { return data; }
        const Type &getValue() const { return data; }
        virtual const AType &getType() const { return AMeta::getStaticType<Type>(); }
        virtual UniqueReference<AVariantData> copy() const { return std::make_unique<AVariantValueData<Type>>(data); }
    };

    UniqueReference<AVariantData> data;
};

inline AVariant::AVariant(const AVariant &variant)
{
    if (variant.data)
    {
        data = variant.data->copy();
    }
}

inline AVariant::AVariant(AVariant &&variant)
{
    if (variant.data)
    {
        data = std::move(variant.data);
    }
}

inline AVariant &AVariant::operator =(const AVariant &variant)
{
    if (variant.data)
    {
        data = variant.data->copy();
    }
    else
    {
        clear();
    }

    return *this;
}

inline AVariant &AVariant::operator =(AVariant &&variant)
{
    if (variant.data)
    {
        data = std::move(variant.data);
    }
    else
    {
        clear();
    }

    return *this;
}

template<typename Type>
inline AVariant::AVariant(Type &&value)
{
    setValue(std::forward<Type>(value));
}

template<size_t size>
inline AVariant::AVariant(const char (&string)[size])
{
    setValue(string);
}

template<typename Type>
inline Type &AVariant::asValue()
{
    AAssert(data, "Bad access, variant is null");
    AAssert(data->getType() == AMeta::getStaticType<Type>(), "The variant type(%s) is not the same type(%s)", data->getType().getName(), AMeta::getStaticTypeName<Type>());
    return static_cast<AVariantValueData<Type> *>(data.get())->getValue();
}

template<typename Type>
inline const Type &AVariant::asValue() const
{
    AAssert(data, "Bad access, variant is null");
    AAssert(data->getType() == AMeta::getStaticType<Type>(), "The variant type(%s) is not the same type(%s)", data->getType().getName(), AMeta::getStaticTypeName<Type>());
    return static_cast<AVariantValueData<Type> *>(data.get())->getValue();
}

template<typename Type>
inline bool AVariant::isValue() const
{
    if(data)
        return AMeta::getStaticType<Type>() == data->getType();
    return false;
}

template<typename Type>
inline Type AVariant::toValue() const
{
    if(data->getType() == AMeta::getStaticType<Type>())
        return StaticCast<AVariantValueData<Type>>(data.get())->getValue();
    return Type();
}

inline void AVariant::setValue(const AVariant &variant)
{
    if (data)
    {
        data.reset();
    }

    if (variant.data)
    {
        data = variant.data->copy();
    }
    else
    {
        data.reset();
    }
}

inline void AVariant::setValue(AVariant &&variant)
{
    if (data)
    {
        data.reset();
    }

    if(variant.data)
    {
        data = std::move(variant.data);
    }
    else
    {
        data.reset();
    }
}

template<typename Type>
inline void AVariant::setValue(Type &&value)
{
    data = std::make_unique<AVariantValueData<std::remove_const<std::remove_reference<Type>::type>::type>>(std::forward<Type>(value));
}

template<size_t size>
inline void AVariant::setValue(const char (&string)[size])
{
    data = std::make_unique<AVariantValueData<String>>(string);
}

inline bool AVariant::operator ==(const AVariant &variant) const
{
    if (data && variant.data)
    {
        return data->getType() == variant.data->getType();
    }
    else
    {
        if (!data && !variant.data)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

inline bool AVariant::operator !=(const AVariant &variant) const
{
    return !(*this == variant);
}
