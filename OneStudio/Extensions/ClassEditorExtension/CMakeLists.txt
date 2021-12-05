file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(ClassEditorExtension SHARED ${SOURCES})
target_include_directories(ClassEditorExtension PUBLIC .)
target_link_libraries(ClassEditorExtension ClassEditor Legacy ClassGenLibrary OneStudioPlatform)
set_target_properties(ClassEditorExtension PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/LegacyExtensions/ClassGenExtensions
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/LegacyExtensionsClassGenExtensions
)
