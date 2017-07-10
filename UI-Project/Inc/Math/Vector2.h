#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace Pyro
{
    struct Vector3;
    struct Vector4;

    struct Vector2 : public XMFLOAT2 {

        /// Constructors
        Vector2();
        Vector2(const float x, const float y);
        Vector2(const Vector3& vec);
        Vector2(const Vector4& vec);
        /// Construct from a float array
        Vector2(const float* data);

        /// Assignment Calls
        Vector2& operator=(const Vector2& rhs);
        Vector2& operator=(const Vector3& rhs);
        Vector2& operator=(const Vector4& rhs);

        /// Conversions from DirectX Math Lib
        Vector2& operator=(const DirectX::XMFLOAT2& rhs);
        Vector2& operator=(const DirectX::XMFLOAT3& rhs);
        Vector2& operator=(const DirectX::XMFLOAT4& rhs);

        /// Test for equlity with another vector
        bool operator==(const Vector2& rhs) const;
        /// Test for inequality with another vector
        bool operator!=(const Vector2& rhs) const;

        /// Add a vector
        Vector2 operator+(const Vector2& rhs) const;
        /// Add-assign a vector
        Vector2& operator+=(const Vector2& rhs);

        /// Subtract a vector
        Vector2 operator-(const Vector2& rhs) const;
        /// Subtract-assign a vector
        Vector2& operator-=(const Vector2& rhs);

        /// Muliply a scaler
        Vector2 operator*(const float rhs) const;
        /// Multiply-assign a scaler
        Vector2& operator*=(const float rhs);

        /// Divide a scaler
        Vector2 operator/(const float rhs) const;
        /// Divide-assign a scaler
        Vector2& operator/=(const float rhs);

        /// Access x or y component using 0 or 1 repsctively
        float& operator[](unsigned int index);
        /// Access x or y component using 0 or 1 repsctively
        const float& operator[](unsigned int index) const;

        /// Dot Product
        float operator*(const Vector2& rhs) const;

        /// Returns a copy of the vector negated
        Vector2 operator-() const;

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
        /// Return angle between two vectors
        float Angle(const Vector2& vector);
        /// Returns the absoulute vector
        Vector2 Abs() const;
        /// Returns a copy of the vector normalized
        Vector2 Norm() const;
        /// Normalizes the vector and returns it
        Vector2& Normalize();

        /// Determines if the vector has all real values or not
        bool IsValid() const;

        /// Return float data
        float* Data() { return &x; }

        /// Return float data
        const float* Data() const { return &x; }

        /// Returns a vector initialized to all zeros
        static Vector2 Zero();
        /// Returns a vector initialized to global Up (0, 1)
        static Vector2 Up();
        /// Returns a vector initialized to global Right (1, 0)
        static Vector2 Right();
        /// Returns a vector initialized to all ones
        static Vector2 One();

        /// Find the dot product of two vectors
        static float Dot(const Vector2& a, const Vector2& b);
        /// Returns the distance between two vectors
        static float Distance(const Vector2& a, const Vector2& b);
        /// Returns an angle between two vectors
        static float Angle(const Vector2& from, const Vector2& to);
        /// Linearly interpolates between two vectors
        static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
        /// Reflects a vector off the vector defined by a normal.
        static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal);
        /// Multiplies two vectors component - wise.
        static Vector2 Scale(const Vector2& a, const Vector2& b);
    };

    inline Vector2 operator*(float lhs, const Vector2& rhs) { return rhs * lhs; }

    template<typename T>
    struct IVector2 {

    public:
        T x;
        T y;

    public:
        IVector2<T>() : x(0), y(0) {}

        IVector2<T>(T _x, T _y) : x(_x), y(_y) {}

        IVector2<T>& operator=(const IVector2<T>& rhs) {
            x = rhs.x;
            y = rhs.y;
        }

        bool operator==(const IVector2<T>& rhs) { return x == rhs.x && y == rhs.y; }
        bool operator!=(const IVector2<T>& rhs) { return x != rhs.x || y != rhs.y; }

        IVector2<T> operator+(const IVector2<T>& rhs) const {
            IVector2<T> vec;
            vec.x = x + rhs.x;
            vec.y = y + rhs.y;
            return vec;
        }

        IVector2<T>& operator+=(const IVector2<T>& rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        IVector2<T> operator-(const IVector2<T>& rhs) const {
            IVector2<T> vec;
            vec.x = x - rhs.x;
            vec.y = y - rhs.y;
            return vec;
        }

        IVector2<T>& operator-=(const IVector2<T>& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        IVector2<T> operator*(const T rhs) const {
            IVector2<T> vec;
            vec.x = x * rhs;
            vec.y = y * rhs;
            return vec;
        }

        IVector2<T>& operator*=(const T rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        IVector2<T> operator/(const T rhs) const {
            IVector2<T> vec;
            vec.x = x / rhs;
            vec.y = y / rhs;
            return vec;
        }

        IVector2<T>& operator/=(const T rhs) {
            x /= rhs;
            y /= rhs;
            return *this;
        }
    };

    typedef IVector2<int> ivec2;
    typedef IVector2<unsigned> uvec2;
}
