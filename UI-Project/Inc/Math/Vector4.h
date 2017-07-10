#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace Pyro
{
    struct Vector2;
    struct Vector3;

    struct Vector4 : public DirectX::XMFLOAT4
    {
        /// Ctors
        Vector4();
        Vector4(const float x, const float y, const float z, const float w);
        Vector4(const Vector2& vec);
        Vector4(const Vector3& vec);

        /// Assignment Calls
        Vector4& operator=(const Vector2& rhs);
        Vector4& operator=(const Vector3& rhs);
        Vector4& operator=(const Vector4& rhs);
        /// Conversions from DirectX Math Lib
        Vector4& operator=(const DirectX::XMFLOAT2& rhs);
        Vector4& operator=(const DirectX::XMFLOAT3& rhs);
        Vector4& operator=(const DirectX::XMFLOAT4& rhs);

        /// Comparison Check
        bool operator==(const Vector4& rhs) const;

        /// Standard Operations
        Vector4 operator+(const Vector4& rhs) const;
        Vector4& operator+=(const Vector4& rhs);

        Vector4 operator-(const Vector4& rhs) const;
        Vector4& operator-=(const Vector4& rhs);

        Vector4 operator*(const float rhs) const;
        Vector4& operator*=(const float rhs);

        Vector4 operator/(const float rhs) const;
        Vector4& operator/=(const float rhs);

        /// Returns a copy of the vector negated
        Vector4 operator-() const;

        /// Negates the vector
        void Negate();

        /// Dot Product
        float operator*(const Vector4& rhs) const;

        /// Cross Product
        Vector4 operator^(const Vector4& rhs) const;
        Vector4& operator^=(const Vector4& rhs);

        /// Returns the length of the vector
        float Length() const;

        /// Returns the magnitude of the vector
        float Magnitude() const;

        /// Returns the squared length of the vector
        float LengthSq() const;

        /// Returns the squared magnitude of the vector
        float MagnitudeSq() const;

        /// Returns the absoulute vector
        Vector4 Abs() const;

        /// Returns a copy of the vector normalized
        Vector4 Norm() const;

        /// Normalizes the vector and returns it
        Vector4& Normalize();

        /// Determines if the matrix has all good values or not
        bool IsValid() const;

        const float* Data() const { return &x; }

        /// Returns a vector initialized to all zeros
        static Vector4 Zero();

        /// Returns a vector initialized to all ones
        static Vector4 One();
    };
}

