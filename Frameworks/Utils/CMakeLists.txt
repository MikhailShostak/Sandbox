file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(Utils INTERFACE ${SOURCES})
target_include_directories(Utils INTERFACE .)
target_link_libraries(Utils INTERFACE ThirdParty)
