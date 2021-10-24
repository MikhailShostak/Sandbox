add_subdirectory(ClassGen)
add_subdirectory(NativeApplication)
add_subdirectory(UI)
add_subdirectory(Utils)

set(LIBRARIES
    ClassGen
    NativeApplication
    UI
    Utils
)

add_library(Frameworks INTERFACE)
target_precompile_headers(Frameworks INTERFACE Frameworks.pch.hpp)
target_link_libraries(Frameworks INTERFACE ${LIBRARIES})
