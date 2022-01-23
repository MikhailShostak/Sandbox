#pragma once

namespace ClassGen
{
struct ArrayPropertyEditor
    : public ClassGen::ValuePropertyEditor<List<Serialization::Data>>
{
    using This = ArrayPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<List<Serialization::Data>>;
    Array<UniqueReference<ClassGen::PropertyEditor>> PropertyEditors = {};

    virtual ~ArrayPropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
    virtual Serialization::Data/*DefaultData*/ CreateDefaultData();
    virtual void RebuildEditors();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
