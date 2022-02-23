file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(Input ${SOURCES})
target_include_directories(Input PUBLIC .)
target_precompile_headers(Input PUBLIC Input.pch.hpp)
target_link_libraries(Input PUBLIC ECS)
