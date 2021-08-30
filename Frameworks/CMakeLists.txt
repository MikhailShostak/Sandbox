add_subdirectory(NativeApplication)
add_subdirectory(Utils)

set(LIBRARIES
    NativeApplication
    Utils
)

add_library(Frameworks INTERFACE)
target_precompile_headers(Frameworks INTERFACE Frameworks.pch.hpp)
target_link_libraries(Frameworks INTERFACE ${LIBRARIES})
