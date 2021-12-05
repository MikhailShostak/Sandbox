//CLASSGEN GENERATED REGION: Includes
#include "FunctionManager.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//#include <ClassGenLibrary>
//#include "ClassManager.h"
//#include "PropertyInfo.gen.h"
//#include "FunctionInfo.gen.h"
//#include "CGTypeGroup.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FunctionManager::FunctionManager()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FunctionManager::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Test", toJSONValue(Test));
}
void FunctionManager::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Test", value);
    fromJSONValue(value, Test);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
String FunctionManager::getTest() const
{
    return this->Test;
}
void FunctionManager::setTest(String const &Test)
{
    this->Test = Test;
}
void FunctionManager::setTest(String &&Test)
{
    this->Test = std::move(Test);
}
//CLASSGEN END REGION
Array<LegacyClassGen::FunctionInfo> FunctionManager::Fetch()
{
    Array<LegacyClassGen::FunctionInfo> result;
    const Map<String, SharedReference<LegacyClassGen::BaseCGType>> &types = LegacyClassGen::ClassManager::getInstance().getLoadedTypes();
    for (const APair<String, SharedReference<LegacyClassGen::BaseCGType>> &pair : types)
    {
        String name = pair.second->getDefaultType();

        Array<LegacyClassGen::FunctionInfo> functions;
        AJSONValue f;
        pair.second->data.read("Functions", f);
        fromJSONValue(f, functions);

        if (pair.second->group == LegacyClassGen::CGTypeGroup::Object)
        {
            for (auto &function : functions)
            {
                function.Identifier = name + "." + function.Identifier;
                result.push_back(function);
            }
        }
        else
        {
            for (auto &function : functions)
            {
                result.push_back(function);
            }
        }

        Array<LegacyClassGen::PropertyInfo> properties;
        AJSONValue p;
        pair.second->data.read("Properties", p);
        fromJSONValue(p, properties);

        for (auto &p : properties)
        {
            LegacyClassGen::Parameter arg;
            arg.Name = "Value";
            arg.Type.Name = "Boolean";

            LegacyClassGen::FunctionInfo getter;
            getter.Identifier = name + ".Get" + p.Name;
            getter.Callable = false;
            getter.OutputArguments.push_back(arg);
            //getter.ExecutionBranches.append(String());

            LegacyClassGen::FunctionInfo setter;
            setter.InputArguments.push_back(arg);
            setter.Identifier = name + ".Set" + p.Name;
            setter.Callable = true;
            //setter.ExecutionBranches.append(String());

            result.push_back(getter);
            result.push_back(setter);
        }
    }
    return result;
}

void FunctionManager::ClearIndex()
{
    Cache.clear();
}

void FunctionManager::Index()
{
    if (Cache.empty())
    {
        Cache = Fetch();
    }
}

void FunctionManager::ReIndex()
{
    ClearIndex();
    Index();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
