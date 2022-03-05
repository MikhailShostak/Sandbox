#pragma once

#include <portable-file-dialogs.h>

#include "System/Filesystem.hpp"
#include "Text/StringUtils.hpp"

namespace System::Dialogs
{

namespace Details
{

inline Array<String> CreateFilters(const Array<std::pair<String, String>>& Filters)
{
    Array<String> result;

    if (Filters.size() > 1)
    {
        result.push_back("All Supported Files");
        result.push_back(Str::Join(Filters | ranges::views::transform([](const auto& pair) { return "*" + pair.second; }) | ranges::to<Array<String>>(), " "));
    }

    for (const auto& [Title, Extension] : Filters)
    {
        String wildcard = "*" + Extension;
        result.push_back(fmt::format("{} ({})", Title, wildcard));
        result.push_back(std::move(wildcard));
    }

    result.push_back("All Files (*.*)");
    result.push_back("*.*");

    return result;
}

}

enum class Button
{
    Cancel = std::int64_t(pfd::button::cancel),
    Ok = std::int64_t(pfd::button::ok),
    Yes = std::int64_t(pfd::button::yes),
    No = std::int64_t(pfd::button::no),
    Abort = std::int64_t(pfd::button::abort),
    Retry = std::int64_t(pfd::button::retry),
    Ignore = std::int64_t(pfd::button::ignore),
};

enum class Buttons
{
    Ok = std::int64_t(pfd::choice::ok),
    OkCancel = std::int64_t(pfd::choice::ok_cancel),
    YesNo = std::int64_t(pfd::choice::yes_no),
    YesNoCancel = std::int64_t(pfd::choice::yes_no_cancel),
    RetryCancel = std::int64_t(pfd::choice::retry_cancel),
    AbortRetryIgnore = std::int64_t(pfd::choice::abort_retry_ignore),
};

inline Button InfoMessage(const String& Title, const String& Text, Buttons buttons = Buttons::Ok)
{
    pfd::button result = pfd::message(Title, Text, pfd::choice(buttons), pfd::icon::info).result();
    return Button(result);
}

inline Button WarningMessage(const String& Title, const String& Text, Buttons buttons = Buttons::Ok)
{
    pfd::button result = pfd::message(Title, Text, pfd::choice(buttons), pfd::icon::warning).result();
    return Button(result);
}

inline Button ErrorMessage(const String& Title, const String& Text, Buttons buttons = Buttons::Ok)
{
    pfd::button result = pfd::message(Title, Text, pfd::choice(buttons), pfd::icon::error).result();
    return Button(result);
}

inline Button QuestionMessage(const String& Title, const String& Text, Buttons buttons = Buttons::YesNo)
{
    pfd::button result = pfd::message(Title, Text, pfd::choice(buttons), pfd::icon::question).result();
    return Button(result);
}

inline System::Path OpenFile(const String& Title, const Array<std::pair<String, String>>& Filters, const System::Path& DefaultPath)
{
    System::Path resultPath;

    pfd::opt options = !DefaultPath.empty() ? pfd::opt::force_path : pfd::opt::none;
    Array<String> selection = pfd::open_file(Title, System::Path(DefaultPath).make_preferred().string(), Details::CreateFilters(Filters), options).result();
    if (!selection.empty())
    {
        resultPath = std::move(selection[0]);
        resultPath = resultPath.generic_string();
    }

    return resultPath;
}

inline Array<System::Path> OpenFiles(const String& Title, const Array<std::pair<String, String>>& Filters, const System::Path& DefaultPath)
{
    Array<System::Path> resultPaths;

    pfd::opt options = !DefaultPath.empty() ? pfd::opt::force_path : pfd::opt::none;
    options = options | pfd::opt::multiselect;
    Array<String> selection = pfd::open_file(Title, System::Path(DefaultPath).make_preferred().string(), Details::CreateFilters(Filters), options).result();
    for (auto& path : selection)
    {
        System::Path p = std::move(path);
        resultPaths.push_back(p.generic_string());
    }

    return resultPaths;
}

inline System::Path SaveFile(const String& Title, const Array<std::pair<String, String>>& Filters, const System::Path& DefaultPath)
{
    pfd::opt options = !DefaultPath.empty() ? pfd::opt::force_path : pfd::opt::none;
    System::Path resultPath = pfd::save_file(Title, System::Path(DefaultPath).make_preferred().string(), Details::CreateFilters(Filters), options).result();
    resultPath = resultPath.generic_string();
    return resultPath;
}

inline System::Path SelectFolder(const String& Title, const System::Path& DefaultPath)
{
    pfd::opt options = !DefaultPath.empty() ? pfd::opt::force_path : pfd::opt::none;
    System::Path resultPath = pfd::select_folder(Title, System::Path(DefaultPath).make_preferred().string(), options).result();
    resultPath = resultPath.generic_string();
    return resultPath;
}

}
