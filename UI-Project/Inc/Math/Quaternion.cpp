#include "Quaternion.h"

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Mathf.h"

namespace Pyro
{
    Quaternion::Quaternion() { x = y = z = w = 0; }

    Quaternion::Quaternion(const float w, const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Quaternion::Quaternion(const Vector3& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = 0.0f;
    }

    Quaternion::Quaternion(const float angle, const Vector3& vec) {
        XMStoreFloat4(this, XMQuaternionRotationNormal(XMLoadFloat3(&vec), angle));
    }

    Quaternion& Quaternion::operator = (const Quaternion& quaternion) {
        w = quaternion.w;
        x = quaternion.x;
        y = quaternion.y;
        z = quaternion.z;

        return *this;
    }

    Quaternion Quaternion::operator + (const Quaternion& rhs) const { return{ w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z }; }
    Quaternion& Quaternion::operator += (const Quaternion& rhs) { return *this = *this + rhs; }

    Quaternion Quaternion::operator-(const Quaternion& rhs) const { return{ w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z }; }
    Quaternion& Quaternion::operator-=(const Quaternion& rhs) { return *this = *this - rhs; }

    Quaternion Quaternion::operator*(const Quaternion& rhs) const {
        Quaternion newQuat;
        XMStoreFloat4(&newQuat, XMQuaternionMultiply(XMLoadFloat4(this), XMLoadFloat4(&rhs)));

        return newQuat;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& rhs) { return *this = *this * rhs; }

    Quaternion Quaternion::operator*(const float rhs) const { return{ w * rhs, x * rhs, y * rhs, z * rhs }; }
    Quaternion& Quaternion::operator*=(const float rhs) { return *this = *this * rhs; }

    Quaternion Quaternion::operator/(const float rhs) const {
        float temp = 1 / rhs;
        return *this * temp;
    }

    Quaternion& Quaternion::operator/=(const float rhs) { return *this = *this / rhs; }

    Quaternion Quaternion::operator*(const Vector3& rhs) const {
        Quaternion temp(0, rhs.x, rhs.y, rhs.z);
        return *this * temp;
    }

    Quaternion& Quaternion::operator*=(const Vector3& rhs) { return *this = *this * rhs; }

    float Quaternion::Dot(const Quaternion& quaternion) const {
        return w * quaternion.w + x * quaternion.x + y * quaternion.y + z * quaternion.z;
    }

    float Quaternion::Dot(const Quaternion& lhs, const Quaternion& rhs) { return lhs.Dot(rhs); }

    Matrix3 Quaternion::ToMatrix3() const {
        return{
            1 - 2 * (y * y) - 2 * (z * z), 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y,
            2 * x * y + 2 * w * z, 1 - 2 * (x * x) - 2 * (z * z), 2 * y * z - 2 * w * x,
            2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * (x * x) - 2 * (y * y)
        };
    }

    Matrix4 Quaternion::ToMatrix4() const {
        return{
            1 - 2 * (y * y) - 2 * (z * z), 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y, 0,
            2 * x * y + 2 * w * z, 1 - 2 * (x * x) - 2 * (z * z), 2 * y * z - 2 * w * x, 0,
            2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * (x * x) - 2 * (y * y), 0,
            0, 0, 0, 1
        };
    }

    Quaternion Quaternion::Conjugate() const { return{ x, -y, -z, -w }; }

    Quaternion Quaternion::Inverse() const { return Conjugate() / (*this).Dot(*this); }

    Quaternion Quaternion::InverseUnitQuaternion() const { return Conjugate(); }

    float Quaternion::Length() const { return sqrtf(this->Dot(*this)); }

    float Quaternion::LengthSq() const { return this->Dot(*this); }

    float Quaternion::Magnitude() const { return Length(); }

    float Quaternion::MagnitudeSq() const { return LengthSq(); }

    Quaternion Quaternion::Norm() const { return *this / Length(); }

    void Quaternion::Normalize() { *this = Norm(); }

    bool Quaternion::IsValid() const {
        return Mathf::IsValid(x) && Mathf::IsValid(y) && Mathf::IsValid(z) && Mathf::IsValid(w);
    }

    Vector3 Quaternion::GetEulerAngles() const {
        Vector3 Angles;
        Angles.x = Mathf::RadToDeg * (atan2f(2.0f * (w * x + y * z), 1 - 2.0f * (x * x + y * y)));
        Angles.y = Mathf::RadToDeg * (asinf(2.0f * (w * y - z * x)));
        Angles.z = Mathf::RadToDeg * (atan2f(2.0f * (w * z + x * y), 1 - 2.0f * (y * y + z * z)));

        return Angles;
    }

    Quaternion Quaternion::FromEulerAngles(const float x, const float y, const float z) {
        Quaternion newQuat;
        XMStoreFloat4(&newQuat, XMQuaternionRotationRollPitchYaw(x, y, z));

        return newQuat;
    }

    Quaternion Quaternion::FromEulerAngles(const Vector3& Angles) { return FromEulerAngles(Angles.x, Angles.y, Angles.z); }

    Quaternion Quaternion::FromEulerAngles(const Vector4& Angles) { return FromEulerAngles(Angles.x, Angles.y, Angles.z); }

    Quaternion Quaternion::RotateAxis(float angle, const Vector3& axis) {
        Quaternion newQuat;
        XMStoreFloat4(&newQuat, XMQuaternionRotationAxis(XMLoadFloat3(&axis), angle));

        return newQuat;
    }

    Quaternion Quaternion::Identity() { return Quaternion(1.0f, 0.0f, 0.0f, 0.0f); }
}
