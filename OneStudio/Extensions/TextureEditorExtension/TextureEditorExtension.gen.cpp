//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>
//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "TextureEditor.gen.h"
#include "TextureCGType.h"
class TextureEditorExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &type = manager.getMetaObject<LegacyClassGen::TextureCGType>();
			context.registerType(type, "Texture", LegacyClassGen::CGTypeGroup::Asset/*, &EnumerationCGType::processAllFiles*/);
			
			MetaObject &editor = manager.getMetaObject<LegacyClassGen::TextureEditor>();
			context.registerEditor(editor, type);
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, TextureEditorExtension, 0, "1.0.0", "com.Devernity.TextureExtension");
//CLASSGEN END REGION
