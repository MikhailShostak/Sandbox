#pragma once

#include "Editor.hpp"

namespace DefaultExtensions
{

class TextEditor : public Editor
{
public:
    void RenderFile(const std::filesystem::path &path) override;
};

}
