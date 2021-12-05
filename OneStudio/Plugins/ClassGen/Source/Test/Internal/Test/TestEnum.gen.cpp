//CLASSGEN GENERATED REGION: Includes
#include "TestEnum.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Implementation
AStaticRun(TestEnum)
{
    MetaObjectInformation::getInstance().enums.insert({ AMeta::getStaticTypeHash<TestEnum>(), { "TestEnum", { "Test1", "Test2" } } });
}
TestEnum::TestEnum()
{
    LinkStaticRun(TestEnum);
}
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
