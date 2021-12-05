file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(EnumerationEditorExtension SHARED ${SOURCES})
target_include_directories(EnumerationEditorExtension PUBLIC .)
target_link_libraries(EnumerationEditorExtension Legacy ClassGenLibrary OneStudioPlatform)
set_target_properties(EnumerationEditorExtension PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/LegacyExtensions/ClassGenExtensions
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/LegacyExtensionsClassGenExtensions
)
