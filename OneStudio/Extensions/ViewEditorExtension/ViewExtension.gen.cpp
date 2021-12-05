//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>
//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ViewEditorView.gen.h"
#include "ViewCGType.h"
class ViewExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::ViewCGType>();
			context.registerType(type, "View", LegacyClassGen::CGTypeGroup::Object/*, &ViewCGType::processAllFiles*/);
			
			MetaObject &editor = manager.getMetaObject<LegacyClassGen::ViewEditorView>();
			context.registerEditor(editor, type);
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, ViewExtension, 0, "1.0.0", "com.Devernity.ViewExtension");
//CLASSGEN END REGION
