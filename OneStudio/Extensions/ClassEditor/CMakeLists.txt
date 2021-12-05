file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(ClassEditor ${SOURCES})
target_include_directories(ClassEditor PUBLIC .)
target_link_libraries(ClassEditor NodeEditor ObjectEditor ClassGenLibrary OneStudioPlatform)
