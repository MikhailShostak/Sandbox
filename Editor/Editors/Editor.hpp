#pragma once

class Editor
{
public:
    virtual void IndexFile(const std::filesystem::path &path) {}
    virtual void RenderFile(const std::filesystem::path &path) {}
    virtual bool SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination) { return false; }
    void MarkFileDirty(const std::filesystem::path &path);
};

inline std::unordered_map<std::string, std::unique_ptr<Editor>> Editors;
