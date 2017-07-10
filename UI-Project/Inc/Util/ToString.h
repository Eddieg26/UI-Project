#pragma once

namespace Pyro
{
    class String;
    struct Color;
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Quaternion;
    struct Sphere;
    struct Rect;

    class ToString {
    public:
        static String FromColor(const Color& color);
        static String FromVector2(const Vector2& vec);
        static String FromVector3(const Vector3& vec);
        static String FromVector4(const Vector4& vec);
        static String FromQuaternion(const Quaternion& quaternion);
        static String FromSphere(const Sphere& sphere);
        static String FromRect(const Rect& rect);

    private:
        ToString() = delete;
        ~ToString() = delete;
        ToString(const ToString&) = delete;
        ToString& operator=(const ToString&) = delete;
    };
}