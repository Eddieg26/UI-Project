#include "Serializer.h"
#include "../Math/MathDefs.h"
#include "../Math/Mathf.h"

namespace Pyro
{
    bool Serializer::WriteInt64(long long value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteInt(int value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteShort(short value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteByte(signed char value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteUInt64(unsigned long long value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteUInt(unsigned int value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteUShort(unsigned short value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteUByte(unsigned char value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteBool(bool value) {
        return WriteUByte((unsigned char)(value ? 1 : 0)) == 1;
    }

    bool Serializer::WriteFloat(float value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteDouble(double value) {
        return Write(&value, sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteRect(const Rect& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteVector2(const Vector2& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteVector3(const Vector3& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteVector4(const Vector4& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteQuaternion(const Quaternion& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteMatrix3(const Matrix3& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteMatrix4(const Matrix4& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteColor(const Color& value) {
        return Write(value.Data(), sizeof(value)) == sizeof(value);
    }

    bool Serializer::WriteBoundingBox(const BoundingBox& value) {
        bool success = true;
        success &= WriteVector3(value.Min());
        success &= WriteVector3(value.Max());
        return success;
    }

    bool Serializer::WriteSphere(const Sphere& value) {
        bool success = true;
        success &= WriteVector3(value.Center());
        success &= WriteFloat(value.Radius());
        return success;
    }

    bool Serializer::WriteString(const String& value) {
        const char* chars = value.CString();
        // Count length to the first zero, because ReadString() does the same
        unsigned length = String::CStringLength(chars);
        return Write(chars, length + 1) == length + 1;
    }

    bool Serializer::WriteFileID(const String& value) {
        bool success = true;
        unsigned length = Mathf::Min(value.Length(), 4U);

        success &= Write(value.CString(), length) == length;
        for (unsigned i = value.Length(); i < 4; ++i)
            success &= WriteByte(' ');
        return success;
    }

    bool Serializer::WriteStringHash(const StringHash& value) {
        return WriteUInt(value.Value());
    }

    bool Serializer::WriteStringVector(const StringVector& value) {
        bool success = true;
        success &= WriteVLE(value.Size());
        for (unsigned int i = 0; i < value.Size(); ++i) {
            if (!WriteString(value[i]))
                return false;
        }
        return success;
    }

    bool Serializer::WriteVLE(unsigned int value) {
        unsigned char data[4];

        if (value < 0x80)
            return WriteUByte((unsigned char)value);
        else if (value < 0x4000) {
            data[0] = (unsigned char)(value | 0x80);
            data[1] = (unsigned char)(value >> 7);
            return Write(data, 2) == 2;
        }
        else if (value < 0x200000) {
            data[0] = (unsigned char)(value | 0x80);
            data[1] = (unsigned char)((value >> 7) | 0x80);
            data[2] = (unsigned char)(value >> 14);
            return Write(data, 3) == 3;
        }
        else {
            data[0] = (unsigned char)(value | 0x80);
            data[1] = (unsigned char)((value >> 7) | 0x80);
            data[2] = (unsigned char)((value >> 14) | 0x80);
            data[3] = (unsigned char)(value >> 21);
            return Write(data, 4) == 4;
        }
    }

    bool Serializer::WriteLine(const String& value) {
        bool success = true;
        success &= Write(value.CString(), value.Length()) == value.Length();
        success &= WriteUByte(13);
        success &= WriteUByte(10);
        return success;
    }
}


