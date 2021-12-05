file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(NodeEditor ${SOURCES})
target_include_directories(NodeEditor PUBLIC .)
target_link_libraries(NodeEditor ClassGenLibrary OneStudioPlatform)
