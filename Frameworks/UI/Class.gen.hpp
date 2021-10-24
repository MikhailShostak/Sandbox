#include <UI.hpp>

namespace { struct { struct Dummy { Dummy() {
Reflection::Add<UI::Button>("UI.Button");
Reflection::Add<UI::Label>("UI.Label");
Reflection::Add<UI::TextField>("UI.TextField");
Reflection::Add<UI::View>("UI.View");
} } Dummy; } Dummy; }
