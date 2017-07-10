#include "Vector3.h"

#include "Vector2.h"
#include "Vector4.h"
#include "Mathf.h"

namespace Pyro
{
    Vector3::Vector3() {
        x = y = z = 0.0f;
    }

    Vector3::Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3(const Vector2& vec) {
        x = vec.x;
        y = vec.y;
        z = 0.0f;
    }

    Vector3::Vector3(const Vector4& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    Vector3::Vector3(const float* data) {
        x = data[0];
        y = data[1];
        z = data[2];
    }

    Vector3& Vector3::operator=(const Vector2& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = 0.0f;

        return *this;
    }

    Vector3& Vector3::operator=(const Vector3& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;

        return *this;
    }

    Vector3& Vector3::operator=(const Vector4& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;

        return *this;
    }

    Vector3& Vector3::operator=(const XMFLOAT2& rhs) { return operator=(*(Vector2*)&rhs); }
    Vector3& Vector3::operator=(const XMFLOAT3& rhs) { return operator=(*(Vector3*)&rhs); }
    Vector3& Vector3::operator=(const XMFLOAT4& rhs) { return operator=(*(Vector4*)&rhs); }

    bool Vector3::operator==(const Vector3& rhs) const {
        if (!Mathf::CompareFloat(x, rhs.x))
            return false;

        if (!Mathf::CompareFloat(y, rhs.y))
            return false;

        if (!Mathf::CompareFloat(z, rhs.z))
            return false;

        return true;
    }

    bool Vector3::operator!=(const Vector3& rhs) const {
        return !(*this == rhs);
    }

    Vector3 Vector3::operator+(const Vector3& rhs) const { return{ x + rhs.x, y + rhs.y, z + rhs.z }; }
    Vector3& Vector3::operator+=(const Vector3& rhs) { return *this = *this + rhs; }

    Vector3 Vector3::operator-(const Vector3& rhs) const { return{ x - rhs.x, y - rhs.y, z - rhs.z }; }
    Vector3& Vector3::operator-=(const Vector3& rhs) { return *this = *this - rhs; }

    Vector3 Vector3::operator*(float rhs) const { return{ x * rhs, y * rhs, z * rhs }; }
    Vector3& Vector3::operator*=(float rhs) { return *this = *this * rhs; }

    Vector3 Vector3::operator/(const float rhs) const { return{ x / rhs, y / rhs, z / rhs }; }
    Vector3& Vector3::operator/=(const float rhs) { return *this = *this / rhs; }

    Vector3 Vector3::operator-() const { return{ -x, -y, -z }; }

    void Vector3::Negate() { *this = -(*this); }

    float Vector3::operator*(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

    Vector3 Vector3::operator^(const Vector3& rhs) const {
        float newX = y * rhs.z - z * rhs.y;
        float newY = z * rhs.x - x * rhs.z;
        float newZ = x * rhs.y - y * rhs.x;

        return{ newX, newY, newZ };
    }

    Vector3& Vector3::operator^=(const Vector3& rhs) { return *this = *this ^ rhs; }

    float& Vector3::operator[](unsigned int index) {
        float* data = Data();
        return data[index];
    }

    const float& Vector3::operator[](unsigned int index) const {
        const float* data = Data();
        return data[index];
    }

    float Vector3::Length() const { return sqrtf(*this * *this); }

    float Vector3::Magnitude() const { return Length(); }

    float Vector3::LengthSq() const { return *this * *this; }

    float Vector3::MagnitudeSq() const { return LengthSq(); }

    Vector3 Vector3::Abs() const { return Vector3(fabsf(x), fabsf(y), fabsf(z)); }

    Vector3 Vector3::Norm() const {
        if (x == 0 && y == 0 && z == 0)
            return Vector3(0, 0, 0);

        float w = 1 / Length();

        return *this * w;
    }

    Vector3& Vector3::Normalize() { return *this = (*this).Norm(); }

    bool Vector3::IsValid() const {
        return Mathf::IsValid(x) && Mathf::IsValid(y) && Mathf::IsValid(z);
    }

    Vector3 Vector3::Zero() { return{ 0.0f, 0.0f, 0.0f }; }
    Vector3 Vector3::Up() { return{ 0.0f, 1.0f, 0.0f }; }
    Vector3 Vector3::Forward() { return{ 0.0f, 0.0f, 1.0f }; }
    Vector3 Vector3::Right() { return{ 1.0f, 0.0f, 0.0f }; }
    Vector3 Vector3::One() { return{ 1.0f,1.0f,1.0f }; }

    float Vector3::Dot(const Vector3& a, const Vector3& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    float Vector3::Distance(const Vector3& a, const Vector3& b) {
        return (a - b).Magnitude();
    }

    float Vector3::Angle(const Vector3& from, const Vector3& to) {
        float dot = Vector3::Dot(from, to);
        float length = from.Length() * to.Length();
        float angle = Mathf::Acos(dot / length) * Mathf::RadToDeg;

        return angle;
    }

    Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
        Vector3 ret;
        ret.x = Mathf::Lerp(a.x, b.x, t);
        ret.y = Mathf::Lerp(a.y, b.y, t);
        ret.z = Mathf::Lerp(a.z, b.z, t);
        return ret;
    }
    Vector3 Vector3::Reflect(const Vector3& inDirection, const Vector3& inNormal) {
        Vector3 ret;
        ret = inDirection - (2.0f * Vector3::Dot(inDirection, inNormal) * inNormal);
        return ret;
    }

    Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) {
        Vector3 ret;
        ret.x = a.y * b.z - a.z * b.y;
        ret.y = a.z * b.x - a.x * b.z;
        ret.z = a.x * b.y - a.y * b.x;
        return ret;
    }

    Vector3 Vector3::Scale(const Vector3& a, const Vector3& b) {
        Vector3 ret;
        ret.x = a.x * b.x;
        ret.y = a.y * b.y;
        ret.z = a.z * b.z;
        return ret;
    }
}









