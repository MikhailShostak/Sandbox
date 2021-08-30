set(SOURCES
    NativeApplication.cpp
    NativeApplication.hpp
)

add_library(NativeApplication ${SOURCES})
target_include_directories(NativeApplication INTERFACE .)
target_link_libraries(NativeApplication ThirdParty Utils)
