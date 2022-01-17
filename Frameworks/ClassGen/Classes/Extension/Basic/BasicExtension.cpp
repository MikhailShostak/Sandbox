
namespace ClassGen
{
void BasicExtension::Load(ClassGen::ExtensionLibrary &Library)
{
    Library.PropertyInstanceEditors["bool"] = Reflection::Find<ClassGen::BooleanPropertyEditor>();

    auto IntEditor = Reflection::Find<ClassGen::IntPropertyEditor>();
    Library.PropertyInstanceEditors["int8_t"] = IntEditor;
    Library.PropertyInstanceEditors["int16_t"] = IntEditor;
    Library.PropertyInstanceEditors["int32_t"] = IntEditor;
    Library.PropertyInstanceEditors["int64_t"] = IntEditor;
    Library.PropertyInstanceEditors["uint8_t"] = IntEditor;
    Library.PropertyInstanceEditors["uint16_t"] = IntEditor;
    Library.PropertyInstanceEditors["uint32_t"] = IntEditor;
    Library.PropertyInstanceEditors["uint64_t"] = IntEditor;

    auto FloatEditor = Reflection::Find<ClassGen::FloatPropertyEditor>();
    Library.PropertyInstanceEditors["float"] = FloatEditor;
    Library.PropertyInstanceEditors["double"] = FloatEditor;

    Library.PropertyInstanceEditors["Int2"] = Reflection::Find<ClassGen::Int2PropertyEditor>();
    Library.PropertyInstanceEditors["Int3"] = Reflection::Find<ClassGen::Int3PropertyEditor>();
    Library.PropertyInstanceEditors["Int4"] = Reflection::Find<ClassGen::Int4PropertyEditor>();
    Library.PropertyInstanceEditors["Float2"] = Reflection::Find<ClassGen::Float2PropertyEditor>();
    Library.PropertyInstanceEditors["Float3"] = Reflection::Find<ClassGen::Float3PropertyEditor>();
    Library.PropertyInstanceEditors["Float4"] = Reflection::Find<ClassGen::Float4PropertyEditor>();
    Library.PropertyInstanceEditors["Color"] = Reflection::Find<ClassGen::ColorPropertyEditor>();

    Library.PropertyInstanceEditors["String"] = Reflection::Find<ClassGen::StringPropertyEditor>();
    Library.PropertyInstanceEditors["System.Path"] = Reflection::Find<ClassGen::PathPropertyEditor>();
}
}
