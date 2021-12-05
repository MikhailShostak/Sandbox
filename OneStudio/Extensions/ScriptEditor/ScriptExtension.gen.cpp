//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ScriptEditor.gen.h"
#include "ScriptCGType.h"
class ScriptExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::ScriptCGType>();
			context.registerType(type, "FunctionLibrary", LegacyClassGen::CGTypeGroup::Function/*, &EnumerationCGType::processAllFiles*/);
			
			MetaObject &editor = manager.getMetaObject<LegacyClassGen::ScriptEditor>();
			context.registerEditor(editor, type);
		}
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::ScriptCGType>();
			context.registerType(type, "Script", LegacyClassGen::CGTypeGroup::Object/*, &EnumerationCGType::processAllFiles*/);
            
			MetaObject &editor = manager.getMetaObject<LegacyClassGen::ScriptEditor>();
			context.registerEditor(editor, type);
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, ScriptExtension, 0, "1.0.0", "com.Devernity.ScriptExtension");
//CLASSGEN END REGION
