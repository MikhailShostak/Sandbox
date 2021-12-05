file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(ViewEditorExtension SHARED ${SOURCES})
target_include_directories(ViewEditorExtension PUBLIC .)
target_link_libraries(ViewEditorExtension ClassEditor Fields Legacy ClassGenLibrary OneStudioPlatform)
set_target_properties(ViewEditorExtension PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/LegacyExtensions/ClassGenExtensions
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/LegacyExtensionsClassGenExtensions
)
