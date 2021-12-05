add_subdirectory(Fields)
add_subdirectory(NodeEditor)
add_subdirectory(ObjectEditor)
add_subdirectory(ClassEditor)

add_subdirectory(FieldsExtension)
add_subdirectory(ClassEditorExtension)
add_subdirectory(EnumerationEditorExtension)
add_subdirectory(TextureEditorExtension)
add_subdirectory(ViewEditorExtension)

add_library(OneStudioExtensions INTERFACE)
target_link_libraries(OneStudioExtensions INTERFACE
    FieldsExtension
    EnumerationEditorExtension
    ClassEditorExtension
    TextureEditorExtension
    ViewEditorExtension
)
