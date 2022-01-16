file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

set(ASSETS
    Assets/config.yaml
    Assets/Fonts/MaterialDesignIcons/LICENSE.txt
    Assets/Fonts/MaterialDesignIcons/MaterialIcons-Regular.ttf
    Assets/Extensions/Anonymous.HelloWorld/.extension.yaml
)

add_executable(Editor ${SOURCES})
target_copy_assets(Editor ${ASSETS})
target_precompile_headers(Editor PRIVATE Icons/IconsMaterialDesign.h)
target_link_libraries(Editor Frameworks)
