//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ApplicationFlowEditor.gen.h"
#include "ApplicationFlowCGType.h"
class ApplicationFlowExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::ApplicationFlowCGType>();
			context.registerType(type, "ApplicationFlow", LegacyClassGen::CGTypeGroup::Object/*, &EnumerationCGType::processAllFiles*/);
		
			MetaObject &editor = manager.getMetaObject<LegacyClassGen::ApplicationFlowEditor>();
			context.registerEditor(editor, type);
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, ApplicationFlowExtension, 0, "1.0.0", "com.Devernity.ApplicationFlowExtension");
//CLASSGEN END REGION
