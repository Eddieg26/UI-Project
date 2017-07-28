#pragma once

#include "../Core/Object.h"
#include "../Containers/Str.h"

namespace Pyro
{
    /// Return files.
    static const uint SCAN_FILES = 0x1;
    /// Return directories.
    static const uint SCAN_DIRS = 0x2;
    /// Return also hidden files.
    static const uint SCAN_HIDDEN = 0x4;

    class FileSystem : public Object {

        PYRO_OBJECT(FileSystem, Object)

    private:
        /// Allowed directories
        StringVector m_vAllowedPaths;
        /// Program directory
        mutable String m_sProgramDir;

    public:
        /// Construct
        FileSystem(Context* context);
        /// Destruct
        ~FileSystem();

        /// Set the current working directory.
        bool SetCurrentDir(const String& pathName);
        /// Create a directory.
        bool CreateDir(const String& pathName);
        /// Run a specific program, block until it exits and return the exit code. Will fail if any allowed paths are defined.
        int SystemRun(const String& fileName, const StringVector& arguments);
        /// Open a file in an external program, with mode such as "edit" optionally specified. Will fail if any allowed paths are defined.
        bool SystemOpen(const String& fileName, const String& mode = String::EMPTY);
        /// Copy a file. Return true if successful.
        bool Copy(const String& srcFileName, const String& destFileName);
        /// Rename a file. Return true if successful.
        bool Rename(const String& srcFileName, const String& destFileName);
        /// Delete a file. Return true if successful.
        bool Delete(const String& fileName);
        /// Register a path as allowed to access. If no paths are registered, all are allowed. Registering allowed paths is considered securing the execution environment: running programs and opening files externally through the system will fail afterward.
        void RegisterPath(const String& pathName);
        /// Set a file's last modified time as seconds since 1.1.1970. Return true on success.
        bool SetLastModifiedTime(const String& fileName, unsigned newTime);

        /// Return the absolute current working directory.
        String GetCurrentDir() const;

        /// Return whether paths have been registered.
        bool HasRegisteredPaths() const { return m_vAllowedPaths.Size() > 0; }

        /// Check if a path is allowed to be accessed. If no paths are registered, all are allowed.
        bool CheckAccess(const String& pathName) const;
        /// Returns the file's last modified time as seconds since 1.1.1970, or 0 if can not be accessed.
        uint GetLastModifiedTime(const String& fileName) const;
        /// Check if a file exists.
        bool FileExists(const String& fileName) const;
        /// Check if a directory exists.
        bool DirExists(const String& pathName) const;
        /// Scan a directory for specified files.
        void ScanDir(StringVector& result, const String& pathName, const String& filter, uint flags, bool recursive) const;
        /// Return the program's directory. If it does not contain the default Assets and Project Settings directories, and the current working directory does, return the working directory instead.
        String GetProgramDir() const;
        /// Return the user documents directory.
        String GetUserDocumentsDir() const;
        /// Return the application preferences directory.
        String GetAppPreferencesDir() const;

        /// Check if a file or directory exists at the specified path
        bool Exists(const String& pathName) const { return FileExists(pathName) || DirExists(pathName); }

        bool CopyDir(const String& directoryIn, const String& directoryOut);

        bool CreateDirs(const String& root, const String& subdirectory);
        bool CreateDirsRecursive(const String& directoryIn);

        bool RemoveDir(const String& directoryIn, bool recursive);

    private:
        /// Scan directory, called internally.
        void ScanDirInternal(StringVector& result, String path, const String& startPath, const String& filter, unsigned flags, bool recursive) const;
    };

    /// Split a full path to path, filename and extension. The extension will be converted to lowercase by default.
    void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension, bool lowercaseExtension = true);
    /// Return the path from a full path.
    String GetPath(const String& fullPath);
    /// Return the filename from a full path.
    String GetFileName(const String& fullPath);
    /// Return the extension from a full path, converted to lowercase by default.
    String GetExtension(const String& fullPath, bool lowercaseExtension = true);
    /// Return the filename and extension from a full path. The case of the extension is preserved by default, so that the file can be opened in case-sensitive operating systems.
    String GetFileNameAndExtension(const String& fullPath, bool lowercaseExtension = false);
    /// Replace the extension of a file name with another.
    String ReplaceExtension(const String& fullPath, const String& newExtension);
    /// Add a slash at the end of the path if missing and convert to internal format (use slashes.)
    String AddTrailingSlash(const String& pathName);
    /// Remove the slash from the end of a path if exists and convert to internal format (use slashes.)
    String RemoveTrailingSlash(const String& pathName);
    /// Return the parent path, or the path itself if not available.
    String GetParentPath(const String& pathName);
    /// Convert a path to internal format (use slashes.)
    String GetInternalPath(const String& pathName);
    /// Convert a path to the format required by the operating system.
    String GetNativePath(const String& pathName);
    /// Convert a path to the format required by the operating system in wide characters.
    WString GetWideNativePath(const String& pathName);
    /// Return whether a path is absolute.
    bool IsAbsolutePath(const String& pathName);

    // ATOMIC BEGIN
    bool IsAbsoluteParentPath(const String& absParentPath, const String& fullPath);
    String GetSanitizedPath(const String& path);

    /// Given two absolute directory paths, get the relative path from one to the other
    /// Returns false if either path isn't absolute, or if they are unrelated
    bool GetRelativePath(const String& fromPath, const String& toPath, String& output);
}