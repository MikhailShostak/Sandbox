file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(Graphics ${SOURCES})
target_compile_definitions(Graphics PUBLIC -DENGINE_DLL=0 -DVULKAN_SUPPORTED=1) #TODO: make private
target_include_directories(Graphics PUBLIC .)
target_precompile_headers(Graphics PUBLIC Graphics.pch.hpp)
target_link_libraries(Graphics PUBLIC Utils)
