//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "MaterialEditor.h"
#include "MaterialCGType.h"
class MaterialExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::MaterialCGType>();
			context.registerType(type, "Material", LegacyClassGen::CGTypeGroup::Object/*, &EnumerationCGType::processAllFiles*/);
            
			MetaObject &editor = manager.getMetaObject<UI::MaterialEditor>();
			context.registerEditor(editor, type);
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, MaterialExtension, 0, "1.0.0", "com.Devernity.MaterialExtension");
//CLASSGEN END REGION
