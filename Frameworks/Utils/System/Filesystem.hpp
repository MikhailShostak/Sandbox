#pragma once

#include <filesystem>

#include "Meta/Flags.hpp"

namespace System
{

using Path = std::filesystem::path;
using Directory = std::filesystem::directory_entry;
using DirectoryIterator = std::filesystem::recursive_directory_iterator;
using RecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;

using FileStatus = std::filesystem::file_status;
using SpaceInfo = std::filesystem::space_info;

enum class CopyOptions
{
    None = std::int64_t(std::filesystem::copy_options::none),

    SkipExisting = std::int64_t(std::filesystem::copy_options::skip_existing),
    OverwriteExisting = std::int64_t(std::filesystem::copy_options::overwrite_existing),
    UpdateExisting = std::int64_t(std::filesystem::copy_options::update_existing),

    Recursive = std::int64_t(std::filesystem::copy_options::recursive),

    CopySymlinks = std::int64_t(std::filesystem::copy_options::copy_symlinks),
    SkipSymlinks = std::int64_t(std::filesystem::copy_options::skip_symlinks),

    DirectoriesOnly = std::int64_t(std::filesystem::copy_options::directories_only),
    CreateSymlinks = std::int64_t(std::filesystem::copy_options::create_symlinks),
    CreateHardLinks = std::int64_t(std::filesystem::copy_options::create_hard_links),
};
DECLARE_FLAG_OPERATORS(CopyOptions)

enum class Permissions {
    None = std::int64_t(std::filesystem::perms::none),

    OwnerExecute = std::int64_t(std::filesystem::perms::owner_exec),
    OwnerRead = std::int64_t(std::filesystem::perms::owner_read),
    OwnerWrite = std::int64_t(std::filesystem::perms::owner_write),
    OwnerReadWrite = OwnerRead | OwnerWrite,
    OwnerReadExecute = OwnerRead | OwnerExecute,
    OwnerAll = OwnerExecute | OwnerReadWrite,

    GroupExecute = std::int64_t(std::filesystem::perms::group_exec),
    GroupRead = std::int64_t(std::filesystem::perms::group_read),
    GroupWrite = std::int64_t(std::filesystem::perms::group_write),
    GroupReadWrite = GroupRead | GroupWrite,
    GroupReadExecute = GroupRead | GroupExecute,
    GroupAll = GroupExecute | GroupReadWrite,

    OthersExecute = std::int64_t(std::filesystem::perms::others_exec),
    OthersRead = std::int64_t(std::filesystem::perms::others_read),
    OthersWrite = std::int64_t(std::filesystem::perms::others_write),
    OthersReadWrite = OthersRead | OthersWrite,
    OthersReadExecute = OthersRead | OthersExecute,
    OthersAll = OthersExecute | OthersReadWrite,

    ShareReadToGroup = OwnerAll | GroupReadExecute,
    ShareWriteToGroup = OwnerAll | GroupAll,

    ShareReadToEveryone = ShareReadToGroup | OthersReadExecute,
    ShareWriteToEveryone = ShareWriteToGroup | OthersAll,

