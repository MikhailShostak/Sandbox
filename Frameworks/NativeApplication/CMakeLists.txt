set(SOURCES
    NativeApplication.cpp
    NativeApplication.hpp
)

add_library(NativeApplication ${SOURCES})
target_include_directories(NativeApplication INTERFACE .)
target_link_libraries(NativeApplication ThirdParty Utils)

target_compile_definitions(NativeApplication PRIVATE -DENGINE_DLL=0 -DVULKAN_SUPPORTED=1)
if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    target_compile_definitions(NativeApplication PRIVATE -DPLATFORM_MACOS=1 -DGLFW_EXPOSE_NATIVE_COCOA=1)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_compile_definitions(NativeApplication PRIVATE -DPLATFORM_LINUX=1 -DGLFW_EXPOSE_NATIVE_X11=1)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    target_compile_definitions(NativeApplication PRIVATE -DPLATFORM_WIN32=1 -DGLFW_EXPOSE_NATIVE_WIN32=1)
endif()
