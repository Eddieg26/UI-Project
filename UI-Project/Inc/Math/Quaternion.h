#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace Pyro
{
    struct Vector3;
    struct Vector4;
    struct Matrix3;
    struct Matrix4;

    struct Quaternion : public DirectX::XMFLOAT4 {
        /// Ctors
        Quaternion();
        Quaternion(const float w, const float x, const float y, const float z = 0);
        Quaternion(const Vector3& vec);
        Quaternion(const float angle, const Vector3& vec);

        /// Assignment calls
        Quaternion& operator=(const Quaternion& quaternion);

        /// Standard Quaternion Operations
        Quaternion operator+(const Quaternion& rhs) const;
        Quaternion& operator+=(const Quaternion& rhs);

        Quaternion operator-(const Quaternion& rhs) const;
        Quaternion& operator-=(const Quaternion& rhs);

        Quaternion operator*(const Quaternion& rhs) const;
        Quaternion& operator*=(const Quaternion& rhs);

        Quaternion operator*(const float rhs) const;
        Quaternion& operator*=(const float rhs);

        Quaternion operator/(const float rhs) const;
        Quaternion& operator/=(const float rhs);

        /// Rotation by vector
        Quaternion operator*(const Vector3& rhs) const;
        Quaternion& operator*=(const Vector3& rhs);

        /// Dots this quaternion with the passed in quaternion and returns the result
        float Dot(const Quaternion& quaternion) const;

        /// Dots the two quaternions and returns the result
        static float Dot(const Quaternion& lhs, const Quaternion& rhs);

        /// Returns a rotation matrix from the quaternion
        Matrix3 ToMatrix3() const;

        /// Returns a rotation matrix from the quaternion
        Matrix4 ToMatrix4() const;

        /// Returns a cojugate of the quaternion
        Quaternion Conjugate() const;

        /// Returns the inverse to the quaternion
        Quaternion Inverse() const;

        /// Returns a unit inverse quaternion
        Quaternion InverseUnitQuaternion() const;

        /// Returns the length of the quaternion
        float Length() const;

        /// Returns the squared length of the quaternion
        float LengthSq() const;

        /// Returns the magnitude of the quaternion
        float Magnitude() const;

        /// Returns the squared magnitude of the quaternion
        float MagnitudeSq() const;

        /// Returns a copy of the quaternion normalized
        Quaternion Norm() const;

        /// Normalized the quaternion
        void Normalize();

        /// Determines if the matrix has all good values or not
        bool IsValid() const;

        const float* Data() const { return &x; }

        /// Returns the quaternion as Euler Angles
        Vector3 GetEulerAngles() const;

        /// Creates a rotation quaternion based on the incoming Euler Angles
        static Quaternion FromEulerAngles(const float x, const float y, const float z);

        /// Creates a rotation quaternion based on the incoming Euler Angles
        static Quaternion FromEulerAngles(const Vector3& Angles);

        /// Creates a rotation quaternion based on the incoming Euler Angles
        static Quaternion FromEulerAngles(const Vector4& Angles);

        /// Creates a quaternion based on the angle and axis
        static Quaternion RotateAxis(float angle, const Vector3& axis);

        /// Returns a unit quaternion
        static Quaternion Identity();
    };
}
