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

    /// Abstract class for streaming
    class Serializer {

    public:
        /// Destruct
        virtual ~Serializer() = default;

        /// Write bytes to the stream. Return number of bytes actually written.
        virtual unsigned Write(const void* data, unsigned size) = 0;

        /// Write a 64-bit integer.
        bool WriteInt64(long long value);
        /// Write a 32-bit integer.
        bool WriteInt(int value);
        /// Write a 16-bit integer.
        bool WriteShort(short value);
        /// Write an 8-bit integer.
        bool WriteByte(signed char value);
        /// Write a 64-bit unsigned integer.
        bool WriteUInt64(unsigned long long value);
        /// Write a 32-bit unsigned integer.
        bool WriteUInt(unsigned int value);
        /// Write a 16-bit unsigned integer.
        bool WriteUShort(unsigned short value);
        /// Write an 8-bit unsigned integer.
        bool WriteUByte(unsigned char value);
        /// Write a bool.
        bool WriteBool(bool value);
        /// Write a float.
        bool WriteFloat(float value);
        /// Write a double.
        bool WriteDouble(double value);
        /// Write a Rect.
        bool WriteRect(const Rect& value);
        /// Write a Vector2.
        bool WriteVector2(const Vector2& value);
        /// Write a Vector3.
        bool WriteVector3(const Vector3& value);
        /// Write a Vector4.
        bool WriteVector4(const Vector4& value);
        /// Write a quaternion.
        bool WriteQuaternion(const Quaternion& value);
        /// Write a Matrix3.
        bool WriteMatrix3(const Matrix3& value);
        /// Write a Matrix4.
        bool WriteMatrix4(const Matrix4& value);
        /// Write a color.
        bool WriteColor(const Color& value);
        /// Write a bounding box.
        bool WriteBoundingBox(const BoundingBox& value);
        /// Write a sphere
        bool WriteSphere(const Sphere& value);
        /// Write a null-terminated string.
        bool WriteString(const String& value);
        /// Write a four-letter file ID. If the string is not long enough, spaces will be appended.
        bool WriteFileID(const String& value);
        /// Write a 32-bit StringHash.
        bool WriteStringHash(const StringHash& value);
        /// Write a variant vector.
        bool WriteStringVector(const StringVector& value);
        /// Write a variable-length encoded unsigned integer, which can use 29 bits maximum.
        bool WriteVLE(unsigned int value);
        /// Write a text line. Char codes 13 & 10 will be automatically appended.
        bool WriteLine(const String& value);
    };
}