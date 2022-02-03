
namespace ClassGen
{
void ClassExtension::Load(ClassGen::ExtensionLibrary &Library)
{
    Library.Types["Class"] = Reflection::Find<ClassGen::ClassInfo>();
    Library.FileEditors["Class"] = Reflection::Find<ClassGen::ClassFileEditor>();
    Library.Compilers["Class"] = Reflection::Find<ClassGen::ClassCompiler>();
    Library.PropertyTypeEditors["Class"] = Reflection::Find<ClassGen::ObjectPropertyEditor>();

    Library.Types["Asset"] = Reflection::Find<ClassGen::AssetInfo>();
    Library.FileEditors["Asset"] = Reflection::Find<ClassGen::AssetFileEditor>();
    Library.Compilers["Asset"] = Reflection::Find<ClassGen::AssetCompiler>();
    Library.PropertyTypeEditors["Asset"] = Reflection::Find<ClassGen::ObjectPropertyEditor>();
}
}
