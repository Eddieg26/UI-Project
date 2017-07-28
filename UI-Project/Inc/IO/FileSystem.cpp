#include "FileSystem.h"
#include "File.h"

#include <Windows.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <sys/stat.h>
#include <shellapi.h>
#include <direct.h>
#include <shlobj.h>

namespace Pyro
{
    int DoSystemRun(const String& fileName, const StringVector arguments) {
        String fixedFileName = GetNativePath(fileName);

#ifdef _WIN32
        // Add .exe extension if no extension defined
        if (GetExtension(fixedFileName).Empty())
            fixedFileName += ".exe";

        String commandLine = "\"" + fixedFileName + "\"";
        for (unsigned i = 0; i < arguments.Size(); ++i)
            commandLine += " " + arguments[i];

        STARTUPINFOW startupInfo;
        PROCESS_INFORMATION processInfo;
        memset(&startupInfo, 0, sizeof(startupInfo));
        memset(&processInfo, 0, sizeof(processInfo));

        WString commandLineW(commandLine);
        if (!CreateProcessW(NULL, (wchar_t*)commandLineW.CString(), 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &startupInfo, &processInfo))
            return -1;

        WaitForSingleObject(processInfo.hProcess, INFINITE);
        DWORD exitCode;
        GetExitCodeProcess(processInfo.hProcess, &exitCode);

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);

        return exitCode;
#endif

