#include "ClassGenEditor.hpp"

#include "../Data/Workspace.hpp"

#include <imgui_node_editor.h>

static ax::NodeEditor::EditorContext* g_Context = nullptr;

struct Node
{
    size_t id = 0;
    std::string name;
};

std::vector<Node> Nodes;

void ShowGraph()
{
    if(g_Context == nullptr)
    {
        g_Context = ax::NodeEditor::CreateEditor();
        //TODO: ax::NodeEditor::DestroyEditor(g_Context);
    }

    auto &io = ImGui::GetIO();
    auto swapButtons = [&io](size_t i, size_t j){
        std::swap(io.MouseDown[i], io.MouseDown[j]);
        std::swap(io.MouseClickedPos[i], io.MouseClickedPos[j]);
        std::swap(io.MouseClickedTime[i], io.MouseClickedTime[j]);
        std::swap(io.MouseClicked[i], io.MouseClicked[j]);
        std::swap(io.MouseDoubleClicked[i], io.MouseDoubleClicked[j]);
        std::swap(io.MouseReleased[i], io.MouseReleased[j]);
        std::swap(io.MouseDownOwned[i], io.MouseDownOwned[j]);
        std::swap(io.MouseDownWasDoubleClick[i], io.MouseDownWasDoubleClick[j]);
        std::swap(io.MouseDownDuration[i], io.MouseDownDuration[j]);
        std::swap(io.MouseDownDurationPrev[i], io.MouseDownDurationPrev[j]);
        std::swap(io.MouseDragMaxDistanceAbs[i], io.MouseDragMaxDistanceAbs[j]);
        std::swap(io.MouseDragMaxDistanceSqr[i], io.MouseDragMaxDistanceSqr[j]);
    };

    if (ImGui::Begin("GraphWindow"))
    {
        //swapButtons(1, 2);
        ax::NodeEditor::SetCurrentEditor(g_Context);
        ax::NodeEditor::Begin("GraphEditor");

        ax::NodeEditor::NodeId contextNodeId = 0;
        ax::NodeEditor::PinId contextPinId = 0;
        ax::NodeEditor::LinkId contextLinkId = 0;

        for (const auto &node : Nodes)
        {
            ax::NodeEditor::BeginNode(node.id);
            ImGui::Text(node.name.data());
            ax::NodeEditor::Suspend();
            if (ax::NodeEditor::ShowNodeContextMenu(&contextNodeId))
                ImGui::OpenPopup("Node Context Menu");
            /*else if (ax::NodeEditor::ShowPinContextMenu(&contextPinId))
                ImGui::OpenPopup("Pin Context Menu");
            else if (ax::NodeEditor::ShowLinkContextMenu(&contextLinkId))
                ImGui::OpenPopup("Link Context Menu");*/
            else if (ax::NodeEditor::ShowBackgroundContextMenu())
            {
                ImGui::OpenPopup("Create New Node");
            }
            ax::NodeEditor::Resume();
            ax::NodeEditor::EndNode();
        }

        ax::NodeEditor::Suspend();
        if (ImGui::BeginPopup("Node Context Menu"))
        {
            if(ImGui::MenuItem("Remove"))
            {
                //ed::DeleteNode(contextNodeId);
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Create New Node"))
        {
            std::string name;
            if(ImGui::InputText("Find##GraphSearch", &name, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                Node n;
                n.id = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                n.name = name;
                Nodes.push_back(n);
            }
            ImGui::EndPopup();
        }
        ax::NodeEditor::Resume();

        //bool ShowPinContextMenu(PinId* pinId);
        //bool ShowLinkContextMenu(LinkId* linkId);

        ax::NodeEditor::End();
        //swapButtons(1, 2);

        /*if(ImGui::BeginPopupContextWindow())
        {
            ImGui::EndPopup();
        }*/
    }
    ImGui::End();
}

namespace DefaultExtensions
{

std::unordered_map<std::string, YAML::Node> ClassGenCache;

YAML::Node FindClassByName(const std::string &name, const std::string &nameSpace)
{
    YAML::Node node;

    auto it = std::find_if(ClassGenCache.begin(), ClassGenCache.end(), [&](const auto &v)
    {
        bool result = true;
        if(!nameSpace.empty() && v.second["Namespace"].IsDefined())
        {
            result = v.second["Namespace"].as<std::string>() == nameSpace;
        }

        return result && std::filesystem::path(v.first).stem().generic_string() == name;
    });
    if(it != ClassGenCache.end())
    {
        node = it->second;
    }

    return node;
}

YAML::Node FindClassByName(const std::string &fullname)
{
    std::filesystem::path p(fullname);
    if(p.has_extension())
    {
        return FindClassByName(p.extension().generic_string(), p.stem().generic_string());
    }
    else
    {
        return FindClassByName(p.stem().generic_string(), std::string());
    }
}

void ClassGenEditor::IndexFile(const std::filesystem::path &path)
{
    std::string pathString = path.generic_string();
    auto it = ClassGenCache.find(pathString);
    if(it != ClassGenCache.end())
    {
        fmt::print("Class {} already exists", pathString);
        return;
    }

    auto node = YAML::LoadFile(pathString);
    if (node["Type"].IsDefined())
    {
        ClassGenCache.insert({pathString, node});
    }
}

void ClassGenEditor::RenderDataRecursively(const std::filesystem::path &root, const std::string &name)
{
    YAML::Node node = FindClassByName(name);
    if (ImGui::CollapsingHeader(name.data(), ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Columns(2);
        for(auto i : node["Properties"])
        {
            std::string name = i["Name"].as<std::string>();
            ImGui::Text(name.data());
            //ImGui::TreeNode("Test", name.data());
            auto propertyName = "##Property" + name;

            std::string type = i["Type"].as<std::string>();
            ImGui::NextColumn();
            if (type == "Boolean")
            {
                static bool value = true;
                ImGui::Checkbox(propertyName.data(), &value);
            }
            else if (type == "Integer")
            {
                static int value = 100;
                ImGui::DragInt(propertyName.data(), &value, 1);
            }
            else if (type == "Float")
            {
                static float value = 1.0f;
                ImGui::DragFloat(propertyName.data(), &value, 0.01f);
            }
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
    }
    if (node["BaseType"])
    {
        RenderDataRecursively(root, node["BaseType"].as<std::string>());
    }
}

void ClassGenEditor::RenderDetails(const std::filesystem::path &path, YAML::Node &FileData, std::string &Namespace)
{
    if (ImGui::CollapsingHeader("Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::InputText("Namespace", &Namespace))
        {
            FileData["Namespace"] = Namespace;
            MarkFileDirty(path);
        }

        std::string BaseType;
        if(FileData["BaseType"].IsDefined())
        {
            BaseType = FileData["BaseType"].as<std::string>();
        }
        if(ImGui::InputText("Base Type", &BaseType))
        {
            FileData["BaseType"] = BaseType;
            MarkFileDirty(path);
        }

        ImGui::Separator();

        ImGui::Text("Interfaces");
        std::string Interfaces;
        for(auto i : FileData["Interfaces"])
        {
            ImGui::Text(i.as<std::string>().data());
        }
    }

    if (ImGui::CollapsingHeader("Properties", ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string Properties;
        for(auto i : FileData["Properties"])
        {
            std::string type = i["Type"].as<std::string>();
            std::string name = i["Name"].as<std::string>();
            if(ImGui::InputText(("Type##" + name).data(), &type, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                i["Type"] = type;
            }
            if(ImGui::InputText(("Name##" + name).data(), &name, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                i["Name"] = name;
                ImGui::SetKeyboardFocusHere(-1);
            }
        }
    }
}

void ClassGenEditor::RenderData(const std::filesystem::path &path, YAML::Node &FileData, std::string &Namespace)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
    RenderDataRecursively(path, Namespace.empty() ? path.stem().generic_string() : (Namespace + "." + path.stem().generic_string()));
    ImGui::PopStyleVar();
}

void ClassGenEditor::RenderFile(const std::filesystem::path &path)
{
    auto &FileData = ClassGenCache[path.generic_string()];

    if(!FileData["Type"].IsDefined())
    {
        FileData["Type"] = "Class";
    }

    std::string Type = FileData["Type"].as<std::string>();

    if(ImGui::BeginPopupContextWindow())
    {
        if(ImGui::MenuItem("Add property"))
        {
            YAML::Node node;
            node["Type"] = "Boolean";
            node["Name"] = "NewProperty";
            FileData["Properties"].push_back(node);
            MarkFileDirty(path);
        }
        ImGui::EndPopup();
    }

    ImGui::Text(Type.data());

    std::string Namespace;
    if(FileData["Namespace"].IsDefined())
    {
        Namespace = FileData["Namespace"].as<std::string>();
    }

    if (ImGui::BeginTabBar("##ClassTabBarDetails"))
    {
        if(ImGui::BeginTabItem("Details"))
        {
            RenderDetails(path, FileData, Namespace);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (ImGui::BeginTabBar("##ClassTabBarData"))
    {
        if(ImGui::BeginTabItem("Data"))
        {
            RenderData(path, FileData, Namespace);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ShowGraph();
}

bool ClassGenEditor::SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination)
{
    auto node = ClassGenCache.at(source.generic_string());
    YAML::Emitter out;
    out << YAML::Block << node;

    std::ofstream file;
    file.open(destination.generic_string(), std::ios::binary);
    if(!file.is_open())
    {
        return false;
    }

    file << out.c_str();
    return true;
}

}
