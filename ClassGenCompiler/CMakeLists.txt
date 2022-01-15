file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_executable(ClassGenCompiler ${SOURCES})
target_link_libraries(ClassGenCompiler Frameworks)
