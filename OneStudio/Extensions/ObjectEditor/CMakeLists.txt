file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(ObjectEditor ${SOURCES})
target_include_directories(ObjectEditor PUBLIC .)
target_link_libraries(ObjectEditor Fields ClassGenLibrary OneStudioPlatform)
