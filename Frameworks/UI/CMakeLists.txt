file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(UI ${SOURCES})
target_precompile_headers(UI PRIVATE UI.hpp)
target_include_directories(UI PUBLIC .)
target_link_libraries(UI PUBLIC Utils)
