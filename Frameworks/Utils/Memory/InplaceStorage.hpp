#pragma once

template<typename Type, std::size_t Size, std::size_t Alignment, bool StrictSize = true>
class InplaceStorage
{
public:

    template<typename ...Args>
    explicit InplaceStorage(Args &&...args)
    {
        new (&m_Storage) Type(std::forward<Args>(args)...);
    }

    InplaceStorage(const InplaceStorage &value):
        InplaceStorage(value.StorageCast())
    {

    }

    InplaceStorage(InplaceStorage &&value) noexcept:
        InplaceStorage(std::move(value.StorageCast()))
    {

    }

    ~InplaceStorage() noexcept
    {
        MustBe<sizeof(Type), alignof(Type)>();
        StorageCast().~Type();
    }

    InplaceStorage &operator =(const InplaceStorage &value)
    {
        StorageCast() = value.StorageCast();
        return *this;
    }

    InplaceStorage &operator =(InplaceStorage &&value) noexcept
    {
        StorageCast() = std::move(value.StorageCast());
        return *this;
    }

    Type* operator->() noexcept { return &StorageCast(); }
    const Type* operator->() const noexcept { return &StorageCast(); }

    Type& operator*() noexcept { return StorageCast(); }
    const Type& operator*() const noexcept { return StorageCast(); }

private:

    template<std::size_t TypeSize, std::size_t TypeAlignment>
    constexpr static void MustBe() noexcept
    {
        static_assert(StrictSize && TypeSize == Size || !StrictSize && TypeSize <= Size, "InplaceStorage<Type> size mismatch");
        static_assert(TypeAlignment == Alignment, "InplaceStorage<Type> alignment mismatch");
    }

    Type &StorageCast() noexcept { return reinterpret_cast<Type &>(m_Storage); }
    const Type &StorageCast() const noexcept { return reinterpret_cast<const Type &>(m_Storage); }

    std::aligned_storage_t<Size, Alignment> m_Storage;
};
