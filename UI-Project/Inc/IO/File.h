#pragma once

#include "../Core/Object.h"
#include "Serializer.h"
#include "Deserializer.h"

namespace Pyro
{
    enum class FileMode {
        Read = 0,
        Write,
        Read_Write,
        Append
    };

    class File : public Object, public Deserializer, public Serializer {

        PYRO_OBJECT(File, Object);

    private:
        /// File handle
        void* handle;
        /// Synchronization needed before read -flag.
        bool readSyncNeeded;
        /// Synchronization needed before write -flag.
        bool writeSyncNeeded;
        /// File name
        String fileName;
        /// Full path to the file
        String fullPath;
        /// Open mode
        FileMode mode;

    public:
        /// Construct
        File(Context* _context);
        /// Construct and Open
        File(Context* _context, const String& fileName, FileMode mode = FileMode::Read);
        /// Destruct. Close the file if open
        virtual ~File();

        /// Read bytes from the file. Return number of bytes actually read
        virtual unsigned int Read(void* dest, unsigned int size) override;
        /// Set position from the beginning of the file
        virtual unsigned int Seek(unsigned int pos) override;
        /// Write bytes to the file. Return number of bytes actually written
        virtual unsigned int Write(const void* data, unsigned int size) override;

        /// Open a filesystem file. Return true if successful.
        bool Open(const String& fileName, FileMode mode = FileMode::Read);
        /// Close the file
        void Close();
        /// Flush any buffered output to the file.
        void Flush();
        /// Change the file name. Used by the resource system.
        void SetName(const String& fileName);

        /// Return name
        virtual const String& GetName() { return fileName; }

        /// Return mode
        FileMode GetMode() const { return mode; }

        /// Return whether is open
        bool IsOpen() const { return handle != nullptr; }

        /// Return file handle
        void* GetHandle() const { return handle; }

        /// Reads a text file, ensuring data from file is 0 terminated
        virtual void ReadText(String& text);

        /// Reads a text file, ensuring data from file is 0 terminated
        virtual String ReadText() { String retValue; ReadText(retValue); return retValue; }

        /// Return the fullpath to the file
        const String& GetFullPath() const { return fullPath; }

        /// Copy a file from a source file, must be opened and FILE_WRITE
        bool Copy(File* srcFile);

    private:
        /// Perform the file read internally using either C standard IO functions. Return true if successful.
        bool ReadInternal(void* dest, unsigned int size);
        /// Seek in file internally using either C standard IO functions
        void SeekInternal(unsigned int newPosition);
    };
}
