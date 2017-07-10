#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace Pyro
{
    struct Vector3;
    struct Matrix4;

    struct Matrix3 : public DirectX::XMFLOAT3X3 {
        /// Ctors
        Matrix3();
        Matrix3(const float _m11, const float _m12, const float _m13,
            const float _m21, const float _m22, const float _m23,
            const float _m31, const float _m32, const float _m33);
        Matrix3(const Matrix4& mat);
        Matrix3(const DirectX::XMMATRIX& mat);

        /// Assignment Calls
        Matrix3& operator=(const Matrix3& rhs);
        Matrix3& operator=(const Matrix4& rhs);
        Matrix3& operator=(const DirectX::XMFLOAT3X3& rhs);
        Matrix3& operator=(const DirectX::XMFLOAT4X4& rhs);
        Matrix3& operator=(const DirectX::XMMATRIX& rhs);

        /// Comparison Operator
        bool operator==(const Matrix3& rhs) const;

        /// Standard Matrix to Matrix operations
        Matrix3 operator+(const Matrix3& rhs) const;
        Matrix3& operator+=(const Matrix3& rhs);

        Matrix3 operator-(const Matrix3& rhs) const;
        Matrix3& operator-=(const Matrix3& rhs);

        DirectX::XMMATRIX operator*(const Matrix3& rhs) const;
        DirectX::XMMATRIX operator*(const DirectX::XMMATRIX& rhs) const;
        Matrix3& operator*=(const Matrix3& rhs);
        Matrix3& operator*=(const DirectX::XMMATRIX& rhs);

        /// Vector to Matrix operations
        Vector3 operator*(const Vector3& rhs) const;

        /// Scalar Operations
        Matrix3 operator*(const float rhs) const;
        Matrix3& operator*=(const float rhs);

        Matrix3 operator/(const float rhs) const;
        Matrix3& operator/=(const float rhs);

        /// Returns a copy of the matrix transposed
        Matrix3 Transpose() const;

        /// Returns the determinant of the matrix
        float Determinant() const;

        /// Return a copy of the matrix inverse
        Matrix3 Inverse() const;

        /// Returns a copy of the matrix negated
        Matrix3 operator-() const;

        /// Negated the matrix
        void Negate();

        /// Determines if the matrix has all good values or not
        bool IsValid() const;

        const float* Data() const { return &_11; }

        /// Returns a matrix that is identity
        static Matrix3 Identity();
    };
}

