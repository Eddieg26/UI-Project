#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace Pyro
{
    struct Vector2;
    struct Vector4;

    struct Vector3 : public DirectX::XMFLOAT3 {

        /// Construct
        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector2& vec);
        Vector3(const Vector4& vec);
        /// Construct from a float array
        Vector3(const float* data);

        /// Assignment Calls
        Vector3& operator=(const Vector2& rhs);
        Vector3& operator=(const Vector3& rhs);
        Vector3& operator=(const Vector4& rhs);

        /// Conversions from DirectX Math Lib
        Vector3& operator=(const DirectX::XMFLOAT2& rhs);
        Vector3& operator=(const DirectX::XMFLOAT3& rhs);
        Vector3& operator=(const DirectX::XMFLOAT4& rhs);

        /// Test for equality with another vector
        bool operator==(const Vector3& rhs) const;
        /// Test for inequality with another vector
        bool operator!=(const Vector3& rhs) const;

        /// Add a vector
        Vector3 operator+(const Vector3& rhs) const;
        /// Add-assign a vector
        Vector3& operator+=(const Vector3& rhs);

        /// Subtract a vector
        Vector3 operator-(const Vector3& rhs) const;
        /// Subtract-assign a vector
        Vector3& operator-=(const Vector3& rhs);

        /// Multiply by a scaler
        Vector3 operator*(float rhs) const;
        /// Multiply-assign by a scaler
        Vector3& operator*=(float rhs);

        /// Divide by a scaler
        Vector3 operator/(const float rhs) const;
        /// Divide-assign by a scaler
        Vector3& operator/=(const float rhs);

        /// Return negation
        Vector3 operator-() const;

        /// Dot Product
        float operator*(const Vector3& rhs) const;

        /// Cross Product
        Vector3 operator^(const Vector3& rhs) const;
        Vector3& operator^=(const Vector3& rhs);

        /// Access x or y component using 0 or 1 repsctively
        float& operator[](unsigned int index);
        /// Access x or y component using 0 or 1 repsctively
        const float& operator[](unsigned int index) const;

        /// Negates the vector
        void Negate();

        /// Returns the length of the vector
        float Length() const;
        /// Returns the magnitude of the vector
        float Magnitude() const;
        /// Returns the squared length of the vector
        float LengthSq() const;
        /// Returns the squared magnitude of the vector
        float MagnitudeSq() const;
        /// Returns the absoulute vector
        Vector3 Abs() const;
        /// Returns a copy of the vector normalized
        Vector3 Norm() const;
        /// Normalizes the vector and returns it
        Vector3& Normalize();

        /// Determines if the matrix has all good values or not
        bool IsValid() const;

        /// Return as float array
        float* Data() { return &x; }

        /// Return as float array
        const float* Data() const { return &x; }

        /// Returns a vector initialized to all zeros
        static Vector3 Zero();
        /// Returns a vector initialized to global Up (0, 1, 0)
        static Vector3 Up();
        /// Returns a vector initialized to global Forward (0, 0, 1)
        static Vector3 Forward();
        /// Returns a vector initialized to global Right (1, 0, 0)
        static Vector3 Right();
        /// Returns a vector initialized to all ones
        static Vector3 One();

        /// Returns dot prodcut between two vectors
        static float Dot(const Vector3& a, const Vector3& b);
        /// Return distane between two vectors
        static float Distance(const Vector3& from, const Vector3& to);
        /// Return angle between two vectors
        static float Angle(const Vector3& a, const Vector3& b);
        /// Linearly interpolates between two vectors
        static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
        /// Reflects a vector off the vector defined by a normal.
        static Vector3 Reflect(const Vector3& inDirection, const Vector3& inNormal);
        /// Return cross product
        static Vector3 Cross(const Vector3& a, const Vector3& b);
        /// Multiplies two vectors component - wise.
        static Vector3 Scale(const Vector3& a, const Vector3& b);
    };

    inline Vector3 operator*(float lhs, const Vector3& rhs) { return rhs * lhs; }

    template<typename T>
    struct IVector3 {

    public:
        T x;
        T y;
        T z;

    public:
        IVector3<T>() : x(0), y(0), z(0) { }

        IVector3<T>(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

        IVector3<T>(const IVector3<T>& rhs) {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
        }

        IVector3<T>& operator=(const IVector3<T>& rhs) {
            if (this == &rhs) return *this;

            x = rhs.x;
            y = rhs.y;
            z = rhs.z;

            return *this;
        }

        bool operator==(const IVector3<T>& rhs) { return x == rhs.x && y == rhs.y && z == rhs.z; }
        bool operator!=(const IVector3<T>& rhs) { return x != rhs.x || y != rhs.y && z != rhs.z; }

        IVector3<T> operator+(const IVector3<T>& rhs) const {
            IVector3<T> vec;
            vec.x = x + rhs.x;
            vec.y = y + rhs.y;
            vec.z = z + rhs.z;

            return vec;
        }

        IVector3<T>& operator+=(const IVector3<T>& rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;

            return *this;
        }

        IVector3<T> operator-(const IVector3<T>& rhs) const {
            IVector3<T> vec;
            vec.x = x - rhs.x;
            vec.y = y - rhs.y;
            vec.z = z - rhs.z;

            return vec;
        }

        IVector3<T>& operator-=(const IVector3<T>& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;

            return *this;
        }

        IVector3<T> operator*(const IVector3<T>& rhs) const {
            IVector3<T> vec;
            vec.x = x * rhs.x;
            vec.y = y * rhs.y;
            vec.z = z * rhs.z;

            return vec;
        }

        IVector3<T>& operator*=(const IVector3<T>& rhs) {
            x *= rhs.x;
            y * rhs.y;
            z *= rhs.z;

            return *this;
        }

        IVector3<T> operator/(const IVector3<T>& rhs) const {
            IVector3<T> vec;
            vec.x = x / rhs.x;
            vec.y = y / rhs.y;
            vec.z = z / rhs.z;

            return vec;
        }

        IVector3<T>& operator/=(const IVector3<T>& rhs) {
            x *= rhs.x;
            y * rhs.y;
            z *= rhs.z;

            return *this;
        }
    };

    typedef IVector3<int> ivec3;
    typedef IVector3<unsigned> uvec3;
}