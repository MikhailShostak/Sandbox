file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(SceneWindow ${SOURCES})
target_include_directories(SceneWindow PUBLIC .)
target_precompile_headers(SceneWindow PUBLIC SceneWindow.pch.hpp)
target_link_libraries(SceneWindow PUBLIC Input NativeApplication)
