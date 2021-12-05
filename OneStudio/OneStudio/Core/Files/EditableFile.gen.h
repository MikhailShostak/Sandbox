#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "FileInstance.gen.h"
#include "OneStudioPlatform"
#include "Experimental"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct EditableFile : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EditableFile This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    SharedReference<OneStudio::FileInstance> FileInstance;
    SharedReference<OneStudioPlatform::EditorInstance> EditorInstance;
    SharedReference<UI::View> EditorView;
public:
    EditableFile();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    EditableFile(const SharedReference<OneStudio::FileInstance> &FileInstance, const SharedReference<OneStudioPlatform::EditorInstance> &EditorInstance, const SharedReference<UI::View> &EditorView):
        FileInstance(FileInstance),
        EditorInstance(EditorInstance),
        EditorView(EditorView)
    {

    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
