#pragma once

#define AReleaseBuild 0
#define ADebugBuild 0
#define ATestBuild 0

#if defined(NDEBUG)
    #if defined(NTEST)
        #undef AReleaseBuild
        #define AReleaseBuild 1
    #else
        #undef ATestBuild
        #define ATestBuild 1
    #endif
#else
    #undef ADebugBuild
    #define ADebugBuild 1
#endif

#define APlatformWindowsDesktop 0
#define APlatformWindowsDesktop32 0
#define APlatformWindowsDesktop64 0
#define APlatformWindowsDesktopMinGW 0
#define APlatformWindowsDesktopMSVC 0
#define APlatformArm 0
#define APlatformLinux 0
#define APlatformUnix 0
#define APlatformPosix 0
#define APlatformAndroid 0
#define APlatformApple 0
#define APlatformOSX 0
#define APlatformIOS 0
#define APlatformIOSDevice 0
#define APlatformIOSSimulator 0

#if defined(__WIN32__) || defined(_WIN32)
    #undef APlatformWindowsDesktop
    #define APlatformWindowsDesktop 1
    #undef APlatformWindowsDesktop32
    #define APlatformWindowsDesktop32 1
#endif

#if defined(__WIN64__) || defined(_WIN64)
    #undef APlatformWindowsDesktop
    #define APlatformWindowsDesktop 1
    #undef APlatformWindowsDesktop64
    #define APlatformWindowsDesktop64 1
#endif

#if APlatformWindowsDesktop
    #if defined(__MINGW32__)
        #undef APlatformWindowsDesktopMinGW
        #define APlatformWindowsDesktopMinGW 1
        #undef APlatformWindowsDesktopMinGW32
        #define APlatformWindowsDesktopMinGW32 1
    #elif defined(__MINGW64__)
        #undef APlatformWindowsDesktopMinGW
        #define APlatformWindowsDesktopMinGW 1
        #undef APlatformWindowsDesktopMinGW64
        #define APlatformWindowsDesktopMinGW64 1
    #elif defined(_MSC_VER)
        #undef APlatformWindowsDesktopMSVC
        #define APlatformWindowsDesktopMSVC 1
    #endif
#endif

#if defined(__APPLE__) || defined(__MACH__)
    #undef APlatformUnix
    #define APlatformUnix 1
    #undef APlatformPosix
    #define APlatformPosix 1
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #undef APlatformApple
        #define APlatformApple 1
        #undef APlatformOSX
        #define APlatformOSX 1
    #elif TARGET_OS_IPHONE
        #undef APlatformApple
        #define APlatformApple 1
        #undef APlatformIOS
        #define APlatformIOS 1
        #undef APlatformIOSDevice
        #define APlatformIOSDevice 1
    #elif TARGET_IPHONE_SIMULATOR
        #undef APlatformApple
        #define APlatformApple 1
        #undef APlatformIOS
        #define APlatformIOS 1
        #undef APlatformIOSSimulator
        #define APlatformIOSSimulator 1
    #endif
#endif

#ifdef __ANDROID__
    #undef APlatformAndroid
    #define APlatformAndroid 1
    #include <android/api-level.h>
    #define APlatformAndroidSDK __ANDROID_API__
#endif

#if defined(linux) || defined(__linux__) || defined(__linux)
    #undef APlatformLinux
    #define APlatformLinux 1
#endif

#if defined(unix) || defined(__unix__) || defined(__unix)
    #undef APlatformUnix
    #define APlatformUnix 1
#endif

#if defined(posix) || defined(__posix__) || defined(__posix)
    #undef APlatformPosix
    #define APlatformPosix 1
#endif

#if APlatformWindowsDesktopMSVC
    #define AFunctionSignature __FUNCSIG__
#else
    #define AFunctionSignature __PRETTY_FUNCTION__
#endif
