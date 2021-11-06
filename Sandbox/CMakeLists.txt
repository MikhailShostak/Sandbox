file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_executable(Sandbox ${SOURCES})
target_link_libraries(Sandbox Frameworks)
