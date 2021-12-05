//CLASSGEN GENERATED REGION: Includes
#include "BlockFlags.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Implementation
AStaticRun(BlockFlags)
{
    MetaObjectInformation::getInstance().flags.insert({ AMeta::getStaticTypeHash<BlockFlags>(), {"ClassGen.BlockFlags", { "AddIndents", "AddEmptyLines", "CompleteWithSemicolon", "SkipBraces", "AddRegions", "Compact" } } });
}
BlockFlags::BlockFlags()
{
    LinkStaticRun(BlockFlags);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
