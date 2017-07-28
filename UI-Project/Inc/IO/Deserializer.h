#pragma once

#include "../Containers/Str.h"
#include "../Util/StringHash.h"

namespace Pyro
{
    struct Color;
    struct Quaternion;
    struct Rect;
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Matrix3;
    struct Matrix4;
    struct BoundingBox;
    struct Sphere;

    /// Abstract stream for reading.
    class Deserializer {

    protected:
        /// Stream position
        unsigned int position;
        /// Stream size
        unsigned int size;

    public:
        /// Construct
        Deserializer();
        /// Destruct
        virtual ~Deserializer() = default;

        /// Read bytes from the stream. Return number of bytes actually read
        virtual unsigned int Read(void* dest, unsigned int size) = 0;
        /// Set position from the beginning of the stream
        virtual unsigned int Seek(unsigned int pos) = 0;
        /// Return whether the end of stream has been reached
        virtual bool IsEOF() const { return position >= size; }

        virtual const String& GetName() { return String::EMPTY; }

        unsigned int GetPosition() const { return position; }

        unsigned int GetSize() const { return size; }

        /// Read a 64-bit integer.
        long long ReadInt64();
        /// Read a 32-bit integer.
        int ReadInt();
        /// Read a 16-bit integer.
        short ReadShort();
        /// Read an 8-bit integer.
        signed char ReadByte();
        /// Read a 64-bit unsigned integer.
        unsigned long long ReadUInt64();
        /// Read a 32-bit unsigned integer.
        unsigned int ReadUInt();
        /// Read a 16-bit unsigned integer.
        unsigned short ReadUShort();
        /// Read an 8-bit unsigned integer.
        unsigned char ReadUByte();
        /// Read a bool.
        bool ReadBool();
        /// Read a float.
        float ReadFloat();
        /// Read a double.
        double ReadDouble();
        /// Read a Rect.
        Rect ReadRect();
        /// Read a Vector2.
        Vector2 ReadVector2();
        /// Read a Vector3.
        Vector3 ReadVector3();
        /// Read a Vector4.
        Vector4 ReadVector4();
        /// Read a quaternion.
        Quaternion ReadQuaternion();
        /// Read a Matrix3.
        Matrix3 ReadMatrix3();
        /// Read a Matrix4.
        Matrix4 ReadMatrix4();
        /// Read a color.
        Color ReadColor();
        /// Read a bounding box.
        BoundingBox ReadBoundingBox();
        /// Read sphere
        Sphere ReadSphere();
        /// Read a null-terminated string.
        String ReadString();
        /// Read a four-letter file ID.
        String ReadFileID();
        /// Read a 32-bit StringHash.
        StringHash ReadStringHash();
        /// Read a string vector.
        StringVector ReadStringVector();
        /// Read a variable-length encoded unsigned integer, which can use 29 bits maximum.
        unsigned int ReadVLE();
        /// Read a text line.
        String ReadLine();
    };
}