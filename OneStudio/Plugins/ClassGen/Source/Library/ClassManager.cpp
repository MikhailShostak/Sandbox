#include "Types/Class/ClassManager.h"

#include "BasicCGType.h"
//#include "FunctionLibraryCGType.h"
//#include "ScriptCGType.h"
#include "ExtensionCGType.h"
//#include "EnumerationCGType.h"
//#include "FlagsCGType.h"
#include "StateMachineCGType.h"
//#include "ApplicationFlowCGType.h"
#include "DataObjectCGType.h"
//#include "MaterialCGType.h"
#include "SceneCGType.h"

#include <MetaObject.h>

namespace LegacyClassGen
{

template<typename T>
MetaObject &registerTempType(const char *name)
{
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<T>();
    object.baseObject = &manager.getMetaObject<AObject>();
    manager.registerMetaObject(name, object);
    return object;
}

ClassManager::ClassManager()
{
    registerType(registerTempType<BasicCGType>("ClassGen.BasicCGType"), "BasicType", CGTypeGroup::SimpleValue);
    //registerType(registerTempType<EnumerationCGType>("ClassGen.EnumerationCGType"), "Enumeration", CGTypeGroup::SimpleValue, &EnumerationCGType::processAllFiles);
    //registerType(registerTempType<FlagsCGType>("ClassGen.FlagsCGType"), "Flags", CGTypeGroup::SimpleValue, &FlagsCGType::processAllFiles);
    //registerType(registerTempType<ClassCGType>("ClassGen.ClassCGType"), "Class", CGTypeGroup::Object, &ClassCGType::processAllFiles);
    //registerType(registerTempType<FunctionLibraryCGType>("ClassGen.FunctionLibraryCGType"), "FunctionLibrary", CGTypeGroup::Function);
    registerType(registerTempType<ExtensionCGType>("ClassGen.ExtensionCGType"), "Extension", CGTypeGroup::Object);
    //registerType(registerTempType<ScriptCGType>("ClassGen.ScriptCGType"), "Script", CGTypeGroup::Object);
    registerType(registerTempType<DataObjectCGType>("ClassGen.DataObjectCGType"), "DataObject", CGTypeGroup::Object);
    registerType(registerTempType<StateMachineCGType>("ClassGen.StateMachineCGType"), "StateMachine", CGTypeGroup::Object);
    //registerType(registerTempType<ApplicationFlowCGType>("ClassGen.ApplicationFlowCGType"), "ApplicationFlow", CGTypeGroup::Object);
    //registerType(registerTempType<TextureCGType>("ClassGen.TextureCGType"), "Texture", CGTypeGroup::Asset, &TextureCGType::processAllFiles);
    //registerType(registerTempType<ViewCGType>("ClassGen.ViewCGType"), "View", CGTypeGroup::Object, &ViewCGType::processAllFiles);
    //registerType(registerTempType<MaterialCGType>("ClassGen.MaterialCGType"), "Material", CGTypeGroup::Object);
    registerType(registerTempType<SceneCGType>("ClassGen.SceneCGType"), "Scene", CGTypeGroup::Object);
}

}
