#pragma once

#include "Editor.hpp"

namespace DefaultExtensions
{

class ClassGenEditor : public Editor
{
public:
    void IndexFile(const System::Path &path) override;
    void RenderFile(const System::Path &path) override;
    bool SaveFile(const System::Path &source, const System::Path &destination) override;
private:
    void ShowGraph(const System::Path &path);
    void RenderDetails(const System::Path &path, ClassGen::ClassInfo &classInfo);
    void RenderData(const System::Path &path, ClassGen::ClassInfo &classInfo);
    void RenderDataRecursively(const System::Path &root, const String &name);
};

}
