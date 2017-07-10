#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace Pyro
{
    struct Vector3;
    struct Vector4;
    struct Quaternion;
    struct Matrix3;

    struct Matrix4 : public DirectX::XMFLOAT4X4 {
        Matrix4();
        Matrix4(const float _m11, const float _m12, const float _m13, const float _m14,
            const float _m21, const float _m22, const float _m23, const float _m24,
            const float _m31, const float _m32, const float _m33, const float _m34,
            const float _m41, const float _m42, const float _m43, const float _m44);
        Matrix4(const Matrix3& mat);
        Matrix4(const DirectX::XMMATRIX& mat);

        /// Comparison Operator
        bool operator==(const Matrix4& rhs) const;

        /// Assignment Calls
        Matrix4& operator=(const Matrix3& rhs);
        Matrix4& operator=(const Matrix4& rhs);
        Matrix4& operator=(const DirectX::XMFLOAT3X3& rhs);
        Matrix4& operator=(const DirectX::XMFLOAT4X4& rhs);
        Matrix4& operator=(const DirectX::XMMATRIX& rhs);

        /// Standard Matrix to Matrix operations
        Matrix4 operator+(const Matrix4& rhs) const;
        Matrix4& operator+=(const Matrix4& rhs);

        Matrix4 operator-(const Matrix4& rhs) const;
        Matrix4& operator-=(const Matrix4& rhs);

        DirectX::XMMATRIX operator*(const Matrix4& rhs) const;
        DirectX::XMMATRIX operator*(const DirectX::XMMATRIX& rhs) const;
        Matrix4& operator*=(const Matrix4& rhs);
        Matrix4& operator*=(const DirectX::XMMATRIX& rhs);

        /// Vector to Matrix operations
        Vector4 operator*(const Vector4& rhs) const;

        /// Scalar Operations
        Matrix4 operator*(const float rhs) const;
        Matrix4& operator*=(const float rhs);

        Matrix4 operator/(const float rhs) const;
        Matrix4& operator/=(const float rhs);

        /// Returns the foward vector from the matrix
        Vector3 Forward() const;

        /// Returns the right vector from the matrix
        Vector3 Right() const;

        /// Returns the up vector from the matrix
        Vector3 Up() const;

        /// Returns the translation vector from the matrix
        Vector3 Translation() const;

        /// Returns a copy of the matrix transposed
        Matrix4 Transpose() const;

        /// Returns the determinant of the matrix
        float Determinant() const;

        /// Return a copy of the matrix inverse
        Matrix4 Inverse() const;

        /// Rotates the matrix around the set in point around the axis by the angle
        void RotateAround(const Vector3& point, const Vector3& axis, const float angle);

        /// Creates a rotation to look at the point
        void LookAt(const Vector3& position, const Vector3& lookTo);

        /// Decomposes the Matrix and stores the results in the passed in variables
        bool Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const;

        /// Decomposes the Matrix and stores the results in the passed in Vector
        bool DecomposeTranslation(Vector3& translation) const;

        /// Decomposes the Matrix and stores the results in the passed in quaternion
        bool DecomposeRotation(Quaternion& rotation) const;

        /// Decomposes the Matrix and stores the results in the passed in vector
        bool DecomposeScale(Vector3& scale) const;

        /// Returns the rotation values of the current matrix
        Vector3 GetRotation() const;

        /// Returns the scaling values for the matrix
        Vector3 GetScale() const;

        /// Returns a copy of the matrix negated
        Matrix4 operator-() const;

        /// Negated the matrix
        void Negate();

        /// Determines if the matrix has all good values or not
        bool IsValid() const;

        const float* Data() const { return &_11; }

        /// Returns a matrix that is empty
        static Matrix4 Empty();

        /// Returns a matrix that is identity
        static Matrix4 Identity();

        /// Creates a translation matrix based on passed in values
        static Matrix4 Translate(const float x, const float y, const float z);

        /// Creates a translation matrix based on passed in values
        static Matrix4 Translate(const Vector3& vec);

        /// Creates a translation matrix based on passed in values
        static Matrix4 Translate(const Vector4& vec);

        /// Creates a rotation matrix based on the passed in rotation
        static Matrix4 RotationX(const float xRotation);

        /// Creates a rotation matrix based on the passed in rotation
        static Matrix4 RotationY(const float yRotation);

        /// Creates a rotation matrix based on the passed in rotation
        static Matrix4 RotationZ(const float zRotation);

        /// Creates a scalar matrix based on passed in values
        static Matrix4 Scale(const float x, const float y, const float z);

        /// Creates a scalar matrix based on passed in values
        static Matrix4 Scale(const Vector3& vec);

        /// Creates a scalar matrix based on passed in values
        static Matrix4 Scale(const Vector4& vec);

        /// Performs a matrix affine on the sent in information
        static Matrix4 Affine(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);
    };

    /// Multiplies the two matrices together
    DirectX::XMMATRIX operator*(const DirectX::XMMATRIX& lhs, const Matrix4& rhs);

    /// Multiplies the whole vector array by the passed in matrix and returns the results
    void Vec3TransformCoordArray(Vector3* pOut, size_t outStride, Vector3* pIn, size_t inStride, size_t count, Matrix4* matrix);
}
