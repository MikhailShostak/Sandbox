#pragma once

struct NativeWindowHandle
{
    using This = NativeWindowHandle;
    InplaceStorage<NativeWindowHandleData, 64, 8, false> Data;
    NativeWindowHandle();
    NativeWindowHandle(const NativeWindowHandle &other);
    NativeWindowHandle &operator =(const NativeWindowHandle &other);
    NativeWindowHandle(NativeWindowHandle &&other);
    NativeWindowHandle &operator =(NativeWindowHandle &&other);

     ~NativeWindowHandle();
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
