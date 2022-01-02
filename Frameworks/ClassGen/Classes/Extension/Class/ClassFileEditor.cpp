
#include <imgui_node_editor.h>

namespace ClassGen
{

inline static ImGuiTableFlags DefaultTableFlags =
    ImGuiTableFlags_SizingFixedFit |
    ImGuiTableFlags_RowBg |
    ImGuiTableFlags_Borders |
    ImGuiTableFlags_Resizable |
    ImGuiTableFlags_Hideable;

static ax::NodeEditor::EditorContext *g_Context = nullptr;

float padding = 0;
const float PaddingSize = 16;
void PushPadding() { padding += PaddingSize; }
void PopPadding() { padding -= PaddingSize; }
void ApplyPadding() { ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding); }

String g_GraphName;
String g_GraphID;
ClassGen::GraphInfo *g_CurrentGraph = nullptr;


void ClassFileEditor::ShowGraph(const System::Path &path)
{
    if (g_Context == nullptr)
    {
        g_Context = ax::NodeEditor::CreateEditor();
        //TODO: ax::NodeEditor::DestroyEditor(g_Context);
    }
    if (ImGui::Begin("Classes##ClassGen"))
    {
        if (ImGui::BeginTable("ClassTable##ClassGen", 3, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

            for (auto &p : g_ClassGenCache)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ClassGen::FileInfo &f = p.second;
                ImGui::Text(System::Path(p.first).stem().generic_string().data());

                ImGui::TableSetColumnIndex(1);
                ImGui::Text(f.Type.data());

                ImGui::TableSetColumnIndex(2);
                ImGui::TextWrapped(p.first.data());

            }

            ImGui::EndTable();
        }
    }
    ImGui::End();

    String tooltip;
    if (ImGui::Begin(("Graph: " + g_GraphName + "###ClassGen").data()))
    {
        ax::NodeEditor::SetCurrentEditor(g_Context);
        ax::NodeEditor::Begin("GraphEditor");

        ax::NodeEditor::NodeId contextNodeId = 0;
        ax::NodeEditor::PinId contextPinId = 0;
        ax::NodeEditor::LinkId contextLinkId = 0;

        for (const auto &node : g_CurrentGraph->Nodes)
        {
            ax::NodeEditor::BeginNode((ax::NodeEditor::NodeId)&node);
            ImGui::Text(node.Name.data());

            if (node.Name == "Input")
            {
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)0, ax::NodeEditor::PinKind::Output);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();

                auto it = g_FunctionCache.find(g_GraphID);
                if (it != g_FunctionCache.end())
                {
                    const ClassGen::FunctionInfo &f = it->second;
                    for (auto &p : f.InputParameters)
                    {
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Output);
                        ImGui::Text(p.Name.data());
                        ImGui::SameLine();
                        ImGui::Text("[ ]");
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                    }
                }
                ax::NodeEditor::EndNode();
                continue;
            }
            else if (node.Name == "Output")
            {
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)1, ax::NodeEditor::PinKind::Input);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();
                auto it = g_FunctionCache.find(g_GraphID);
                if (it != g_FunctionCache.end())
                {
                    const ClassGen::FunctionInfo &f = it->second;
                    for (auto &p : f.OutputParameters)
                    {
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Input);
                        ImGui::Text("[ ]");
                        ImGui::SameLine();
                        ImGui::Text(p.Name.data());
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                    }
                }
                ax::NodeEditor::EndNode();
                continue;
            }

            Array<String> id;
            boost::split(id, node.ID, boost::is_any_of("-"));
            auto it = g_FunctionCache.find(id[0]);
            if (it != g_FunctionCache.end())
            {
                const ClassGen::FunctionInfo &f = it->second;
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)0, ax::NodeEditor::PinKind::Input);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();
                ImGui::SameLine();
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)1, ax::NodeEditor::PinKind::Output);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();
                size_t s = std::max(f.InputParameters.size(), f.OutputParameters.size());
                for (size_t i = 0; i < s; ++i)
                {
                    bool sameLine = false;
                    if (i < f.InputParameters.size())
                    {
                        auto &p = f.InputParameters[i];
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Input);
                        ImGui::Text("[ ]");
                        ImGui::SameLine();
                        ImGui::Text(p.Name.data());
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                        sameLine = true;
                    }

                    if (i < f.OutputParameters.size())
                    {
                        auto &p = f.OutputParameters[i];
                        if (sameLine)
                        {
                            ImGui::SameLine();
                        }
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Input);
                        ImGui::Text(p.Name.data());
                        ImGui::SameLine();
                        ImGui::Text("[ ]");
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                    }
                }
            }

            ax::NodeEditor::EndNode();
        }
        ax::NodeEditor::Suspend();
        if (ax::NodeEditor::ShowNodeContextMenu(&contextNodeId))
        {
            ImGui::OpenPopup("Node Context Menu");
        }
        else if (ax::NodeEditor::ShowPinContextMenu(&contextPinId))
        {
            ImGui::OpenPopup("Pin Context Menu");
        }
        else if (ax::NodeEditor::ShowLinkContextMenu(&contextLinkId))
        {
            ImGui::OpenPopup("Link Context Menu");
        }
        if (ax::NodeEditor::ShowNodeContextMenu(&contextNodeId))
        {
            ImGui::OpenPopup("Node Context Menu");
        }
        else if (ax::NodeEditor::ShowBackgroundContextMenu())
        {
            ImGui::OpenPopup("Create New Node");
        }

        if (ImGui::BeginPopup("Node Context Menu"))
        {
            if (ImGui::MenuItem("Remove"))
            {
                ax::NodeEditor::DeleteNode(contextNodeId);
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Create New Node"))
        {
            String name;
            if (ImGui::InputText("Find##GraphSearch", &name, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                ClassGen::NodeInfo n;
                n.ID = fmt::format("{}-{:x}", name, std::chrono::duration_cast<DateTime::Milliseconds>(DateTime::System::Clock::now().time_since_epoch()).count());
                n.Name = name;
                g_CurrentGraph->Nodes.push_back(n);
                MarkFileDirty(path);
            }
            ImGui::EndPopup();
        }
        ax::NodeEditor::Resume();
        ax::NodeEditor::End();
    }
    ImGui::End();
    if (ImGui::Begin("Tooltip##ClassGen"))
    {
        ImGui::TextWrapped(tooltip.data());
    }
    ImGui::End();
}

ClassGen::FileInfo FindClassByName(const String &name, const String &nameSpace)
{
    ClassGen::FileInfo node;

    auto it = std::find_if(g_ClassGenCache.begin(), g_ClassGenCache.end(), [&](const auto &v)
    {
        bool result = true;
        if (!nameSpace.empty() && !v.second.Instance->Namespace.empty())
        {
            result = v.second.Instance->Namespace == nameSpace;
        }

        return result && System::Path(v.first).stem().generic_string() == name;
    });
    if (it != g_ClassGenCache.end())
    {
        node = it->second;
    }

    return node;
}

ClassGen::FileInfo FindClassByName(const String &fullname)
{
    System::Path p(fullname);
    if (p.has_extension())
    {
        auto name = p.extension().generic_string();
        boost::trim_left_if(name, boost::is_any_of("."));
        return FindClassByName(name, p.stem().generic_string());
    }
    else
    {
        return FindClassByName(p.stem().generic_string(), String());
    }
}

namespace
{

template<class Key, class T, class Compare, class Alloc, class Pred>
typename std::map<Key, T, Compare, Alloc>::size_type erase_if(std::map<Key, T, Compare, Alloc> &c, Pred pred)
{
    auto old_size = c.size();
    for (auto i = c.begin(), last = c.end(); i != last; ) {
        if (pred(*i)) {
            i = c.erase(i);
        }
        else {
            ++i;
        }
    }
    return old_size - c.size();
}

template<class Key, class T, class Compare, class Alloc, class Pred>
typename std::unordered_map<Key, T, Compare, Alloc>::size_type erase_if(std::unordered_map<Key, T, Compare, Alloc> &c, Pred pred)
{
    auto old_size = c.size();
    for (auto i = c.begin(), last = c.end(); i != last; ) {
        if (pred(*i)) {
            i = c.erase(i);
        }
        else {
            ++i;
        }
    }
    return old_size - c.size();
}

}

void ClearIndex(const String &namespaceName)
{
    auto prefix = namespaceName + ".";
    erase_if(g_FunctionCache, [&](auto &pair) {
        return boost::starts_with(pair.first, prefix);
    });
}

void IndexFunctions(const Array<ClassGen::FunctionInfo> &functions, const String &namespaceName)
{
    for (const auto &f : functions)
    {
        ClassGen::FunctionInfo function = f;
        function.Name = namespaceName + "." + function.Name;
        g_FunctionCache[function.Name] = std::move(function);
    }
}

void IndexProperties(const Array<ClassGen::PropertyInfo> &properties, const String &namespaceName)
{
    for (const auto &p : properties)
    {
        ClassGen::FunctionInfo getter;
        getter.Name = namespaceName + ".Get" + p.Name;
        getter.InputParameters = { ClassGen::ParameterInfo{ p.Type, p.Name } };
        g_FunctionCache[getter.Name] = std::move(getter);

        ClassGen::FunctionInfo setter;
        setter.Name = namespaceName + ".Set" + p.Name;
        setter.OutputParameters = { ClassGen::ParameterInfo{ p.Type, p.Name } };
        g_FunctionCache[setter.Name] = std::move(setter);
    }
}

void IndexFileData(const System::Path &path, const ClassGen::BaseInfo &baseInfo)
{
    auto namespaceName = path.stem().generic_string();
    if (!baseInfo.Namespace.empty())
    {
        namespaceName = baseInfo.Namespace + "." + namespaceName;
    }

    ClearIndex(namespaceName);

    auto classInfo = dynamic_cast<const ClassGen::ClassInfo *>(&baseInfo);
    if (!classInfo)
    {
        return;
    }

    IndexProperties(classInfo->Properties, namespaceName);
    IndexFunctions(classInfo->Functions, namespaceName);
}

void ClassFileEditor::RenderDataRecursively(const System::Path &root, const String &name)
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
        for (auto &p : classInfo->Properties)
        {
            ImGui::Text(p.Name.data());
            auto propertyId = fmt::format("##PropertyValue{}", (void *)&p);
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
                    static String value;
                    ImGui::InputText(propertyId.data(), &value);
                }
                else if (type == "std.filesystem.path")
                {
                    static String value;
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

void ClassFileEditor::RenderDetails(const System::Path &path, ClassGen::ClassInfo &classInfo)
{
    if (ImGui::CollapsingHeader("Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Columns(2);

        ImGui::Text("Namespace");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if (ImGui::InputText("##Namespace", &classInfo.Namespace))
        {
            IndexFileData(path, classInfo);
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Base Type");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        String baseType = writeRecursively(classInfo.BaseType);
        if (ImGui::InputText("##BaseType", &baseType))
        {
            readRecursively(baseType, classInfo.BaseType);
            IndexFileData(path, classInfo);
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
            IndexFileData(path, classInfo);
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Template Types");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        std::string templateTypes = Str::Join(classInfo.TemplateTypes, " ");
        if (ImGui::InputText("##TemplateTypes", &templateTypes))
        {
            classInfo.TemplateTypes = Str::Split(templateTypes, " ");
            IndexFileData(path, classInfo);
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Indirect Type");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        String indirectType = writeRecursively(classInfo.IndirectType);
        if (ImGui::InputText("##IndirectType", &indirectType))
        {
            readRecursively(indirectType, classInfo.IndirectType);
            IndexFileData(path, classInfo);
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();
        /*ImGui::Separator();

        ImGui::Text("Interfaces");
        String Interfaces;
        for(auto i : FileData["Interfaces"])
        {
            ImGui::Text(i.as<String>().data());
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
            String type = writeRecursively(selectedProperty->Type);
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::InputText(fmt::format("##PropertyName{}", (void *)selectedProperty).data(), &selectedProperty->Name))
            {
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
                ImGui::SetKeyboardFocusHere(-1);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Text("Type");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::InputText(fmt::format("##PropertyType{}", (void *)selectedProperty).data(), &type))
            {
                readRecursively(type, selectedProperty->Type);
                IndexFileData(path, classInfo);
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
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
    }

    auto ArrayProperty = [this, &path, &classInfo](const char *label, auto &data)
    {
        ImGui::Text(label);
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if (ImGui::Button(fmt::format("+##{}", (void *)&data).data()))
        {
            data.push_back({});
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        PushPadding();
        ImGui::Separator();
        size_t itemToRemove = -1;
        for (size_t i = 0; i < data.size(); ++i)
        {
            auto &p = data[i];

            ApplyPadding();
            ImGui::Text(fmt::format("{}", i).data());
            ImGui::NextColumn();

            if (ImGui::Button(fmt::format("-##{}", (void *)&p).data()))
            {
                itemToRemove = i;
            }
            ImGui::NextColumn();
            ImGui::Separator();

            PushPadding();
            ApplyPadding();
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::InputText(fmt::format("##Name{}", (void *)&p).data(), &p.Name))
            {
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
                ImGui::SetKeyboardFocusHere(-1);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ApplyPadding();
            ImGui::Text("Type");
            ImGui::NextColumn();
            String type = writeRecursively(p.Type);
            ImGui::PushItemWidth(-1);
            if (ImGui::InputText(fmt::format("##Type{}", (void *)&p).data(), &type))
            {
                readRecursively(type, p.Type);
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Text("Writable");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::Checkbox(fmt::format("##{}", (void *)&p.Writable).data(), &p.Writable))
            {
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Text("Copy");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::Checkbox(fmt::format("##{}", (void *)&p.Copy).data(), &p.Copy))
            {
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ImGui::Separator();
            PopPadding();
        }
        PopPadding();
        if (itemToRemove != -1)
        {
            data.erase(data.begin() + itemToRemove);
        }
    };

    if (ImGui::CollapsingHeader("Events", ImGuiTreeNodeFlags_DefaultOpen))
    {
        static ClassGen::EventInfo *selectedEvent = nullptr;
        bool selection = false;
        for (auto &e : classInfo.Events)
        {
            bool selected = selectedEvent == &e;
            if (ImGui::Selectable(fmt::format("{}##EventItem", e.Name).data(), &selected))
            {
                selectedEvent = &e;
            }
            selection |= selected;
        }
        if (!selection)
        {
            selectedEvent = nullptr;
        }
        else
        {
            ImGui::Separator();
        }
        ImGui::Columns(2);
        if (selectedEvent)
        {
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            String currentName = String("Event.") + selectedEvent->Name;
            if (ImGui::InputText(fmt::format("##EventName{}", (void *)selectedEvent).data(), &selectedEvent->Name))
            {
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
                ImGui::SetKeyboardFocusHere(-1);

                //TODO: rework
                String oldName = std::move(currentName);
                currentName = String("Event.") + selectedEvent->Name;
                //classInfo.Graphs[currentName] = classInfo.Graphs[oldName];
                //classInfo.Graphs.erase(oldName);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            ArrayProperty("InputParameters", selectedEvent->InputParameters);
        }
        ImGui::Columns(1);
    }

    if (ImGui::CollapsingHeader("Functions", ImGuiTreeNodeFlags_DefaultOpen))
    {
        static ClassGen::FunctionInfo *selectedFunction = nullptr;
        bool selection = false;
        for (auto &f : classInfo.Functions)
        {
            bool selected = selectedFunction == &f;
            if (ImGui::Selectable(fmt::format("{}##FunctionItem", f.Name).data(), &selected))
            {
                selectedFunction = &f;
            }
            selection |= selected;
        }
        if (!selection)
        {
            selectedFunction = nullptr;
        }
        else
        {
            ImGui::Separator();
        }
        ImGui::Columns(2);
        if (selectedFunction)
        {
            ImGui::Text("Name");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            String currentName = String("Function.") + selectedFunction->Name;
            if (ImGui::InputText(fmt::format("##FunctionName{}", (void *)selectedFunction).data(), &selectedFunction->Name))
            {
                IndexFileData(path, classInfo);
                MarkFileDirty(path);
                ImGui::SetKeyboardFocusHere(-1);

                //TODO: rework
                String oldName = std::move(currentName);
                currentName = String("Function.") + selectedFunction->Name;
                classInfo.Graphs[currentName] = classInfo.Graphs[oldName];
                classInfo.Graphs.erase(oldName);
            }
            g_CurrentGraph = &classInfo.Graphs[currentName];
            g_GraphName = selectedFunction->Name;
            g_GraphID = (classInfo.Namespace.empty() ? path.stem().generic_string() : (classInfo.Namespace + "." + path.stem().generic_string())) + "." + selectedFunction->Name;
            auto it = ranges::find_if(g_CurrentGraph->Nodes, [](ClassGen::NodeInfo &node) { return node.ID == "Input"; });
            if (it == g_CurrentGraph->Nodes.end())
            {
                ClassGen::NodeInfo node;
                node.ID = "Input";
                node.Name = "Input";
                g_CurrentGraph->Nodes.push_back(std::move(node));
            }
            it = ranges::find_if(g_CurrentGraph->Nodes, [](ClassGen::NodeInfo &node) { return node.ID == "Output"; });
            if (it == g_CurrentGraph->Nodes.end())
            {
                ClassGen::NodeInfo node;
                node.ID = "Output";
                node.Name = "Output";
                g_CurrentGraph->Nodes.push_back(std::move(node));
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();

            /*String returnType = writeRecursively(selectedFunction->ReturnType);
            ImGui::Text("ReturnType");
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            if (ImGui::InputText(fmt::format("##FunctionReturnType{}", (void *)selectedFunction).data(), &returnType))
            {
                readRecursively(returnType, selectedFunction->ReturnType);
                MarkFileDirty(path);
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();*/

            ArrayProperty("InputParameters", selectedFunction->InputParameters);
            ArrayProperty("OutputParameters", selectedFunction->OutputParameters);
        }
        ImGui::Columns(1);
    }
}

void ClassFileEditor::RenderData(const System::Path &path, ClassGen::ClassInfo &classInfo)
{
    //TODO: Check FileData
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    RenderDataRecursively(path, classInfo.Namespace.empty() ? path.stem().generic_string() : (classInfo.Namespace + "." + path.stem().generic_string()));
    ImGui::PopStyleVar();
}

void RenderGlobalFile()
{
    return;
    //TODO: this temp code should be fully reworked
    Map<String, std::ofstream> Files;
    auto beginFile = [](std::ofstream &f, const String &pch) {
        f << "#include <" << pch << ">\n\n";
        f << "namespace { struct { struct Dummy { Dummy() {\n";
    };
    auto processClassGenFile = [](std::ofstream &f, const System::Path &path, const ClassGen::FileInfo &fileInfo) {
        auto &classInfo = *std::dynamic_pointer_cast<ClassGen::ClassInfo>(fileInfo.Instance);

        auto className = path.stem().generic_string();
        if (!classInfo.Namespace.empty())
        {
            className = classInfo.Namespace + "." + className;
        }
        auto resolvedClassName = boost::replace_all_copy(className, ".", "::");
        f << "Reflection::Add<" + resolvedClassName + ">(\"" + className + "\");\n";
    };
    auto endFile = [](std::ofstream &f) {
        f << "} } Dummy; } Dummy; }\n";
    };

    SortedSet<System::Path> ProjectFolders;
    /*for (System::Path p : Config.File.OpenedFolders)
    {
        auto root = p.root_path();
        while (p.has_parent_path() && p != root)
        {
            System::Path cmake = p / "CMakeLists.txt";
            if (std::filesystem::exists(cmake))
            {
                ProjectFolders.insert(p);
            }
            p = p.parent_path();
        }
    }*/
    for (auto &pair : g_ClassGenCache)
    {
        for (auto &p : ProjectFolders | ranges::views::reverse)
        {
            if (boost::starts_with(System::Path(pair.first).parent_path().generic_string(), p.generic_string()))
            {
                auto pch = p.filename().generic_string() + ".hpp";
                auto filepath = p / "Class.gen.hpp";
                auto filepathString = filepath.generic_string();
                std::ofstream &f = Files[filepathString];
                if (!f.is_open())
                {
                    f.open(filepathString, std::ios::binary);
                    fmt::print("Write: {}\n", filepathString);
                    beginFile(f, pch);
                }
                processClassGenFile(f, pair.first, pair.second);
                break;
            }
        }
    }
    for (auto &f : Files)
    {
        endFile(f.second);
        f.second.close();
    }
}

void ClassFileEditor::RenderFile()
{
    auto &fileInfo = Data;
    auto &classInfo = *std::dynamic_pointer_cast<ClassGen::ClassInfo>(fileInfo.Instance);
    g_CurrentGraph = nullptr;

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("Add property"))
        {
            ClassGen::PropertyInfo p;
            p.Type.Name = "Boolean";
            p.Name = "NewProperty";
            classInfo.Properties.push_back(std::move(p));
            IndexFileData(Path, classInfo);
            MarkFileDirty(Path);
        }
        if (ImGui::MenuItem("Add function"))
        {
            ClassGen::FunctionInfo f;
            f.Name = "NewFunction";
            classInfo.Functions.push_back(std::move(f));
            IndexFileData(Path, classInfo);
            MarkFileDirty(Path);
        }
        if (ImGui::MenuItem("Add event"))
        {
            ClassGen::EventInfo e;
            e.Name = "NewEvent";
            classInfo.Events.push_back(std::move(e));
            IndexFileData(Path, classInfo);
            MarkFileDirty(Path);
        }
        ImGui::EndPopup();
    }

    ImGui::Text(fileInfo.Type.data());
    ImGui::SameLine();
    if (ImGui::Button("Generate"))
    {
        RenderGlobalFile();

        bool isStruct = ranges::contains(classInfo.Attributes, "Structure");
        auto className = Path.stem().generic_string();
        auto classNamespace = boost::replace_all_copy(classInfo.Namespace, ".", "::");
        auto classBaseType = writeRecursivelyResolved(classInfo.BaseType);
        auto p = System::Path(Path).replace_extension(".hpp");
        std::ofstream file;
        file.open(p.generic_string(), std::ios::binary);
        fmt::print("Write: {}\n", p.generic_string());
        file << "#pragma once\n";
        file << "\n";
        if (!classNamespace.empty())
        {
            file << "namespace " << classNamespace << "\n";
            file << "{\n";
        }
        if (!classInfo.TemplateTypes.empty())
        {
            file << "template<";
            file << (classInfo.TemplateTypes | ranges::views::transform([](String &name) { return "typename " + name; }) | ranges::views::cache1 | ranges::views::join(',') | ranges::to<String>());
            file << ">\n";
        }
        file << "struct " << className << "\n";
        if (!classInfo.BaseType.Name.empty())
        {
            file << "    : public " << classBaseType << "\n";
        }
        file << "{\n";
        file << "    using This = " << className << ";\n";
        if (!classInfo.BaseType.Name.empty())
        {
            file << "    using Super = " << classBaseType << ";\n";
        }
        for (const auto &p : classInfo.Properties)
        {
            file << "    " << writeRecursivelyResolved(p.Type) << " " << p.Name << ";\n";
        }


        bool hasCustomDefaultConstructor = ranges::contains(classInfo.Attributes, "DefaultConstructor");
        if (hasCustomDefaultConstructor)
        {
            file << "    " << className << "();\n";
        }

        if (ranges::contains(classInfo.Attributes, "Copy"))
        {
            if (!hasCustomDefaultConstructor)
            {
                file << "    " << className << "() = default;\n";
                hasCustomDefaultConstructor = true;
            }
            file << "    " << className << "(const " << className << " &other);\n";
            file << "    " << className << " &operator =(const " << className << " &other);\n";
        }
        else if (ranges::contains(classInfo.Attributes, "DefaultCopy"))
        {
            if (!hasCustomDefaultConstructor)
            {
                file << "    " << className << "() = default;\n";
                hasCustomDefaultConstructor = true;
            }
            file << "    " << className << "(const " << className << " &other) = default;\n";
            file << "    " << className << " &operator =(const " << className << " &other) = default;\n";
        }
        else if (ranges::contains(classInfo.Attributes, "DeleteCopy"))
        {
            if (!hasCustomDefaultConstructor)
            {
                file << "    " << className << "() = default;\n";
                hasCustomDefaultConstructor = true;
            }
            file << "    " << className << "(const " << className << " &other) = delete;\n";
            file << "    " << className << " &operator =(const " << className << " &other) = delete;\n";
        }

        if (ranges::contains(classInfo.Attributes, "Move"))
        {
            if (!hasCustomDefaultConstructor)
            {
                file << "    " << className << "() = default;\n";
                hasCustomDefaultConstructor = true;
            }
            file << "    " << className << "(" << className << " &&other);\n";
            file << "    " << className << " &operator =(" << className << " &&other);\n";
        }
        else if (ranges::contains(classInfo.Attributes, "DefaultMove"))
        {
            if (!hasCustomDefaultConstructor)
            {
                file << "    " << className << "() = default;\n";
                hasCustomDefaultConstructor = true;
            }
            file << "    " << className << "(" << className << " &&other) = default;\n";
            file << "    " << className << " &operator =(" << className << " &&other) = default;\n";
        }
        else if (ranges::contains(classInfo.Attributes, "DeleteMove"))
        {
            file << "    " << className << "(" << className << " &&other) = delete;\n";
            file << "    " << className << " &operator =(" << className << " &&other) = delete;\n";
        }

        bool hasCustomDestructor = ranges::contains(classInfo.Attributes, "Destructor");
        if (hasCustomDestructor || !isStruct)
        {
            file << "\n";
            file << "    ";
            if (!isStruct)
            {
                file << "virtual";
            }
            file << " ~" << className << "()";
            if (hasCustomDestructor)
            {
                file << ";";
            }
            else
            {
                file << " {}";
            }
        }

        auto indirectType = writeRecursivelyResolved(classInfo.IndirectType);
        if (!indirectType.empty())
        {
            file << "\n";
            file << "protected:\n";
            file << "    " << indirectType << " *GetIndirectValue();\n";
            file << "public:\n";
            file << "    " << indirectType << " &operator*() { return *GetIndirectValue(); }\n";
            file << "    const " << indirectType << " &operator*() const { return *ConstCast<decltype(this)>(this)->GetIndirectValue(); }\n";
            file << "    " << indirectType << " *operator->() { return GetIndirectValue(); }\n";
            file << "    const " << indirectType << " *operator->() const { return ConstCast<decltype(this)>(this)->GetIndirectValue(); }\n";
        }
        file << "\n";
        file << "    template<typename T>\n";
        file << "    void Serialize(T &&data)\n";
        file << "    {\n";
        for (const auto &p : classInfo.Properties)
        {
            if (ranges::contains(p.Attributes, "Serialize"))
            {
                file << "        data[\"" << p.Name << "\"] & " << p.Name << ";\n";
            }
        }
        file << "    }\n";
        for (const ClassGen::EventInfo &e : classInfo.Events)
        {
            Array<String> parameters = e.InputParameters | ranges::views::transform([](auto &p)
            {
                auto addReference = [&](const String &name) { return p.Copy ? name : (name + " &"); };
                auto addConst = [&](const String &name) { return p.Writable ? name : ("const " + name); };
                return addConst(addReference(writeRecursivelyResolved(p.Type))) + " /*" + p.Name + "*/";
            }) | ranges::to<Array<String>>();

            file << "    Meta::Function<void, " << boost::join(parameters, ", ") << "> " << e.Name << ";\n";
        }
        for (const ClassGen::FunctionInfo &f : classInfo.Functions)
        {
            Array<String> parameters = f.InputParameters | ranges::views::transform([](auto &p)
            {
                auto addReference = [&](const String &name) { return p.Copy ? name : (name + " &"); };
                auto addConst = [&](const String &name) { return p.Writable ? name : ("const " + name); };
                return addConst(addReference(writeRecursivelyResolved(p.Type))) + " " + p.Name;
            }) | ranges::to<Array<String>>();

            auto resolveReturnType = [&]() -> String
            {
                if (f.OutputParameters.empty())
                {
                    return "void";
                }

                Array<String> parameters = f.OutputParameters | ranges::views::transform([](auto &p) { return writeRecursivelyResolved(p.Type) + "/*" + p.Name + "*/"; }) | ranges::to<Array<String>>();
                return "std::tuple<" + boost::join(parameters, ", ") + ">";
            };

            file << "    virtual " << resolveReturnType() << " " << f.Name << "(" << boost::join(parameters, ", ") << ");\n";
        }
        file << "};\n";

        if (!classNamespace.empty())
        {
            file << "}\n";
        }
    }

    if (ImGui::BeginTabBar("##ClassTabBarDetails"))
    {
        if (ImGui::BeginTabItem("Details"))
        {
            RenderDetails(Path, classInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (ImGui::BeginTabBar("##ClassTabBarData"))
    {
        if (ImGui::BeginTabItem("Data"))
        {
            RenderData(Path, classInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    if (g_CurrentGraph)
    {
        ShowGraph(Path);
    }
}
}
