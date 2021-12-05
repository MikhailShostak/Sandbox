file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(TextureEditorExtension SHARED ${SOURCES})
target_include_directories(TextureEditorExtension PUBLIC .)
target_link_libraries(TextureEditorExtension Fields Legacy ClassGenLibrary OneStudioPlatform)
set_target_properties(TextureEditorExtension PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/LegacyExtensions/ClassGenExtensions
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/LegacyExtensionsClassGenExtensions
)
