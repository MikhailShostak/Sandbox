file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

set(ASSETS
    Assets/config.yaml
    Assets/Extensions/Anonymous.HelloWorld/.extension.yaml
)

add_executable(Editor ${SOURCES})
target_copy_assets(Editor ${ASSETS})
target_link_libraries(Editor Frameworks)
