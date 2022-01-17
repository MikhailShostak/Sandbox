#include <ClassGen.hpp>

namespace { struct { struct Dummy { Dummy() {
Reflection::Add<ClassGen::BaseInfo>("ClassGen.BaseInfo");
Reflection::Add<ClassGen::ClassInfo>("ClassGen.ClassInfo");
Reflection::Add<ClassGen::EventInfo>("ClassGen.EventInfo");
Reflection::Add<ClassGen::FileInfo>("ClassGen.FileInfo");
Reflection::Add<ClassGen::FunctionInfo>("ClassGen.FunctionInfo");
Reflection::Add<ClassGen::ParameterInfo>("ClassGen.ParameterInfo");
Reflection::Add<ClassGen::PropertyInfo>("ClassGen.PropertyInfo");
Reflection::Add<ClassGen::TypeInfo>("ClassGen.TypeInfo");
Reflection::Add<ClassGen::FileEditor>("ClassGen.FileEditor");
Reflection::Add<ClassGen::PropertyEditor>("ClassGen.PropertyEditor");
Reflection::Add<ClassGen::ClassExtension>("ClassGen.ClassExtension");
Reflection::Add<ClassGen::ClassCompiler>("ClassGen.ClassCompiler");
Reflection::Add<ClassGen::ClassFileEditor>("ClassGen.ClassFileEditor");
Reflection::Add<ClassGen::ExtensionInterface>("ClassGen.ExtensionInterface");
Reflection::Add<ClassGen::ExtensionLibrary>("ClassGen.ExtensionLibrary");
Reflection::Add<ClassGen::ConnectionInfo>("ClassGen.ConnectionInfo");
Reflection::Add<ClassGen::GraphInfo>("ClassGen.GraphInfo");
Reflection::Add<ClassGen::NodeInfo>("ClassGen.NodeInfo");
} } Dummy; } Dummy; }
