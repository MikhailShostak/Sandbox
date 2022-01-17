
namespace ClassGen
{
void EnumerationExtension::Load(ClassGen::ExtensionLibrary &Library)
{
    Library.Types["Enumeration"] = Reflection::Find<ClassGen::EnumerationInfo>();
    Library.Types["Flags"] = Reflection::Find<ClassGen::EnumerationInfo>();
    Library.FileEditors["Enumeration"] = Reflection::Find<ClassGen::EnumerationFileEditor>();
    Library.FileEditors["Flags"] = Reflection::Find<ClassGen::EnumerationFileEditor>();
    Library.PropertyTypeEditors["Enumeration"] = Reflection::Find<ClassGen::EnumerationPropertyEditor>();
    Library.PropertyTypeEditors["Flags"] = Reflection::Find<ClassGen::EnumerationPropertyEditor>();
    Library.Compilers["Enumeration"] = Reflection::Find<ClassGen::EnumerationCompiler>();
    Library.Compilers["Flags"] = Reflection::Find<ClassGen::EnumerationCompiler>();
}
}
