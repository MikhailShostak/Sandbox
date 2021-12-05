//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <LanguageFunctions.h>
//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ClassEditor.gen.h"

#include "ClassSuggestionsComponent.h"

#include "PropertyEditors/BooleanPropertyEditor.gen.h"
#include "PropertyEditors/NumberPropertyEditor.gen.h"
#include "PropertyEditors/RotationPropertyEditor.gen.h"
#include "PropertyEditors/TextPropertyEditor.gen.h"
#include "PropertyEditors/PathPropertyEditor.gen.h"
#include "PropertyEditors/ColorPropertyEditor.gen.h"
#include "PropertyEditors/ArrayPropertyEditor.gen.h"
#include "PropertyEditors/DictionaryPropertyEditor.gen.h"
#include "PropertyEditors/ObjectPropertyEditor.gen.h"

#include "PropertyEditors/ImagePropertyEditor.gen.h"
#include "PropertyEditors/EnumerationPropertyEditor.gen.h"
#include "PropertyEditors/FlagsPropertyEditor.gen.h"

class FieldsExtension : public LegacyClassGen::TypeExtension
{
public:
	void load() override
	{
		auto &context = LegacyClassGen::Context::getInstance();
		MetaObjectManager &manager = MetaObjectManager::getInstance();
		{
			MetaObject &fieldEidtor = manager.getMetaObject<LegacyClassGen::EmbeddedObjectFieldEditor>();
			context.registerFieldEditorForTypes(fieldEidtor, "Class");

			context.registerFieldEditorForTypes(manager.getMetaObject<LegacyClassGen::EnumerationPropertyEditor>(), "Enumeration");
			context.registerFieldEditorForTypes(manager.getMetaObject<LegacyClassGen::FlagsPropertyEditor>(), "Flags");

			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::BooleanPropertyEditor>(), "Boolean");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::NumberPropertyEditor>(), "SignedInteger");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::NumberPropertyEditor>(), "UnsignedInteger");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::NumberPropertyEditor>(), "SizeInteger");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::NumberPropertyEditor>(), "Float");

			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::TextPropertyEditor>(), "String");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::TextPropertyEditor>(), "Text");

			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ArrayPropertyEditor>(), "Array");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ArrayPropertyEditor>(), "Queue");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ArrayPropertyEditor>(), "Stack");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ArrayPropertyEditor>(), "OrderedSet");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ArrayPropertyEditor>(), "UnorderedSet");

			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ObjectPropertyEditor>(), "SharedReference");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ObjectPropertyEditor>(), "UniqueReference");			
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ObjectPropertyEditor>(), "WeakReference");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ObjectPropertyEditor>(), "AssetReference");

			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::DictionaryPropertyEditor>(), "OrderedDictionary");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::DictionaryPropertyEditor>(), "UnorderedDictionary");

			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ColorPropertyEditor>(), "Color");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::RotationPropertyEditor>(), "Math.Quaternion");
			context.registerFieldEditorForInstances(manager.getMetaObject<LegacyClassGen::ImagePropertyEditor>(), "Graphics.Texture");
		}
	}
};
//CLASSGEN GENERATED REGION: ExtensionImplementation
AApplicationPluginImplementation(LegacyClassGen::TypeExtension, FieldsExtension, 0, "1.0.0", "com.Devernity.FieldsExtension");
//CLASSGEN END REGION
