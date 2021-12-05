//CLASSGEN GENERATED REGION: Includes
#include "TestFlags.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Implementation
AStaticRun(TestFlags)
{
    MetaObjectInformation::getInstance().flags.insert({ AMeta::getStaticTypeHash<TestFlags>(), {"TestFlags", { "Test1", "Test2" } } });
}
TestFlags::TestFlags()
{
    LinkStaticRun(TestFlags);
}
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
