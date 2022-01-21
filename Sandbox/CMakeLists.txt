file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_executable(Sandbox ${SOURCES})
target_include_directories(Sandbox PRIVATE .)
target_precompile_headers(Sandbox PRIVATE Sandbox.pch.hpp)
target_link_libraries(Sandbox Frameworks)
