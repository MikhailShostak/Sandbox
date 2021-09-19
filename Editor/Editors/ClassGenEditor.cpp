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

    /*auto &io = ImGui::GetIO();
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
    };*/

    if (ImGui::Begin("GraphWindow"))
    {
        //swapButtons(1, 2);
        ax::NodeEditor::SetCurrentEditor(g_Context);
        ax::NodeEditor::Begin("GraphEditor");

        ax::NodeEditor::NodeId contextNodeId = 0;
        //ax::NodeEditor::PinId contextPinId = 0;
        //ax::NodeEditor::LinkId contextLinkId = 0;

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

std::unordered_map<std::string, ClassGen::FileInfo> ClassGenCache;

ClassGen::FileInfo FindClassByName(const std::string &name, const std::string &nameSpace)
{
    ClassGen::FileInfo node;

    auto it = std::find_if(ClassGenCache.begin(), ClassGenCache.end(), [&](const auto &v)
    {
        bool result = true;
        if(!nameSpace.empty() && !v.second.Instance->Namespace.empty())
        {
            result = v.second.Instance->Namespace == nameSpace;
        }

        return result && std::filesystem::path(v.first).stem().generic_string() == name;
    });
    if(it != ClassGenCache.end())
    {
        node = it->second;
    }

    return node;
}

ClassGen::FileInfo FindClassByName(const std::string &fullname)
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
    if (path.extension() != ".cg")
    {
        return;
    }

    std::string pathString = path.generic_string();
    auto it = ClassGenCache.find(pathString);
    if(it != ClassGenCache.end())
    {
        fmt::print("Class {} already exists", pathString);
        return;
    }

    Serialization::Data data;
    data.FromFile(pathString);

    auto fileInfo = Serialization::Deserialize<ClassGen::FileInfo>(data);
    if (fileInfo.Type == "Class")
    {
        auto classInfo = std::make_shared<ClassGen::ClassInfo>();
        Serialization::Deserialize(data, *classInfo);
        fileInfo.Instance = classInfo;
        ClassGenCache.insert({ pathString, fileInfo });
    }
}

