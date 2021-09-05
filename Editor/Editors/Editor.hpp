#pragma once

class Editor
{
public:
    virtual void IndexFile([[maybe_unused]] const std::filesystem::path &path) {}
    virtual void RenderFile([[maybe_unused]] const std::filesystem::path &path) {}
    virtual bool SaveFile([[maybe_unused]] const std::filesystem::path &source, [[maybe_unused]] const std::filesystem::path &destination) { return false; }
    void MarkFileDirty(const std::filesystem::path &path);
};

inline std::unordered_map<std::string, std::unique_ptr<Editor>> Editors;
