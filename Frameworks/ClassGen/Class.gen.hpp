#include <ClassGen.hpp>

namespace { struct { struct Dummy { Dummy() {
Reflection::Add<ClassGen::BaseInfo>("ClassGen.BaseInfo");
Reflection::Add<ClassGen::ClassInfo>("ClassGen.ClassInfo");
Reflection::Add<ClassGen::AssetInfo>("ClassGen.AssetInfo");
Reflection::Add<ClassGen::EventInfo>("ClassGen.EventInfo");
Reflection::Add<ClassGen::FileInfo>("ClassGen.FileInfo");
Reflection::Add<ClassGen::FunctionInfo>("ClassGen.FunctionInfo");
Reflection::Add<ClassGen::ParameterInfo>("ClassGen.ParameterInfo");
Reflection::Add<ClassGen::PropertyInfo>("ClassGen.PropertyInfo");
Reflection::Add<ClassGen::TypeInfo>("ClassGen.TypeInfo");
Reflection::Add<ClassGen::FileEditor>("ClassGen.FileEditor");
Reflection::Add<ClassGen::PropertyEditor>("ClassGen.PropertyEditor");
Reflection::Add<ClassGen::BasicExtension>("ClassGen.BasicExtension");
Reflection::Add<ClassGen::BooleanPropertyEditor>("ClassGen.BooleanPropertyEditor");
Reflection::Add<ClassGen::IntPropertyEditor>("ClassGen.IntPropertyEditor");
Reflection::Add<ClassGen::Int2PropertyEditor>("ClassGen.Int2PropertyEditor");
Reflection::Add<ClassGen::Int3PropertyEditor>("ClassGen.Int3PropertyEditor");
Reflection::Add<ClassGen::Int4PropertyEditor>("ClassGen.Int4PropertyEditor");
Reflection::Add<ClassGen::FloatPropertyEditor>("ClassGen.FloatPropertyEditor");
Reflection::Add<ClassGen::Float2PropertyEditor>("ClassGen.Float2PropertyEditor");
Reflection::Add<ClassGen::Float3PropertyEditor>("ClassGen.Float3PropertyEditor");
Reflection::Add<ClassGen::Float4PropertyEditor>("ClassGen.Float4PropertyEditor");
Reflection::Add<ClassGen::ColorPropertyEditor>("ClassGen.ColorPropertyEditor");
Reflection::Add<ClassGen::StringPropertyEditor>("ClassGen.StringPropertyEditor");
Reflection::Add<ClassGen::PathPropertyEditor>("ClassGen.PathPropertyEditor");
Reflection::Add<ClassGen::ArrayPropertyEditor>("ClassGen.ArrayPropertyEditor");
Reflection::Add<ClassGen::ObjectPropertyEditor>("ClassGen.ObjectPropertyEditor");
Reflection::Add<ClassGen::InstancePropertyEditor>("ClassGen.InstancePropertyEditor");
Reflection::Add<ClassGen::ClassExtension>("ClassGen.ClassExtension");
Reflection::Add<ClassGen::ClassCompiler>("ClassGen.ClassCompiler");
Reflection::Add<ClassGen::AssetCompiler>("ClassGen.AssetCompiler");
Reflection::Add<ClassGen::ClassFileEditor>("ClassGen.ClassFileEditor");
Reflection::Add<ClassGen::AssetFileEditor>("ClassGen.AssetFileEditor");
Reflection::Add<ClassGen::ExtensionInterface>("ClassGen.ExtensionInterface");
Reflection::Add<ClassGen::ExtensionLibrary>("ClassGen.ExtensionLibrary");
Reflection::Add<ClassGen::ConnectionInfo>("ClassGen.ConnectionInfo");
Reflection::Add<ClassGen::GraphInfo>("ClassGen.GraphInfo");
Reflection::Add<ClassGen::NodeInfo>("ClassGen.NodeInfo");
} } Dummy; } Dummy; }
