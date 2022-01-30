file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(Core ${SOURCES})
target_include_directories(Core PUBLIC .)
target_precompile_headers(Core PUBLIC Core.pch.hpp)
target_link_libraries(Core Graphics)
