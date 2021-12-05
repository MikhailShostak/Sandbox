file(GLOB_RECURSE ONESTUDIO_PLATFORM_SOURCES CONFIGURE_DEPENDS OneStudioPlatform/**.hpp OneStudioPlatform/**.cpp)
add_library(OneStudioPlatform ${ONESTUDIO_PLATFORM_SOURCES})
target_include_directories(OneStudioPlatform PUBLIC OneStudioPlatform/Interface OneStudioPlatform/Interface/Includes)
target_link_libraries(OneStudioPlatform Legacy)

add_subdirectory(Extensions)
add_subdirectory(Plugins)

#file(GLOB_RECURSE ONESTUDIO_PLUGINS_SOURCES CONFIGURE_DEPENDS Plugins/**.hpp Plugins/**.cpp)

file(GLOB_RECURSE ONESTUDIO_SOURCES CONFIGURE_DEPENDS OneStudio/**.hpp OneStudio/**.cpp)
add_executable(OneStudio ${ONESTUDIO_SOURCES})
target_include_directories(OneStudio PRIVATE
    OneStudio
    OneStudio/Assets
    OneStudio/Core
    OneStudio/Core/Editor
    OneStudio/Core/EnvironmentVariables
    OneStudio/Core/Extensions
    OneStudio/Core/Files
    OneStudio/Core/Popups
    OneStudio/Core/Popups/File
    OneStudio/Core/Popups/Find
    OneStudio/Core/Settings
    OneStudio/Core/Settings/Toolbar
    OneStudio/Core/Support
    OneStudio/Core/Tasks
    OneStudio/Core/Types
    OneStudio/Core/WindowLayout
    OneStudio/Experimental
    OneStudio/Materials
)
target_link_libraries(OneStudio Legacy OneStudioPlatform)# Ws2_32)#OneStudioPlatform)
add_dependencies(OneStudio OneStudioExtensions ClassGenExtension)
