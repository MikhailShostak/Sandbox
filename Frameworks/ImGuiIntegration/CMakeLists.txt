file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(ImGuiIntegration ${SOURCES})
target_include_directories(ImGuiIntegration PUBLIC .)
target_precompile_headers(ImGuiIntegration PUBLIC ImGuiIntegration.pch.hpp)
target_link_libraries(ImGuiIntegration PUBLIC Graphics)
