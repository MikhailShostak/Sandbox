//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>
//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "EnumerationEditor.gen.h"
#include "EnumerationCGType.h"
#include "FlagsCGType.h"
class EnumerationEditorExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
        auto &context = LegacyClassGen::Context::getInstance();
        MetaObjectManager &manager = MetaObjectManager::getInstance();
        MetaObject &editor = manager.getMetaObject<LegacyClassGen::EnumerationEditor>();
        {
            MetaObject &type = manager.getMetaObject<LegacyClassGen::EnumerationCGType>();
            context.registerType(type, "Enumeration", LegacyClassGen::CGTypeGroup::SimpleValue/*, &EnumerationCGType::processAllFiles*/);
            context.registerEditor(editor, type);
        }
        {
            MetaObject &type = manager.getMetaObject<LegacyClassGen::FlagsCGType>();
            context.registerType(type, "Flags", LegacyClassGen::CGTypeGroup::SimpleValue/*, &EnumerationCGType::processAllFiles*/);
            context.registerEditor(editor, type);
        }
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, EnumerationEditorExtension, 0, "1.0.0", "com.Devernity.EnumerationEditorExtension");
//CLASSGEN END REGION
