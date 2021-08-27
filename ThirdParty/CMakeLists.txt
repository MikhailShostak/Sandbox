# Libraries with CMake Build System
add_subdirectory(fmt)
add_subdirectory(glfw)
add_subdirectory(yaml-cpp)

# Diligent Core
option(DILIGENT_NO_DIRECT3D11 "Disable DirectX 11" ON)
option(DILIGENT_NO_DIRECT3D12 "Disable DirectX 12" ON)
option(DILIGENT_NO_OPENGL "Disable OpenGL" ON)
add_subdirectory(DiligentEngine/DiligentCore)

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

)
set(INCLUDES
    .
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
)
target_precompile_headers(ThirdParty PUBLIC ThirdParty.pch.hpp)
target_compile_definitions(ThirdParty PUBLIC ${DEFINES})
target_include_directories(ThirdParty PUBLIC ${INCLUDES})
target_link_libraries(ThirdParty ${LIBRARIES} ${CONAN_LIBS})