        return -1;
    }

    FileSystem::FileSystem(Context* context) :Object(context) {}

    FileSystem::~FileSystem() {}

    bool FileSystem::SetCurrentDir(const String& pathName) {
        if (!CheckAccess(pathName))
            return false;

#ifdef _WIN32
        if (SetCurrentDirectoryW(GetWideNativePath(pathName).CString()) == FALSE)
            return false;
        return true;
#endif

        return false;
    }

    bool FileSystem::CreateDir(const String& pathName) {
        if (!CheckAccess(pathName))
            return false;

        // Create each of the parents if neccessary
        String parentPath = GetParentPath(pathName);
        if (parentPath.Length() > 1 && !DirExists(parentPath)) {
            if (!CreateDir(parentPath))
                return false;
        }

#ifdef _WIN32
        bool success = (CreateDirectoryW(GetWideNativePath(RemoveTrailingSlash(pathName)).CString(), 0) == TRUE) ||
            (GetLastError() == ERROR_ALREADY_EXISTS);
#else
        bool success = false;
#endif

        return success;
    }

    int FileSystem::SystemRun(const String& fileName, const StringVector& arguments) {
        if (!HasRegisteredPaths())
            return DoSystemRun(fileName, arguments);
        else
            return -1;
    }

    bool FileSystem::SystemOpen(const String& fileName, const String& mode) {
        if (HasRegisteredPaths()) return false;

        if (!fileName.StartsWith("http://") && !fileName.StartsWith("https://") && !fileName.StartsWith("file://"))
            if (!FileExists(fileName) && !DirExists(fileName))
                return false;

#ifdef _WIN32
        bool sucess = (size_t)ShellExecuteW(0, !mode.Empty() ? WString(mode).CString() : 0,
            GetWideNativePath(fileName).CString(), 0, 0, SW_SHOW) > 32;
#else
        bool success = false;
#endif

        return sucess;
    }

    bool FileSystem::Copy(const String& srcFileName, const String& destFileName) {
        if (!CheckAccess(GetPath(srcFileName)))
            return false;

        if (!CheckAccess(GetPath(destFileName)))
            return false;

        SharedPtr<File> srcFile(new File(context));
        if (!srcFile->Open(srcFileName, FileMode::Read))
            return false;
        SharedPtr<File> destFile(new File(context));
        if (!destFile->Open(destFileName, FileMode::Write))
            return false;

        unsigned fileSize = srcFile->GetSize();
        SharedArrayPtr<byte> buffer(new byte[fileSize]);

        unsigned bytesRead = srcFile->Read(buffer.Get(), fileSize);
        unsigned bytesWritten = destFile->Write(buffer.Get(), fileSize);
        return bytesRead == fileSize && bytesWritten == fileSize;
    }

    bool FileSystem::Rename(const String& srcFileName, const String& destFileName) {
        if (!CheckAccess(GetPath(srcFileName)))
            return false;

        if (!CheckAccess(GetPath(destFileName)))
            return false;

#ifdef _WIN32
        return MoveFileW(GetWideNativePath(srcFileName).CString(), GetWideNativePath(destFileName).CString()) != 0;
#endif

        return false;
    }

    bool FileSystem::Delete(const String& fileName) {
        if (!CheckAccess(GetPath(fileName)))
            return false;

#ifdef _WIN32
        return DeleteFileW(GetWideNativePath(fileName).CString()) != 0;
#endif

        return false;
    }

    void FileSystem::RegisterPath(const String& pathName) {
        if (pathName.Empty() || m_vAllowedPaths.Contains(pathName))
            return;

        m_vAllowedPaths.Add(pathName);
    }

    bool FileSystem::SetLastModifiedTime(const String& fileName, unsigned newTime) {
#ifdef _WIN32
        struct _stat oldTime;
        struct _utimbuf newTimes;
        if (_stat(fileName.CString(), &oldTime) != 0)
            return false;
        newTimes.actime = oldTime.st_atime;
        newTimes.modtime = newTime;
        return _utime(fileName.CString(), &newTimes) == 0;
#endif

        return false;
    }

    String FileSystem::GetCurrentDir() const {
#ifdef _WIN32
        wchar_t path[MAX_PATH];
        path[0] = 0;
        GetCurrentDirectoryW(MAX_PATH, path);
        return AddTrailingSlash(String(path));
#endif

        return String::EMPTY;
    }

    bool FileSystem::CheckAccess(const String& pathName) const {
        // If no allowed directories defined, succeed always
        if (!HasRegisteredPaths()) return true;

        String fixedPath = AddTrailingSlash(pathName);

        // If there is any attempt to go to a parent directory, disallow
        if (fixedPath.Contains(".."))
            return false;

        // Check if the path is a partial match of any of the allowed directories
        for (unsigned i = 0; i < m_vAllowedPaths.Size(); ++i) {
            if (m_vAllowedPaths[i].Find(fixedPath) == 0)
                return true;
        }

        // Not found, so disallow
        return false;
    }

    unsigned FileSystem::GetLastModifiedTime(const String& fileName) const {
        if (fileName.Empty() || !CheckAccess(fileName))
            return 0;

#ifdef _WIN32
        struct _stat st;
        if (!_stat(fileName.CString(), &st))
            return (unsigned)st.st_mtime;
        else
            return 0;
#endif

        return 0;
    }

    bool FileSystem::FileExists(const String& fileName) const {
        if (!CheckAccess(GetPath(fileName)))
            return false;

        String fixedName = GetNativePath(RemoveTrailingSlash(fileName));

#ifdef _WIN32
        DWORD attributes = GetFileAttributesW(WString(fixedName).CString());
        if (attributes == INVALID_FILE_ATTRIBUTES || attributes & FILE_ATTRIBUTE_DIRECTORY)
            return false;
#endif

        return true;
    }

    bool FileSystem::DirExists(const String& pathName) const {

        if (!CheckAccess(pathName))
            return false;

#ifndef _WIN32
        // Always return true for the root directory
        if (pathName == "/")
            return true;
#endif

        String fixedName = GetNativePath(RemoveTrailingSlash(pathName));

#ifdef _WIN32
        DWORD attributes = GetFileAttributesW(WString(fixedName).CString());
        if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY))
            return false;
