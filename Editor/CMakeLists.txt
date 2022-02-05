file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

set(ASSETS
    Assets/config.yaml
    Assets/Fonts/MaterialDesignIcons/LICENSE.txt
    Assets/Fonts/MaterialDesignIcons/MaterialIcons-Regular.ttf
    Assets/Extensions/Anonymous.HelloWorld/.extension.yaml
)

add_executable(Editor ${SOURCES})
target_include_directories(Editor PRIVATE .)
target_precompile_headers(Editor PRIVATE Editor.pch.hpp)
target_copy_assets(Editor ${ASSETS})
target_link_libraries(Editor Frameworks)
