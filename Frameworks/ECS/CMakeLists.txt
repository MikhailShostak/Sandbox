file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(ECS ${SOURCES})
target_include_directories(ECS PUBLIC .)
target_precompile_headers(ECS PUBLIC ECS.pch.hpp)
target_link_libraries(ECS PUBLIC Graphics ImGuiIntegration)
