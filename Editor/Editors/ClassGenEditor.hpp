#pragma once

#include "Editor.hpp"

namespace DefaultExtensions
{

class ClassGenEditor : public Editor
{
public:
    void IndexFile(const std::filesystem::path &path) override;
    void RenderFile(const std::filesystem::path &path) override;
    bool SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination) override;
private:
    void RenderDetails(const std::filesystem::path &path, ClassGen::ClassInfo &classInfo);
    void RenderData(const std::filesystem::path &path, ClassGen::ClassInfo &classInfo);
    void RenderDataRecursively(const std::filesystem::path &root, const std::string &name);
};

}