void ClassGenEditor::RenderDataRecursively(const std::filesystem::path &root, const std::string &name)
{
    ClassGen::FileInfo fileInfo = FindClassByName(name);
    auto classInfo = std::dynamic_pointer_cast<ClassGen::ClassInfo>(fileInfo.Instance);
    if (!classInfo)
    {
        ImGui::Text(fmt::format("Base Class Not Found: {}", name).data());
        return;
    }

    if (ImGui::CollapsingHeader(name.data(), ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Columns(2);
        for(auto &p : classInfo->Properties)
        {
            ImGui::Text(p.Name.data());
            auto propertyId = fmt::format("##PropertyValue{}", (void*)&p);
            auto type = writeRecursively(p.Type);
            ImGui::NextColumn();
            if (type == "Boolean")
            {
                static bool value = true;
                ImGui::Checkbox(propertyId.data(), &value);
            }
            else if (type == "Integer")
            {
                static int value = 100;
                ImGui::DragInt(propertyId.data(), &value, 1);
            }
            else if (type == "Float")
            {
                static float value = 1.0f;
                ImGui::DragFloat(propertyId.data(), &value, 0.01f);
            }
            else
            {
                ImGui::PushItemWidth(-1);
                if (type == "std.string")
                {
                    static std::string value;
                    ImGui::InputText(propertyId.data(), &value);
                }
                else if (type == "std.filesystem.path")
                {
                    static std::string value;
                    ImGui::InputText(propertyId.data(), &value);
                }
                ImGui::PopItemWidth();
            }
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
    }
    auto baseType = writeRecursively(classInfo->BaseType);
    if (!baseType.empty())
    {
        RenderDataRecursively(root, baseType);
    }
}

void ClassGenEditor::RenderDetails(const std::filesystem::path &path, ClassGen::ClassInfo &classInfo)
{
    if (ImGui::CollapsingHeader("Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Columns(2);

        ImGui::Text("Namespace");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if (ImGui::InputText("##Namespace", &classInfo.Namespace))
        {
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Base Type");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::InputText("##BaseType", &classInfo.BaseType.Name))
        {
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Attributes");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        auto attributes = boost::join(classInfo.Attributes, " ");
        if (ImGui::InputText("##Attributes", &attributes))
        {
            boost::split(classInfo.Attributes, attributes, boost::is_any_of(" "));
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        /*ImGui::Separator();

        ImGui::Text("Interfaces");
        std::string Interfaces;
        for(auto i : FileData["Interfaces"])
        {
            ImGui::Text(i.as<std::string>().data());
        }*/
        ImGui::Columns(1);
    }

    if (ImGui::CollapsingHeader("Properties", ImGuiTreeNodeFlags_DefaultOpen))
    {
        static ClassGen::PropertyInfo *selectedProperty = nullptr;
        bool selection = false;
        for (auto &p : classInfo.Properties)
        {
            bool selected = selectedProperty == &p;
            if (ImGui::Selectable(fmt::format("{}##PropertyItem", p.Name).data(), &selected))
            {
                selectedProperty = &p;
            }
            selection |= selected;
        }
        if (!selection)
        {
            selectedProperty = nullptr;
        }
        else
        {
            ImGui::Separator();
        }
        ImGui::Columns(2);
        if (selectedProperty)
        {
            std::string type = writeRecursively(selectedProperty->Type);
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::InputText(fmt::format("##PropertyName{}", (void *)selectedProperty).data(), &selectedProperty->Name))
            {
                MarkFileDirty(path);
                ImGui::SetKeyboardFocusHere(-1);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Text("Type");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if(ImGui::InputText(fmt::format("##PropertyType{}", (void*)selectedProperty).data(), &type))
            {
                readRecursively(type, selectedProperty->Type);                
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Text("Attributes");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            auto attributes = boost::join(selectedProperty->Attributes, " ");
            if (ImGui::InputText(fmt::format("##PropertyAttributes{}", (void *)selectedProperty).data(), &attributes))
            {
                boost::split(selectedProperty->Attributes, attributes, boost::is_any_of(" "));
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
    }
}

void ClassGenEditor::RenderData(const std::filesystem::path &path, ClassGen::ClassInfo &classInfo)
{
    //TODO: Check FileData
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
    RenderDataRecursively(path, classInfo.Namespace.empty() ? path.stem().generic_string() : (classInfo.Namespace + "." + path.stem().generic_string()));
    ImGui::PopStyleVar();
}

void ClassGenEditor::RenderFile(const std::filesystem::path &path)
{
    auto &fileInfo = ClassGenCache[path.generic_string()];

    auto classInfo = std::dynamic_pointer_cast<ClassGen::ClassInfo>(fileInfo.Instance);

    if(ImGui::BeginPopupContextWindow())
    {
        if(ImGui::MenuItem("Add property"))
        {
            ClassGen::PropertyInfo p;
            p.Type.Name = "Boolean";
            p.Name = "NewProperty";
            classInfo->Properties.push_back(std::move(p));
            MarkFileDirty(path);
        }
        ImGui::EndPopup();
    }

    ImGui::Text(fileInfo.Type.data());
    ImGui::SameLine();
    if (ImGui::Button("Generate"))
    {
        bool isStruct = ranges::contains(classInfo->Attributes, "Structure");
        auto className = path.stem().generic_string();
        auto classNamespace = boost::replace_all_copy(classInfo->Namespace, ".", "::");
        auto classBaseType = writeRecursivelyResolved(classInfo->BaseType);
        auto p = std::filesystem::path(path).replace_extension(".hpp");
        std::ofstream file;
        file.open(p.generic_string(), std::ios::binary);
        file << "#pragma once\n";
        file << "\n";
        if (!classNamespace.empty())
        {
            file << "namespace " << classNamespace << "\n";
            file << "{\n";
        }
        file << "struct " << className << "\n";
        if (!classInfo->BaseType.Name.empty())
        {
            file << "    : public " << classBaseType << "\n";
        }
        file << "{\n";
        file << "    using This = " << className << ";\n";
        if (!classInfo->BaseType.Name.empty())
        {
            file << "    using Super = " << classBaseType << ";\n";
        }
        for (const auto &p : classInfo->Properties)
        {
            file << "    " << writeRecursivelyResolved(p.Type) << " " << p.Name << ";\n";
        }
        if (!isStruct)
        {
            file << "\n";
            file << "    virtual ~" << className << "() {}\n";
        }
        file << "\n";
        file << "    template<typename T>\n";
        file << "    void Serialize(T &&data)\n";
        file << "    {\n";
        for (const auto &p : classInfo->Properties)
        {
            if (ranges::contains(p.Attributes, "Serialize"))
            {
                file << "        data[\"" << p.Name << "\"] & " << p.Name << ";\n";
            }
        }
        file << "    }\n";
        file << "};\n";
        if (!classNamespace.empty())
        {
            file << "}\n";
        }
    }

    if (ImGui::BeginTabBar("##ClassTabBarDetails"))
    {
        if(ImGui::BeginTabItem("Details"))
        {
            RenderDetails(path, *classInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (ImGui::BeginTabBar("##ClassTabBarData"))
    {
        if(ImGui::BeginTabItem("Data"))
        {
            RenderData(path, *classInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ShowGraph();
}

bool ClassGenEditor::SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination)
{
    auto fileInfo = ClassGenCache.at(source.generic_string());
    Serialization::Data data;
    Serialization::Serialize(fileInfo, data);
    auto classInfo = std::dynamic_pointer_cast<ClassGen::ClassInfo>(fileInfo.Instance);
    Serialization::Serialize(*classInfo, data);
    data.ToFile(destination);
    return true;
}

}
