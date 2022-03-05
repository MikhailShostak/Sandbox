
Array<std::pair<String, String>>/*Filters*/ EditorConfig::CreateFilters()
{
    return FileTypes
        | ranges::views::transform([](auto& fileType) { return std::pair<String, String>{ fileType.Title, fileType.Extensions }; })
        | ranges::to<Array<std::pair<String, String>>>();
}
