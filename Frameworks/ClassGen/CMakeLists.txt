file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(ClassGen ${SOURCES})
target_precompile_headers(ClassGen PRIVATE ClassGen.hpp)
target_include_directories(ClassGen PUBLIC .)
target_link_libraries(ClassGen PUBLIC Graphics)
