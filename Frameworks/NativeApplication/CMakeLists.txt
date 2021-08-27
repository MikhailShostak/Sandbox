set(SOURCES
    NativeApplication.cpp
    NativeApplication.hpp
)

if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    if(NOT IOS)
        list(APPEND SOURCES CocoaUtils.mm)
        set_source_files_properties(CocoaUtils.mm PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
    endif()
endif()

add_library(NativeApplication ${SOURCES})
target_include_directories(NativeApplication INTERFACE .)
target_link_libraries(NativeApplication ThirdParty Utils)

target_compile_definitions(NativeApplication PRIVATE -DENGINE_DLL=0 -DVULKAN_SUPPORTED=1)
if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    if(NOT IOS)
        target_compile_definitions(NativeApplication PRIVATE -DGLFW_EXPOSE_NATIVE_COCOA=1)
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_compile_definitions(NativeApplication PRIVATE -DPLATFORM_LINUX=1 -DGLFW_EXPOSE_NATIVE_X11=1)
elseif(CMAKE_SYSTEM_NAME STREQUAL Android)
    target_compile_definitions(NativeApplication PRIVATE -DPLATFORM_ANDROID=1)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    target_compile_definitions(NativeApplication PRIVATE -DPLATFORM_WIN32=1 -DGLFW_EXPOSE_NATIVE_WIN32=1)
endif()
