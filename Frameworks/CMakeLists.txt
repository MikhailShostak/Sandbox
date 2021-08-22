add_subdirectory(NativeApplication)

set(LIBRARIES
    NativeApplication
)

add_library(Frameworks INTERFACE)
target_precompile_headers(Frameworks INTERFACE Frameworks.pch.hpp)
target_link_libraries(Frameworks INTERFACE ${LIBRARIES})
