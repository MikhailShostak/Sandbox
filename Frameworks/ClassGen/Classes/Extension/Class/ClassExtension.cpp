
namespace ClassGen
{
void ClassExtension::Load(ClassGen::ExtensionLibrary &Library)
{
    Library.Types["Class"] = Reflection::Find<ClassGen::ClassInfo>();
    Library.FileEditors["Class"] = Reflection::Find<ClassGen::ClassFileEditor>();
}
}
