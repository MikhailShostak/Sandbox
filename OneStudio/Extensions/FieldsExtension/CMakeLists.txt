file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp)
add_library(FieldsExtension SHARED ${SOURCES})
target_include_directories(FieldsExtension PUBLIC .)
target_link_libraries(FieldsExtension ClassEditor Fields Legacy ClassGenLibrary OneStudioPlatform)
set_target_properties(FieldsExtension PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/LegacyExtensions/ClassGenExtensions
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/LegacyExtensionsClassGenExtensions
)