#endif

        return true;
    }

    void FileSystem::ScanDir(StringVector& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const {
        result.Clear();

        if (CheckAccess(pathName)) {
            String initialPath = AddTrailingSlash(pathName);
            ScanDirInternal(result, initialPath, initialPath, filter, flags, recursive);
        }
    }

    String FileSystem::GetProgramDir() const {
        // Return cached value if possible
        if (!m_sProgramDir.Empty())
            return m_sProgramDir;

#if defined(_WIN32)
        wchar_t exeName[MAX_PATH];
        exeName[0] = 0;
        GetModuleFileNameW(0, exeName, MAX_PATH);
        m_sProgramDir = GetPath(String(exeName));
#endif

        // If the executable directory does not contain Assets & Program Settings directories, but the current working directory does, use the
        // current working directory instead
        //String currentDir = GetCurrentDir();
        //if (!DirExists(m_sProgramDir + "Assets") && !DirExists(m_sProgramDir + "Program Settings") &&
        //	(DirExists(currentDir + "Assets") || DirExists(currentDir + "Program Settings")))
        //	m_sProgramDir = currentDir;

        // Sanitate /./ construct away
        m_sProgramDir.Replace("/./", "/");

        return m_sProgramDir;
    }

    String FileSystem::GetUserDocumentsDir() const {

#if defined(_WIN32)
        wchar_t pathName[MAX_PATH];
        pathName[0] = 0;
        SHGetSpecialFolderPathW(0, pathName, CSIDL_PERSONAL, 0);
        return AddTrailingSlash(String(pathName));
#endif

        return String::EMPTY;
    }

    String FileSystem::GetAppPreferencesDir() const {

#if defined(_WIN32)
        wchar_t pathName[MAX_PATH];
        pathName[0] = 0;
        SHGetSpecialFolderPathW(0, pathName, CSIDL_COMMON_APPDATA, false);
        return AddTrailingSlash(String(pathName));
#endif

        return String::EMPTY;
    }

    bool FileSystem::CopyDir(const String& directoryIn, const String& directoryOut) {
        if (FileExists(directoryOut) || DirExists(directoryOut))
            return false;

        StringVector results;
        ScanDir(results, directoryIn, "*", SCAN_FILES, true);

        for (unsigned i = 0; i < results.Size(); i++)
        {
            String srcFile = directoryIn + "/" + results[i];
            String dstFile = directoryOut + "/" + results[i];

            String dstPath = GetPath(dstFile);

            if (!CreateDirsRecursive(dstPath))
                return false;

            if (!Copy(srcFile, dstFile))
                return false;
        }

        return true;
    }

    bool FileSystem::CreateDirs(const String& root, const String& subdirectory) {
        String folder = AddTrailingSlash(GetInternalPath(root));
        String sub = GetInternalPath(subdirectory);
        StringVector subs = sub.Split('/');

        for (unsigned i = 0; i < subs.Size(); i++)
        {
            folder += subs[i];
            folder += "/";

            if (DirExists(folder))
                continue;

            CreateDir(folder);

            if (!DirExists(folder))
                return false;
        }

        return true;
    }

    bool FileSystem::CreateDirsRecursive(const String& directoryIn) {
        String directory = AddTrailingSlash(GetInternalPath(directoryIn));

        if (DirExists(directory))
            return true;

        if (FileExists(directory))
            return false;

        String parentPath = directory;

        StringVector paths;

        paths.Add(directory);

        while (true) {
            parentPath = GetParentPath(parentPath);

            if (!parentPath.Length())
                break;

            paths.Add(parentPath);
        }

        if (!paths.Size())
            return false;

        for (int i = (int)(paths.Size() - 1); i >= 0; i--) {
            const String& pathName = paths[i];

            if (FileExists(pathName))
                return false;

            if (DirExists(pathName))
                continue;

            if (!CreateDir(pathName))
                return false;

            // double check
            if (!DirExists(pathName))
                return false;
        }

        return true;
    }

    bool FileSystem::RemoveDir(const String& directoryIn, bool recursive) {
        String directory = AddTrailingSlash(directoryIn);

        if (!DirExists(directory))
            return false;

        StringVector results;

        // ensure empty if not recursive
        if (!recursive) {
            ScanDir(results, directory, "*", SCAN_DIRS | SCAN_FILES | SCAN_HIDDEN, true);
            while (results.Remove(".")) {}
            while (results.Remove("..")) {}

            if (results.Size())
                return false;

            return RemoveDirectoryW(GetWideNativePath(directory).CString()) != 0;
        }

        // delete all files at this level
        ScanDir(results, directory, "*", SCAN_FILES | SCAN_HIDDEN, false);
        for (unsigned i = 0; i < results.Size(); ++i) {
            if (!Delete(directory + results[i]))
                return false;
        }

        results.Clear();

        // recurse into subfolders
        ScanDir(results, directory, "*", SCAN_DIRS, false);
        for (unsigned i = 0; i < results.Size(); ++i) {
            if (results[i] == "." || results[i] == "..")
                continue;

            if (!RemoveDir(directory + results[i], true))
                return false;
        }

        return RemoveDir(directory, false);
    }

    void FileSystem::ScanDirInternal(StringVector& result, String path, const String& startPath, const String& filter, unsigned flags, bool recursive) const {
        path = AddTrailingSlash(path);
        String deltaPath;
        if (path.Length() > startPath.Length())
            deltaPath = path.SubString(startPath.Length());

        String filterExtension = filter.SubString(filter.FindLast('.'));

        if (filterExtension.Contains('*'))
            filterExtension.Clear();

#ifdef _WIN32
        WIN32_FIND_DATAW info;
        HANDLE handle = FindFirstFileW(WString(path + "*").CString(), &info);
        if (handle != INVALID_HANDLE_VALUE) {
            do {
                String fileName(info.cFileName);
                if (!fileName.Empty()) {
                    if (info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN && !(flags & SCAN_HIDDEN))
                        continue;
                    if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        if (flags & SCAN_DIRS)
                            result.Add(deltaPath + fileName);
                        if (recursive && fileName != "." && fileName != "..")
                            ScanDirInternal(result, path + fileName, startPath, filter, flags, recursive);
                    }
                    else if (flags & SCAN_FILES) {
                        if (filterExtension.Empty() || fileName.EndsWith(filterExtension))
                            result.Add(deltaPath + fileName);
                    }
                }
            } while (FindNextFileW(handle, &info));

            FindClose(handle);
        }
#endif
    }

    void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension, bool lowercaseExtension)
    {
        String fullPathCopy = GetInternalPath(fullPath);

        unsigned extPos = fullPathCopy.FindLast('.');
        unsigned pathPos = fullPathCopy.FindLast('/');

        if (extPos != String::NPOS && (pathPos == String::NPOS || extPos > pathPos)) {
            extension = fullPathCopy.SubString(extPos);
            if (lowercaseExtension)
                extension = extension.ToLower();
            fullPathCopy = fullPathCopy.SubString(0, extPos);
        }
        else
            extension.Clear();

        pathPos = fullPathCopy.FindLast('/');
        if (pathPos != String::NPOS) {
            fileName = fullPathCopy.SubString(pathPos + 1);
            pathName = fullPathCopy.SubString(0, pathPos + 1);
        }
        else {
            fileName = fullPathCopy;
            pathName.Clear();
        }
    }

    String GetPath(const String& fullPath) {
        String path, file, extension;
        SplitPath(fullPath, path, file, extension);
        return path;
    }

    String GetFileName(const String& fullPath) {
        String path, file, extension;
        SplitPath(fullPath, path, file, extension);
        return file;
    }

    String GetExtension(const String& fullPath, bool lowercaseExtension) {
        String path, file, extension;
        SplitPath(fullPath, path, file, extension, lowercaseExtension);
        return extension;
    }

    String GetFileNameAndExtension(const String& fileName, bool lowercaseExtension) {
        String path, file, extension;
        SplitPath(fileName, path, file, extension, lowercaseExtension);
        return file + extension;
    }

    String ReplaceExtension(const String& fullPath, const String& newExtension) {
        String path, file, extension;
        SplitPath(fullPath, path, file, extension);
        return path + file + newExtension;
    }

    String AddTrailingSlash(const String& pathName) {
        String ret = pathName.Trimmed();
        ret.Replace('\\', '/');
        if (!ret.Empty() && ret.Back() != '/')
            ret += '/';
        return ret;
    }

    String RemoveTrailingSlash(const String& pathName) {
        String ret = pathName.Trimmed();
        ret.Replace('\\', '/');
        if (!ret.Empty() && ret.Back() == '/')
            ret.Resize(ret.Length() - 1);
        return ret;
    }

    String GetParentPath(const String& path) {
        unsigned pos = RemoveTrailingSlash(path).FindLast('/');
        if (pos != String::NPOS)
            return path.SubString(0, pos + 1);
        else
            return String();
    }

    String GetInternalPath(const String& pathName) {
        return pathName.Replaced('\\', '/');
    }

    String GetNativePath(const String& pathName) {
#ifdef _WIN32
        return pathName.Replaced('/', '\\');
#else
        return pathName;
#endif
    }

    WString GetWideNativePath(const String& pathName) {
#ifdef _WIN32
        return WString(pathName.Replaced('/', '\\'));
#else
        return WString(pathName);
#endif
    }

    bool IsAbsolutePath(const String& pathName) {
        if (pathName.Empty())
            return false;

        String path = GetInternalPath(pathName);

        if (path[0] == '/')
            return true;

#ifdef _WIN32
        if (path.Length() > 1 && isalpha(path[0]) && path[1] == ':')
            return true;
#endif

        return false;
    }

    bool IsAbsoluteParentPath(const String& absParentPath, const String& fullPath) {
        if (!IsAbsolutePath(absParentPath) || !IsAbsolutePath(fullPath))
            return false;

        String path1 = AddTrailingSlash(GetSanitizedPath(absParentPath));
        String path2 = AddTrailingSlash(GetSanitizedPath(GetPath(fullPath)));

        if (path2.StartsWith(path1))
            return true;

        return false;
    }

    String GetSanitizedPath(const String& path) {
        String sanitized = GetInternalPath(path);
        StringVector parts = sanitized.Split('/');

        bool hasTrailingSlash = path.EndsWith("/") || path.EndsWith("\\");

#ifdef _WIN32
        bool absolute = IsAbsolutePath(path);
        sanitized = String::Joined(parts, "/");
        if (absolute)
            sanitized = "/" + sanitized;
#else
        sanitized = String::Joined(parts, "/");
#endif

        if (hasTrailingSlash)
            sanitized += "/";

        return sanitized;
    }

    bool GetRelativePath(const String& fromPath, const String& toPath, String& output) {
        output = String::EMPTY;

        String from = GetSanitizedPath(fromPath);
        String to = GetSanitizedPath(toPath);

        StringVector fromParts = from.Split('/');
        StringVector toParts = to.Split('/');

        if (!fromParts.Size() || !toParts.Size())
            return false;

        if (fromParts == toParts) {
            return true;
        }

        // no common base?
        if (fromParts[0] != toParts[0])
            return false;

        unsigned startIdx;

        for (startIdx = 0; startIdx < toParts.Size(); startIdx++) {
            if (startIdx >= fromParts.Size() || fromParts[startIdx] != toParts[startIdx])
                break;
        }

        if (startIdx == toParts.Size())
            return false;

        for (unsigned i = 0; i < fromParts.Size() - startIdx; i++) {
            output += "../";
        }

        for (unsigned i = startIdx; i < toParts.Size(); i++) {
            output += toParts[i] + "/";
        }

        return true;
    }
}




















