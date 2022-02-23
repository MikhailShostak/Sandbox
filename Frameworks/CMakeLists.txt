add_subdirectory(ClassGen)
add_subdirectory(Core)
add_subdirectory(ECS)
add_subdirectory(Graphics)
add_subdirectory(ImGuiIntegration)
add_subdirectory(Input)
add_subdirectory(NativeApplication)
add_subdirectory(SystemExtension)
add_subdirectory(UI)
add_subdirectory(Utils)

set(LIBRARIES
    ClassGen
    Core
    ECS
    Graphics
    ImGuiIntegration
    Input
    NativeApplication
    SystemExtension
    UI
    Utils
)

add_library(Frameworks INTERFACE)
target_include_directories(Frameworks INTERFACE .)
target_precompile_headers(Frameworks INTERFACE Frameworks.pch.hpp)
target_link_libraries(Frameworks INTERFACE ${LIBRARIES})
