#pragma once

#include <ClassGenLibrary>

namespace LegacyClassGen
{

class ClassDataInstance
{
public:
    APath path;
    SharedReference<BaseCGType> type;
    SharedReference<LegacyClassGen::Editor> editor = nullptr;

    void setPath(const APath &path)
    {
        this->path = path;
    }

    bool load()
    {
        type = ClassManager::getInstance().load(path);
        return type != nullptr;
    }

    void bind(const SharedReference<Editor> &editor)
    {
        this->editor = editor;
        editor->onLoad(type->data, type);
    }

    bool save()
    {
        String t;
        type->data.read("Type", t); //HACK
        editor->onSave(type->data);
        type->data.insert("Type", t); //HACK

        YAML::Emitter output_data;
        output_data << YAML::Node(type->data);
        std::ofstream f(path.toString());
        if (f)
        {
            f << output_data.c_str();
        }
        //AJSON::saveToFile(type->data, path);
        return true;
    }
};

}
