file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(Fields ${SOURCES})
target_include_directories(Fields PUBLIC .)
target_link_libraries(Fields ClassGenLibrary OneStudioPlatform)
