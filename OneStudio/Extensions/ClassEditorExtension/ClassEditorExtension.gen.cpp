//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>
//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ClassEditor.gen.h"
#include "ClassCGType.h"
#include "DataAssetCGType.h"
class ClassEditorExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::ClassCGType>();
			context.registerType(type, "Class", LegacyClassGen::CGTypeGroup::Object/*, &EnumerationCGType::processAllFiles*/);
			MetaObject &dataAsset = manager.getMetaObject<LegacyClassGen::DataAssetCGType>();
			context.registerType(dataAsset, "DataAsset", LegacyClassGen::CGTypeGroup::Asset/*, &EnumerationCGType::processAllFiles*/);

			MetaObject &fieldEidtor = manager.getMetaObject<LegacyClassGen::EmbeddedObjectFieldEditor>();
			context.registerFieldEditorForTypes(fieldEidtor, "Class");
			
			MetaObject &editor = manager.getMetaObject<LegacyClassGen::ClassEditor>();
			context.registerEditor(editor, type);
			context.registerEditor(editor, dataAsset);
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, ClassEditorExtension, 0, "1.0.0", "com.Devernity.ClassEditorExtension");
//CLASSGEN END REGION
