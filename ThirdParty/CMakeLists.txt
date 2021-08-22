# Libraries with CMake Build System
add_subdirectory(fmt)
add_subdirectory(glfw)
add_subdirectory(yaml-cpp)

# Diligent Core
option(DILIGENT_NO_DIRECT3D11 "Disable DirectX 11" ON)
option(DILIGENT_NO_DIRECT3D12 "Disable DirectX 12" ON)
option(DILIGENT_NO_OPENGL "Disable OpenGL" ON)
add_subdirectory(DiligentEngine/DiligentCore)

# Boost
set(BOOST_INCLUDES
    boost/libs/algorithm/include
    boost/libs/asio/include
    boost/libs/assert/include
    boost/libs/bind/include
    boost/libs/concept_check/include
    boost/libs/config/include
    boost/libs/container_hash/include
    boost/libs/core/include
    boost/libs/detail/include
    boost/libs/filesystem/include
    boost/libs/function/include
    boost/libs/fusion/include
    boost/libs/io/include
    boost/libs/integer/include
    boost/libs/iterator/include
    boost/libs/move/include
    boost/libs/mpl/include
    boost/libs/optional/include
    boost/libs/predef/include
    boost/libs/preprocessor/include
    boost/libs/process/include
    boost/libs/range/include
    boost/libs/static_assert/include
    boost/libs/smart_ptr/include
    boost/libs/system/include
    boost/libs/throw_exception/include
    boost/libs/type_index/include
    boost/libs/type_traits/include
    boost/libs/utility/include
    boost/libs/winapi/include
)
set(BOOST_SOURCES
    boost/libs/filesystem/src/codecvt_error_category.cpp
    boost/libs/filesystem/src/exception.cpp
    boost/libs/filesystem/src/operations.cpp
    boost/libs/filesystem/src/directory.cpp
    boost/libs/filesystem/src/path.cpp
    boost/libs/filesystem/src/path_traits.cpp
    boost/libs/filesystem/src/portability.cpp
    boost/libs/filesystem/src/unique_path.cpp
    boost/libs/filesystem/src/utf8_codecvt_facet.cpp
    boost/libs/filesystem/src/windows_file_codecvt.cpp
)

# ImGui + Addons#
set(IMGUI_INCLUDES
    imgui
    imgui/backends
    imgui/misc/cpp
    DiligentEngine/DiligentTools/Imgui/interface
    ImGuiColorTextEdit
    ImGuiFileDialog
    imgui-node-editor
)
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/misc/cpp/imgui_stdlib.cpp
    DiligentEngine/DiligentTools/Imgui/src/ImGuiImplDiligent.cpp
    DiligentEngine/DiligentTools/Imgui/src/ImGuiDiligentRenderer.cpp
    ImGuiColorTextEdit/TextEditor.cpp
    ImGuiFileDialog/ImGuiFileDialog.cpp
    imgui-node-editor/crude_json.cpp
    imgui-node-editor/imgui_canvas.cpp
    imgui-node-editor/imgui_node_editor.cpp
    imgui-node-editor/imgui_node_editor_api.cpp
)

# Ranges
set(RANGES_INCLUDES
    range-v3/include
)

# All ThirdParty
set(DEFINES
    -DBOOST_ALL_NO_LIB
)
set(INCLUDES
    ${BOOST_INCLUDES}
    ${IMGUI_INCLUDES}
    ${RANGES_INCLUDES}
)
set(LIBRARIES
    Diligent-Common
    Diligent-GraphicsEngine
    Diligent-GraphicsEngineVk-static
    Diligent-GraphicsTools
    fmt
    glfw
    yaml-cpp
)
add_library(ThirdParty
    ${IMGUI_SOURCES}
    ${BOOST_SOURCES}
)
target_precompile_headers(ThirdParty PUBLIC ThirdParty.pch.hpp)
target_compile_definitions(ThirdParty PUBLIC ${DEFINES})
target_include_directories(ThirdParty PUBLIC ${INCLUDES})
target_link_libraries(ThirdParty ${LIBRARIES})
