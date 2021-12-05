file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(Math INTERFACE ${SOURCES})
target_include_directories(Math INTERFACE .)
target_link_libraries(Math INTERFACE ThirdParty)
