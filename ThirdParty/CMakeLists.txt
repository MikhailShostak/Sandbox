
add_library(ThirdParty
    ${CONAN_RES_DIRS_DILIGENTENGINE}/ImGuiImplDiligent.cpp
    ${CONAN_RES_DIRS_DILIGENTENGINE}/ImGuiDiligentRenderer.cpp
)
target_precompile_headers(ThirdParty PUBLIC ThirdParty.pch.hpp)
target_include_directories(ThirdParty PUBLIC .)
target_link_libraries(ThirdParty ${CONAN_LIBS})

if(UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(ThirdParty stdc++fs)
endif()
