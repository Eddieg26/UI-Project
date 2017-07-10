#include "Vector4.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"

namespace Pyro
{
    Vector4::Vector4() {
        x = y = z = w = 0.0f;
    }

    Vector4::Vector4(const float x, const float y, const float z, const float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vector4::Vector4(const Vector2& vec) {
        x = vec.x;
        y = vec.y;
        z = 0.0f;
        w = 1.0f;
    }

    Vector4::Vector4(const Vector3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = 1.0f;
    }

    Vector4& Vector4::operator=(const Vector2& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    Vector4& Vector4::operator=(const Vector3& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;

        return *this;
    }

    Vector4& Vector4::operator=(const Vector4& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;

        return *this;
    }

    Vector4& Vector4::operator=(const XMFLOAT2& rhs) { return operator=(*(Vector2*)&rhs); }
    Vector4& Vector4::operator=(const XMFLOAT3& rhs) { return operator=(*(Vector3*)&rhs); }
    Vector4& Vector4::operator=(const XMFLOAT4& rhs) { return operator=(*(Vector4*)&rhs); }

    bool Vector4::operator==(const Vector4& rhs) const {

        if (!Mathf::CompareFloat(x, rhs.x))
            return false;

        if (!Mathf::CompareFloat(y, rhs.y))
            return false;

        if (!Mathf::CompareFloat(z, rhs.z))
            return false;

        if (!Mathf::CompareFloat(w, rhs.w))
            return false;

        return true;
    }

    Vector4 Vector4::operator+(const Vector4& rhs) const { return{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }
    Vector4& Vector4::operator+=(const Vector4& rhs) { return *this = *this + rhs; }

    Vector4 Vector4::operator-(const Vector4& rhs) const { return{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }
    Vector4& Vector4::operator-=(const Vector4& rhs) { return *this = *this - rhs; }

    Vector4 Vector4::operator*(const float rhs) const { return{ x * rhs, y * rhs, z * rhs, w * rhs }; }
    Vector4& Vector4::operator*=(const float rhs) { return *this = *this * rhs; }

    Vector4 Vector4::operator/(const float rhs) const { return{ x / rhs, y / rhs, z / rhs, w / rhs }; }
    Vector4& Vector4::operator/=(const float rhs) { return *this = *this / rhs; }

    Vector4 Vector4::operator-() const { return{ -x, -y, -z, -w }; }

    void Vector4::Negate() { *this = -(*this); }

    float Vector4::operator*(const Vector4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }

    Vector4 Vector4::operator^(const Vector4& rhs) const {
        Vector3 vec = *(Vector3*)this ^ *(Vector3*)&rhs;

        return{ vec.x, vec.y, vec.z, w };
    }

    Vector4& Vector4::operator^=(const Vector4& rhs) { return *this = *this ^ rhs; }

    float Vector4::Length() const { return sqrtf(*this * *this); }

    float Vector4::Magnitude() const { return Length(); }

    float Vector4::LengthSq() const { return *this * *this; }

    float Vector4::MagnitudeSq() const { return LengthSq(); }

    Vector4 Vector4::Abs() const { return Vector4(fabsf(x), fabsf(y), fabsf(z), fabsf(w)); }

    Vector4 Vector4::Norm() const { return *(Vector4*)&XMVector4Normalize(XMLoadFloat4((XMFLOAT4*)this)); }

    Vector4& Vector4::Normalize() { return *this = Norm(); }

    bool Vector4::IsValid() const {
        return Mathf::IsValid(x) && Mathf::IsValid(y) && Mathf::IsValid(z) && Mathf::IsValid(w);
    }

    Vector4 Vector4::Zero() {
        return Vector4(0, 0, 0, 0);
    }

    Vector4 Vector4::One() {
        return Vector4(1, 1, 1, 1);
    }
}
