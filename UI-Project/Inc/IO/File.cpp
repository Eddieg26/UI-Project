#include "File.h"
#include "FileSystem.h"
#include "../Math/Mathf.h"

#include <cstdio>

namespace Pyro
{
    static const wchar_t* openMode[] =
    {
        L"rb",
        L"wb",
        L"r+b",
        L"w+b",
        L"a+b"
    };

    File::File(Context* _context) :
        Object(_context),
        handle(nullptr),
        readSyncNeeded(false),
        writeSyncNeeded(false),
        fileName(String::EMPTY),
        fullPath(String::EMPTY),
        mode(FileMode::Read) {}

    File::File(Context* _context, const String& fileName, FileMode mode) :
        Object(_context),
        handle(nullptr),
        readSyncNeeded(false),
        writeSyncNeeded(false),
        fileName(fileName),
        fullPath(String::EMPTY),
        mode(mode) {
        Open(fileName, mode);
    }

    File::~File() {
        Close();
    }

    uint32 File::Read(void* dest, uint32 size) {
        if (!IsOpen())
            return 0;

        // File is not open for reading
        if (mode == FileMode::Write)
            return 0;

        if (size + position > this->size)
            size = this->size - position;
        if (!size)
            return 0;

        if (readSyncNeeded) {
            SeekInternal(position);
            readSyncNeeded = false;
        }

        if (!ReadInternal(dest, size)) {
            // Return to the position where the read began
            SeekInternal(position);
            return 0;
        }

        writeSyncNeeded = true;
        position += size;
        return size;
    }

    uint32 File::Seek(uint32 pos) {
        if (!IsOpen())
            return 0;

        if (mode == FileMode::Read && pos > size)
            pos = size;

        SeekInternal(pos);
        position = pos;
        readSyncNeeded = false;
        writeSyncNeeded = false;
        position = pos;
        return position;
    }

    uint32 File::Write(const void* data, uint32 size) {
        if (!IsOpen())
            return 0;

        // File is not open for writing
        if (mode == FileMode::Read)
            return 0;

        if (!size)
            return 0;

        if (writeSyncNeeded) {
            SeekInternal(position);
            writeSyncNeeded = false;
        }

        if (fwrite(data, size, 1, (FILE*)handle) != 1) {
            // Return to the position where the write began
            fseek((FILE*)handle, position, SEEK_SET);
            return 0;
        }

        readSyncNeeded = true;
        position += size;
        if (position > this->size)
            this->size = position;

        return size;
    }

    bool File::Open(const String& fileName, FileMode mode) {
        Close();
        readSyncNeeded = false;
        writeSyncNeeded = false;

        if (context) {
            FileSystem* fileSystem = GetSubSystem<FileSystem>();
            if (!fileSystem || !fileSystem->CheckAccess(GetPath(fileName)))
                return false;
        }

        if (fileName.Empty()) return false;

        _wfopen_s((FILE**)&handle, GetWideNativePath(fileName).CString(), openMode[(int)mode]);

        // If file did not exist in readwrite mode, retry with write-update mode
        if (mode == FileMode::Read_Write && !handle) {
            _wfopen_s((FILE**)&handle, GetWideNativePath(fileName).CString(), openMode[(int)mode + 1]);
        }

        // Could not open file
        if (!handle) return false;

        fseek((FILE*)handle, 0, SEEK_END);
        long size = ftell((FILE*)handle);
        fseek((FILE*)handle, 0, SEEK_SET);
        if ((uint32)size > Mathf::UnsignedMax) {
            // Could not open file which is larger than 4GB
            Close();
            this->size = 0;
            return false;
        }

        this->size = (uint32)size;

        position = 0;
        this->fileName = GetFileName(fileName);
        this->fullPath = fileName;
        this->mode = mode;

        return true;
    }

    void File::Close() {
        if (handle) {
            fclose((FILE*)handle);
            handle = nullptr;
            position = 0;
            size = 0;
        }
    }

    void File::Flush() {
        if (handle)
            fflush((FILE*)handle);
    }

    void File::SetName(const String& fileName) {
        this->fileName = fileName;
    }

    void File::ReadText(String& text) {
        text.Clear();

        if (!size) return;

        text.Resize(size);

        Read((void*)text.CString(), size);
    }

    bool File::Copy(File* srcFile) {
        if (!srcFile || !srcFile->IsOpen() || srcFile->GetMode() != FileMode::Read)
            return false;

        if (!IsOpen() || mode != FileMode::Read)
            return false;

        uint32 fileSize = srcFile->GetSize();
        SharedArrayPtr<byte> buffer(new byte[fileSize]);

        uint32 bytesRead = srcFile->Read(buffer.Get(), fileSize);
        uint32 bytesWritten = Write(buffer.Get(), fileSize);
        return bytesRead == fileSize && bytesWritten == fileSize;
    }

    bool File::ReadInternal(void* dest, uint32 size) {
        return fread(dest, size, 1, (FILE*)handle) == 1;
    }

    void File::SeekInternal(uint32 newPosition) {
        fseek((FILE*)handle, newPosition, SEEK_SET);
    }
}






