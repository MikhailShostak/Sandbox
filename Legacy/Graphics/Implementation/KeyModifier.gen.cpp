//CLASSGEN GENERATED REGION: Includes
#include "KeyModifier.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Implementation
AStaticRun(KeyModifier)
{
    MetaObjectInformation::getInstance().flags.insert({ AMeta::getStaticTypeHash<KeyModifier>(), {"Core.KeyModifier", { "Alt", "Ctrl", "Shift", "Win" } } });
}
KeyModifier::KeyModifier()
{
    LinkStaticRun(KeyModifier);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
