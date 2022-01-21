#include <NativeWindow.h>

struct NativeWindowHandleData
{
    Diligent::NativeWindow NativeWindow;
    struct GLFWwindow* Window = nullptr;
};

struct GLFWwindow *&GetWindowHandle(NativeWindowHandle& Handle) { return Handle.Data->Window; }

NativeWindowHandle::NativeWindowHandle() = default;
NativeWindowHandle::NativeWindowHandle(const NativeWindowHandle& other) = default;
NativeWindowHandle& NativeWindowHandle::operator =(const NativeWindowHandle& other) = default;
NativeWindowHandle::NativeWindowHandle(NativeWindowHandle&& other) = default;
NativeWindowHandle& NativeWindowHandle::operator =(NativeWindowHandle&& other) = default;
NativeWindowHandle::~NativeWindowHandle() = default;
