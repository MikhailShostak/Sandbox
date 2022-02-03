
namespace ClassGen
{

namespace
{

constexpr int ButtonSize = 26;

float padding = 0;
const float PaddingSize = 16;
void PushPadding() { padding += PaddingSize; }
void PopPadding() { padding -= PaddingSize; }
void ApplyPadding() { ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding); }


/*namespace
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
}*/

void IndexFileData(const System::Path &path, const ClassGen::BaseInfo &baseInfo)
{
    return;
    /*auto namespaceName = path.stem().generic_string();
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
    IndexFunctions(classInfo->Functions, namespaceName);*/
}

template<typename Type>
auto SamePointer(const Type& value)
{
    return [&value](auto& item)
    {
        return &item == value;
    };
}

bool DrawTypeEditor(ClassGen::TypeInfo& typeInfo)
{
    ClassGen::FileInfo baseTypeInfo = FindClassByName(typeInfo.Name);
    auto ButtonOffset = !baseTypeInfo.Type.empty() ? -ButtonSize - ImGui::GetStyle().ItemInnerSpacing.x : 0;
    ImGui::PushItemWidth(ButtonOffset - 1);
    String baseType = writeRecursively(typeInfo);
    if (ImGui::InputText(fmt::format("##{}", fmt::ptr(&typeInfo)).data(), &baseType))
    {
        readRecursively(baseType, typeInfo);
        return true;
    }
    if (!baseTypeInfo.Type.empty())
    {
        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().ItemInnerSpacing.x - ImGui::GetStyle().ItemSpacing.x);
        if (ImGui::Button(fmt::format("{}##Navigation{}", ICON_OPEN_IN_NEW, fmt::ptr(&typeInfo)).data()))
        {
            g_ExtensionLibrary.Navigate(baseTypeInfo);
        }
    }
    ImGui::PopItemWidth();
    return false;
}
}

void AssetFileEditor::RenderDetails(const System::Path &path, ClassGen::AssetInfo &assetInfo)
{
    if (ImGui::CollapsingHeader("Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Columns(2);

        ImGui::Text("Namespace");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if (ImGui::InputText("##Namespace", &assetInfo.Namespace))
        {
            IndexFileData(path, assetInfo);
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Base Type");
        ImGui::NextColumn();
        if (DrawTypeEditor(assetInfo.BaseType))
        {
            IndexFileData(path, assetInfo);
            MarkFileDirty(path);
        }
        ImGui::Columns(1);
    }
}

void AssetFileEditor::RenderData(const System::Path &path, ClassGen::AssetInfo &assetInfo)
{
    //TODO: Check FileData
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));

    if (!DataEditor.Changed)
    {
        DataEditor.Value = assetInfo.Values;
        DataEditor.Changed = [&]()
        {
            assetInfo.Values = DataEditor.Value;
            MarkFileDirty(path);
        };
    }
    DataEditor.TypeInfo = assetInfo.BaseType;
    DataEditor.FileInfo = FindClassByName(DataEditor.TypeInfo);
    DataEditor.ID = fmt::format("##PropertyValue{}", fmt::ptr(&DataEditor));

    ImGui::Columns(2);
    DataEditor.DrawAllProperties();
    ImGui::Columns(1);
    ImGui::PopStyleVar();
}

void AssetFileEditor::RenderFile()
{
    auto &fileInfo = Data;
    auto &assetInfo = *std::dynamic_pointer_cast<ClassGen::AssetInfo>(fileInfo.Instance);

    if (ImGui::BeginTabBar("##ClassTabBarDetails"))
    {
        if (ImGui::BeginTabItem("Details"))
        {
            RenderDetails(Path, assetInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (ImGui::BeginTabBar("##ClassTabBarData"))
    {
        if (ImGui::BeginTabItem("Data"))
        {
            RenderData(Path, assetInfo);
            ImGui::EndTabItem();
        }
        if (!assetInfo.Values.empty())
        {
            if (ImGui::BeginTabItem(fmt::format("{}##{}", ICON_DELETE, fmt::ptr(&DataEditor)).data()))
            {
                assetInfo.Values.clear();
                DataEditor.Clear();
                MarkFileDirty(Path);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}
}