    All = std::int64_t(std::filesystem::perms::all),
    SetUserID = std::int64_t(std::filesystem::perms::set_uid),
    SetGroupID = std::int64_t(std::filesystem::perms::set_gid),
    StickyBit = std::int64_t(std::filesystem::perms::sticky_bit),
    Mask = std::int64_t(std::filesystem::perms::mask),
    Unknown = std::int64_t(std::filesystem::perms::unknown),
};
DECLARE_FLAG_OPERATORS(Permissions)

enum class PermissionOptions
{
    Replace = std::int64_t(std::filesystem::perm_options::replace),
    Add = std::int64_t(std::filesystem::perm_options::add),
    Remove = std::int64_t(std::filesystem::perm_options::remove),
    ChangeSymlinkRatherTarget = std::int64_t(std::filesystem::perm_options::nofollow),
};
DECLARE_FLAG_OPERATORS(PermissionOptions)

using FileTime = std::filesystem::file_time_type;

inline Path GetWorkingDirectory() { return std::filesystem::current_path(); }
inline Path GetWorkingDirectory(std::error_code& error_code) { return std::filesystem::current_path(error_code); }

inline void SetWorkingDirectory(const Path& path) { std::filesystem::current_path(path); }
inline void SetWorkingDirectory(const Path& path, std::error_code& error_code) noexcept { std::filesystem::current_path(path, error_code); }

inline Path GetAbsolute(const Path& path) { return std::filesystem::absolute(path); }
inline Path GetAbsolute(const Path& path, std::error_code& error_code) { return std::filesystem::absolute(path, error_code); }

inline Path GetCanonical(const Path& path) { return std::filesystem::canonical(path); }
inline Path GetCanonical(const Path& path, std::error_code& error_code) { return std::filesystem::canonical(path, error_code); }

inline Path GetProximate(const Path& path, std::error_code& error_code) { return std::filesystem::proximate(path, error_code); }
inline Path GetProximate(const Path& path, const Path& base = GetWorkingDirectory()) { return std::filesystem::proximate(path, base); }
inline Path GetProximate(const Path& path, const Path& base, std::error_code& error_code) { return std::filesystem::proximate(path, base, error_code); }

inline Path GetRelative(const Path& path, std::error_code& error_code) { return std::filesystem::relative(path, error_code); }
inline Path GetRelative(const Path& path, const Path& base = GetWorkingDirectory()) { return std::filesystem::relative(path, base); }
inline Path GetRelative(const Path& path, const Path& base, std::error_code& error_code) { return std::filesystem::relative(path, base, error_code); }

inline Path GetWeaklyCanonical(const Path& path) { return std::filesystem::weakly_canonical(path); }
inline Path GetWeaklyCanonical(const Path& path, std::error_code& error_code) { return std::filesystem::weakly_canonical(path, error_code); }

inline Path ResolveSymlink(const Path& path) { return std::filesystem::read_symlink(path); }
inline Path ResolveSymlink(const Path& path, std::error_code& error_code) { return std::filesystem::read_symlink(path, error_code); }

inline Path GetTempDirectoryPath() { return std::filesystem::temp_directory_path(); }
inline Path GetTempDirectoryPath(std::error_code& error_code) { return std::filesystem::temp_directory_path(error_code); }

inline bool Equivalent(const Path& p1, const Path& p2) { return std::filesystem::equivalent(p1, p2); }
inline bool Equivalent(const Path& p1, const Path& p2, std::error_code& error_code) noexcept { return std::filesystem::equivalent(p1, p2, error_code); }

inline bool IsExists(FileStatus status) noexcept { return std::filesystem::exists(status); }
inline bool IsExists(const Path& path) { return std::filesystem::exists(path); }
inline bool IsExists(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::exists(path, error_code); }

inline bool IsBlockFile(FileStatus status) noexcept { return std::filesystem::is_block_file(status); }
inline bool IsBlockFile(const Path& path) { return std::filesystem::is_block_file(path); }
inline bool IsBlockFile(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_block_file(path, error_code); }

inline bool IsCharacterFile(FileStatus status) noexcept { return std::filesystem::is_character_file(status); }
inline bool IsCharacterFile(const Path& path) { return std::filesystem::is_character_file(path); }
inline bool IsCharacterFile(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_character_file(path, error_code); }

inline bool IsDirectory(FileStatus status) noexcept { return std::filesystem::is_directory(status); }
inline bool IsDirectory(const Path& path) { return std::filesystem::is_directory(path); }
inline bool IsDirectory(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_directory(path, error_code); }

inline bool IsEmpty(const Path& path) { return std::filesystem::is_empty(path); }
inline bool IsEmpty(const Path& path, std::error_code& error_code) { return std::filesystem::is_empty(path, error_code); }

inline bool IsFIFO(FileStatus status) noexcept { return std::filesystem::is_fifo(status); }
inline bool IsFIFO(const Path& path) { return std::filesystem::is_fifo(path); }
inline bool IsFIFO(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_fifo(path, error_code); }

inline bool IsOther(FileStatus status) noexcept { return std::filesystem::is_other(status); }
inline bool IsOther(const Path& path) { return std::filesystem::is_other(path); }
inline bool IsOther(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_other(path, error_code); }

inline bool IsRegularFile(FileStatus status) noexcept { return std::filesystem::is_regular_file(status); }
inline bool IsRegularFile(const Path& path) { return std::filesystem::is_regular_file(path); }
inline bool IsRegularFile(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_regular_file(path, error_code); }

inline bool IsSocket(FileStatus status) noexcept { return std::filesystem::is_socket(status); }
inline bool IsSocket(const Path& path) { return std::filesystem::is_socket(path); }
inline bool IsSocket(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_socket(path, error_code); }

inline bool IsSymlink(FileStatus status) noexcept { return std::filesystem::is_symlink(status); }
inline bool IsSymlink(const Path& path) { return std::filesystem::is_symlink(path); }
inline bool IsSymlink(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::is_symlink(path, error_code); }

inline uintmax_t GetFileSize(const Path& path) { return std::filesystem::file_size(path); }
inline uintmax_t GetFileSize(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::file_size(path, error_code); }

inline FileTime GetLastWriteTime(const Path& path) { return std::filesystem::last_write_time(path); }
inline FileTime GetLastWriteTime(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::last_write_time(path, error_code); }
inline void SetLastWriteTime(const Path& path, FileTime new_time) { std::filesystem::last_write_time(path, new_time); }
inline void SetLastWriteTime(const Path& path, FileTime new_time, std::error_code& error_code) noexcept { std::filesystem::last_write_time(path, new_time); }

inline SpaceInfo GetSpaceInfo(const Path& path) { return std::filesystem::space(path); }
inline SpaceInfo GetSpaceInfo(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::space(path, error_code); }

inline FileStatus GetStatus(const Path& path) { return std::filesystem::status(path); }
inline FileStatus GetStatus(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::status(path, error_code); }

inline bool IsStatusKnown(FileStatus status) noexcept { return std::filesystem::status_known(status); }

inline uintmax_t GetHardLinkCount(const Path& path) { return std::filesystem::hard_link_count(path); }
inline uintmax_t GetHardLinkCount(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::hard_link_count(path, error_code); }

inline FileStatus GetSymlinkStatus(const Path& path) { return std::filesystem::symlink_status(path); }
inline FileStatus GetSymlinkStatus(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::symlink_status(path, error_code); }

inline void SetPermissions(const Path& path, Permissions permissions, PermissionOptions options = PermissionOptions::Replace) { std::filesystem::permissions(path, std::filesystem::perms(permissions), std::filesystem::perm_options(options)); }
inline void SetPermissions(const Path& path, Permissions permissions, std::error_code& error_code) noexcept { std::filesystem::permissions(path, std::filesystem::perms(permissions), error_code); }
inline void SetPermissions(const Path& path, Permissions permissions, PermissionOptions options, std::error_code& error_code) { std::filesystem::permissions(path, std::filesystem::perms(permissions), std::filesystem::perm_options(options), error_code); }

inline void Copy(const Path& from, const Path& to) { std::filesystem::copy(from, to); }
inline void Copy(const Path& from, const Path& to, std::error_code& error_code) { std::filesystem::copy(from, to, error_code); }
inline void Copy(const Path& from, const Path& to, CopyOptions options) { std::filesystem::copy(from, to, std::filesystem::copy_options(options)); }
inline void Copy(const Path& from, const Path& to, CopyOptions options, std::error_code& error_code) { std::filesystem::copy(from, to, std::filesystem::copy_options(options), error_code); }

inline bool CopyFile(const Path& from, const Path& to) { return std::filesystem::copy_file(from, to); }
inline bool CopyFile(const Path& from, const Path& to, std::error_code& error_code) { return std::filesystem::copy_file(from, to, error_code); }
inline bool CopyFile(const Path& from, const Path& to, CopyOptions options) { return std::filesystem::copy_file(from, to, std::filesystem::copy_options(options)); }
inline bool CopyFile(const Path& from, const Path& to, CopyOptions options, std::error_code& error_code) { return std::filesystem::copy_file(from, to, std::filesystem::copy_options(options), error_code); }

inline void CopySymlink(const Path& existing_symlink, const Path& new_symlink) { std::filesystem::copy_symlink(existing_symlink, new_symlink); }
inline void CopySymlink(const Path& existing_symlink, const Path& new_symlink, std::error_code& error_code) noexcept { std::filesystem::copy_symlink(existing_symlink, new_symlink, error_code); }

inline bool CreateDirectories(const Path& path) { return std::filesystem::create_directories(path); }
inline bool CreateDirectories(const Path& path, std::error_code& error_code) { return std::filesystem::create_directories(path, error_code); }

inline bool CreateDirectory(const Path& path) { return std::filesystem::create_directory(path); }
inline bool CreateDirectory(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::create_directory(path, error_code); }

inline bool CreateDirectory(const Path& path, const Path& attributes) { return std::filesystem::create_directory(path, attributes); }
inline bool CreateDirectory(const Path& path, const Path& attributes, std::error_code& error_code) noexcept { return std::filesystem::create_directory(path, attributes, error_code); }

inline void CreateDirectorySymlink(const Path& to, const Path& new_symlink) { std::filesystem::create_directory_symlink(to, new_symlink); }
inline void CreateDirectorySymlink(const Path& to, const Path& new_symlink, std::error_code& error_code) noexcept { std::filesystem::create_directory_symlink(to, new_symlink, error_code); }

inline void CreateHardLink(const Path& to, const Path& new_hard_link) { std::filesystem::create_hard_link(to, new_hard_link); }
inline void CreateHardLink(const Path& to, const Path& new_hard_link, std::error_code& error_code) noexcept { std::filesystem::create_hard_link(to, new_hard_link, error_code); }

inline void CreateSymlink(const Path& to, const Path& new_symlink) { std::filesystem::create_symlink(to, new_symlink); }
inline void CreateSymlink(const Path& to, const Path& new_symlink, std::error_code& error_code) noexcept { std::filesystem::create_symlink(to, new_symlink, error_code); }

inline void Rename(const Path& from, const Path& to) { std::filesystem::rename(from, to); }
inline void Rename(const Path& from, const Path& to, std::error_code& error_code) noexcept { std::filesystem::rename(from, to); }

inline void ResizeFile(const Path& path, uintmax_t size) { std::filesystem::resize_file(path, size); }
inline void ResizeFile(const Path& path, uintmax_t size, std::error_code& error_code) noexcept { std::filesystem::resize_file(path, size, error_code); }

inline bool Remove(const Path& path) { return std::filesystem::remove(path); }
inline bool Remove(const Path& path, std::error_code& error_code) noexcept { return std::filesystem::remove(path, error_code); }

inline uintmax_t RemoveAll(const Path& path) { return std::filesystem::remove_all(path); }
inline uintmax_t RemoveAll(const Path& path, std::error_code& error_code) { return std::filesystem::remove_all(path, error_code); }

}
