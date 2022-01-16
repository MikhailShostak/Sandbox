#pragma once

#include "Editor.hpp"

namespace DefaultExtensions
{

class ClassGenEditor : public Editor
{
public:
    void ResetIndex() override;
    void IndexFile(const System::Path &path) override;
    void RenderFile(const System::Path &path) override;
    bool SaveFile(const System::Path &source, const System::Path &destination) override;
};

}
