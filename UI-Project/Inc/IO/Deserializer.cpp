#include "Deserializer.h"
#include "../Math/MathDefs.h"

namespace Pyro
{
    Deserializer::Deserializer() {
        position = 0;
        size = 0;
    }

    long long Deserializer::ReadInt64() {
        long long ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    int Deserializer::ReadInt() {
        int ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    short Deserializer::ReadShort() {
        short ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    signed char Deserializer::ReadByte() {
        signed char ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    unsigned long long Deserializer::ReadUInt64() {
        unsigned long long ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    unsigned int Deserializer::ReadUInt() {
        unsigned ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    unsigned short Deserializer::ReadUShort() {
        unsigned short ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    unsigned char Deserializer::ReadUByte() {
        unsigned char ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    bool Deserializer::ReadBool() {
        return ReadUByte() != 0;
    }

    float Deserializer::ReadFloat() {
        float ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    double Deserializer::ReadDouble() {
        double ret;
        Read(&ret, sizeof(ret));
        return ret;
    }

    Rect Deserializer::ReadRect() {
        float data[4];
        Read(data, sizeof(float) * 4);
        return Rect(data[0], data[1], data[2], data[3]);
    }

    Vector2 Deserializer::ReadVector2() {
        float data[2];
        Read(data, sizeof(float) * 2);
        return Vector2(data[0], data[1]);
    }

    Vector3 Deserializer::ReadVector3() {
        float data[3];
        Read(data, sizeof(float) * 3);
        return Vector3(data[0], data[1], data[2]);
    }

    Vector4 Deserializer::ReadVector4() {
        float data[4];
        Read(data, sizeof(float) * 4);
        return Vector4(data[0], data[1], data[2], data[3]);
    }

    Quaternion Deserializer::ReadQuaternion() {
        float data[4];
        Read(data, sizeof(float) * 4);
        return Quaternion(data[0], data[1], data[2], data[3]);
    }

    Matrix3 Deserializer::ReadMatrix3() {
        float data[9];
        Read(data, sizeof(float) * 9);
        return Matrix3(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
    }

    Matrix4 Deserializer::ReadMatrix4() {
        float data[16];
        Read(data, sizeof(float) * 16);
        return Matrix4(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8],
            data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
    }

    Color Deserializer::ReadColor() {
        float data[4];
        Read(data, sizeof(float) * 4);
        return Color(data[0], data[1], data[2], data[3]);
    }

    BoundingBox Deserializer::ReadBoundingBox() {
        float data[6];
        Read(data, sizeof(float) * 6);
        Vector3 min(data[0], data[1], data[2]);
        Vector3 max(data[3], data[4], data[5]);
        return BoundingBox(min, max);
    }

    Sphere Deserializer::ReadSphere() {
        float data[4];
        Read(data, sizeof(float) * 4);
        return Sphere(Vector3(data[0], data[1], data[2]), data[3]);
    }

    String Deserializer::ReadString() {
        String ret;

        while (!IsEOF()) {
            char c = ReadByte();
            if (!c)
                break;
            else
                ret += c;
        }

        return ret;
    }

    String Deserializer::ReadFileID() {
        String ret;
        ret.Resize(4);
        Read(&ret[0], 4);
        return ret;
    }

    StringHash Deserializer::ReadStringHash() {
        return StringHash(ReadUInt());
    }

    StringVector Deserializer::ReadStringVector() {
        StringVector ret(ReadVLE());
        for (unsigned i = 0; i < ret.Size(); ++i)
            ret[i] = ReadString();
        return ret;
    }

    unsigned int Deserializer::ReadVLE() {
        unsigned ret;
        unsigned char byte;

        byte = ReadUByte();
        ret = (unsigned)(byte & 0x7f);
        if (byte < 0x80)
            return ret;

        byte = ReadUByte();
        ret |= ((unsigned)(byte & 0x7f)) << 7;
        if (byte < 0x80)
            return ret;

        byte = ReadUByte();
        ret |= ((unsigned)(byte & 0x7f)) << 14;
        if (byte < 0x80)
            return ret;

        byte = ReadUByte();
        ret |= ((unsigned)byte) << 21;
        return ret;
    }

    String Deserializer::ReadLine() {
        String ret;

        while (!IsEOF()) {
            char c = ReadByte();
            if (c == 10)
                break;
            if (c == 13) {
                // Peek next char to see if it's 10, and skip it too
                if (!IsEOF()) {
                    char next = ReadByte();
                    if (next != 10)
                        Seek(position - 1);
                }
                break;
            }

            ret += c;
        }

        return ret;
    }
}
