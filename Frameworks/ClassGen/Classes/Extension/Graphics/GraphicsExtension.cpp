
namespace ClassGen
{
void GraphicsExtension::Load(ClassGen::ExtensionLibrary& Library)
{
    Library.Types["Animation"] = Reflection::Find<ClassGen::AnimationInfo>();
    Library.FileEditors["Animation"] = Reflection::Find<ClassGen::AnimationFileEditor>();
    Library.Compilers["Animation"] = Reflection::Find<ClassGen::AnimationCompiler>();

    Library.Types["Material"] = Reflection::Find<ClassGen::MaterialInfo>();
    Library.FileEditors["Material"] = Reflection::Find<ClassGen::MaterialFileEditor>();
    Library.Compilers["Material"] = Reflection::Find<ClassGen::MaterialCompiler>();

    Library.Types["Mesh"] = Reflection::Find<ClassGen::MeshInfo>();
    Library.FileEditors["Mesh"] = Reflection::Find<ClassGen::MeshFileEditor>();
    Library.Compilers["Mesh"] = Reflection::Find<ClassGen::MeshCompiler>();

    Library.Types["ParticleSystem"] = Reflection::Find<ClassGen::ParticleSystemInfo>();
    Library.FileEditors["ParticleSystem"] = Reflection::Find<ClassGen::ParticleSystemFileEditor>();
    Library.Compilers["ParticleSystem"] = Reflection::Find<ClassGen::ParticleSystemCompiler>();

    Library.Types["Scene"] = Reflection::Find<ClassGen::SceneInfo>();
    Library.FileEditors["Scene"] = Reflection::Find<ClassGen::SceneFileEditor>();
    Library.Compilers["Scene"] = Reflection::Find<ClassGen::SceneCompiler>();

    Library.Types["Texture"] = Reflection::Find<ClassGen::TextureInfo>();
    Library.FileEditors["Texture"] = Reflection::Find<ClassGen::TextureFileEditor>();
    Library.Compilers["Texture"] = Reflection::Find<ClassGen::TextureCompiler>();

    Library.PropertyInstanceEditors["ECS.Entity"] = Reflection::Find<ClassGen::InstancePropertyEditor>();
}
}
