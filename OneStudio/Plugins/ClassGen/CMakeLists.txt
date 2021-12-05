file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Source/Library/**.h Source/Library/**.cpp)
add_library(ClassGenLibrary ${SOURCES})
target_include_directories(ClassGenLibrary PUBLIC
    Source/Library/Interface
    Source/Library/Interface/Core
    Source/Library/Interface/Includes
    Source/Library/Interface/Types
    Source/Library/Interface/Types/Class
    Source/Library/Interface/Types/Data
    Source/Library/Interface/Types/Extension
    Source/Library/Interface/Types/Graph
    Source/Library/Interface/Types/Scene
    Source/Library/Interface/Types/StateMachine
)
target_link_libraries(ClassGenLibrary Legacy)

file(GLOB_RECURSE EXTENSION_SOURCES CONFIGURE_DEPENDS Source/Plugin/**.h Source/Plugin/**.cpp)
target_include_directories(ClassGenLibrary PUBLIC
    Source/Plugin
    Source/Plugin/Editors
    Source/Plugin/Editors/Extension
)
add_library(ClassGenExtension SHARED ${EXTENSION_SOURCES})
target_link_libraries(ClassGenExtension ClassGenLibrary OneStudioPlatform)
set_target_properties(ClassGenExtension PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/LegacyExtensions
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/LegacyExtensions
)
