#include "../Views.hpp"
#include "../../Data/Workspace.hpp"

namespace Debug
{

void ShowDebugWindow()
{
    if (!DisplayDebugWindow)
    {
        return;
    }

    ImGui::PushMonospacedFont();
    if (ImGui::Begin("DebugWindow"))
    {
        if (ImGui::CollapsingHeader("ClassGen FunctionCache##DebugWindow", nullptr))
        {
            for (auto& [Name, FunctionInfo] : g_FunctionCache)
            {
                ImGui::Text(Name.data());
            }
        }
        if (ImGui::CollapsingHeader("ClassGen Cache##DebugWindow", nullptr))
        {
            for (auto& [Name, FileInfo] : g_ClassGenCache)
            {
                ImGui::Text(Name.data());
            }
        }
        if (ImGui::CollapsingHeader("ClassGen Editors##DebugWindow", nullptr))
        {
            for (auto& [Name, Editor] : g_Editors)
            {
                ImGui::Text(Name.data());
            }
        }

        if (ImGui::CollapsingHeader("FileCache##DebugWindow", nullptr))
        {
            for (auto& [Path, Data] : FileCache)
            {
                ImGui::Text(Path.data());
            }
        }

        if (ImGui::CollapsingHeader("UnsavedFiles##DebugWindow", nullptr))
        {
            for (auto& [Path, Editor] : UnsavedFiles)
            {
                ImGui::Text(Path.data());
            }
        }

        if (ImGui::CollapsingHeader("Types##DebugWindow", nullptr))
        {
            if (ImGui::BeginTable("TypesTable##DebugWindow", 2, DefaultTableFlags))
            {
                ImGui::TableSetupColumn("ClassGen Type", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("C++ Class", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableHeadersRow();
                for (auto& [Name, Type] : g_ExtensionLibrary.Types)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(Name.data());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(Type->m_Name);
                }
                ImGui::EndTable();
            }
        }

        if (ImGui::CollapsingHeader("FileEditors##DebugWindow", nullptr))
        {
            if (ImGui::BeginTable("FileEditorsTable##DebugWindow", 2, DefaultTableFlags))
            {
                ImGui::TableSetupColumn("ClassGen Type", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("C++ Class", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableHeadersRow();
                for (auto& [Name, Type] : g_ExtensionLibrary.FileEditors)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(Name.data());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(Type->m_Name);
                }
                ImGui::EndTable();
            }
        }

        if (ImGui::CollapsingHeader("Compilers##DebugWindow", nullptr))
        {
            if (ImGui::BeginTable("CompilersTable##DebugWindow", 2, DefaultTableFlags))
            {
                ImGui::TableSetupColumn("ClassGen Type", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("C++ Class", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableHeadersRow();
                for (auto& [Name, Type] : g_ExtensionLibrary.Compilers)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(Name.data());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(Type->m_Name);
                }
                ImGui::EndTable();
            }
        }

        if (ImGui::CollapsingHeader("ReflectedTypes##DebugWindow", nullptr))
        {
            for (auto &[Hash, Type] : Reflection::GetTypes())
            {
                ImGui::Text("%s", Type->m_Name);
            }
        }
    }
    ImGui::End();
    ImGui::PopFont();
}

}
