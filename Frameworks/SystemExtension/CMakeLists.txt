file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.inl)

add_library(SystemExtension INTERFACE ${SOURCES})
target_include_directories(SystemExtension INTERFACE .)
target_precompile_headers(SystemExtension INTERFACE SystemExtension.pch.hpp)
target_link_libraries(SystemExtension INTERFACE ThirdParty Utils)
