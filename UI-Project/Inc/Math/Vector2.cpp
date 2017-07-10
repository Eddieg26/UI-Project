#include "Vector2.h"

#include "Vector3.h"
#include "Vector4.h"
#include "Mathf.h"

namespace Pyro
{
    Vector2::Vector2() { x = 0.0f; y = 0.0f; }
    Vector2::Vector2(const float x, const float y) { this->x = x; this->y = y; }
    Vector2::Vector2(const Vector3& vec) { x = vec.x; y = vec.y; }
    Vector2::Vector2(const Vector4& vec) { x = vec.x; y = vec.y; }
    Vector2::Vector2(const float* data) { x = data[0]; y = data[1]; }

    Vector2& Vector2::operator=(const Vector2& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    Vector2& Vector2::operator=(const Vector3& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    Vector2& Vector2::operator=(const Vector4& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    Vector2& Vector2::operator=(const XMFLOAT2& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }
    Vector2& Vector2::operator=(const XMFLOAT3& rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }
    Vector2& Vector2::operator=(const XMFLOAT4& rhs) {
        x = rhs.x;
        y = rhs.y;

        return*this;
    }

    bool Vector2::operator==(const Vector2& rhs) const { return (Mathf::CompareFloat(x, rhs.x) && Mathf::CompareFloat(y, rhs.y)); }
    bool Vector2::operator!=(const Vector2& rhs) const { return !(*this == rhs); }

    Vector2 Vector2::operator+(const Vector2& rhs) const { return{ x + rhs.x, y + rhs.y }; }
    Vector2& Vector2::operator+=(const Vector2& rhs) { return *this = *this + rhs; }

    Vector2 Vector2::operator-(const Vector2& rhs) const { return{ x - rhs.x, y - rhs.y }; }
    Vector2& Vector2::operator-=(const Vector2& rhs) { return *this = *this - rhs; }

    Vector2 Vector2::operator*(const float rhs) const { return{ x * rhs, y * rhs }; }
    Vector2& Vector2::operator*=(const float rhs) { return *this = *this * rhs; }

    Vector2 Vector2::operator/(const float rhs) const { return{ x / rhs, y / rhs }; }
    Vector2& Vector2::operator/=(const float rhs) { return *this = *this / rhs; }

    float& Vector2::operator[](unsigned int index) { return index == 0 ? x : y; }

    const float& Vector2::operator[](unsigned int index) const { return index == 0 ? x : y; }

    Vector2 Vector2::operator-() const { return{ -x, -y }; }

    void Vector2::Negate() { x = -x; y = -y; }

    // Dot Product
    float Vector2::operator*(const Vector2& rhs) const { return x * rhs.x + y * rhs.y; }

    float Vector2::Length() const { return sqrtf(Vector2::Dot(*this, *this)); }

    float Vector2::Magnitude() const { return Length(); }

    float Vector2::LengthSq() const { return *this * *this; }

    float Vector2::MagnitudeSq() const { return LengthSq(); }

    float Vector2::Angle(const Vector2& vector) {
        float dotProduct = Vector2::Dot(*this, vector);
        float length = Length() * vector.Length();
        float angle = acosf(dotProduct / length);

        return angle * Mathf::RadToDeg;
    }

    Vector2 Vector2::Abs() const { return Vector2(fabsf(x), fabsf(y)); }

    Vector2 Vector2::Norm() const {
        float temp = 1 / Length();

        return{ x * temp, y * temp };
    }

    Vector2& Vector2::Normalize() { return *this = Norm(); }

    bool Vector2::IsValid() const {
        return Mathf::IsValid(x) && Mathf::IsValid(y);
    }

    Vector2 Vector2::Zero() { return Vector2(); }
    Vector2 Vector2::Up() { return Vector2(0, 1); }
    Vector2 Vector2::Right() { return Vector2(1, 0); }
    Vector2 Vector2::One() { return Vector2(1, 1); }

    float Vector2::Dot(const Vector2& a, const Vector2& b) {
        return (a.x * b.x) + (a.y * b.y);
    }

    float Vector2::Distance(const Vector2& a, const Vector2& b) {
        return (a - b).Magnitude();
    }

    float Vector2::Angle(const Vector2& from, const Vector2& to) {
        float dot = Vector2::Dot(from, to);
        float length = from.Length() * to.Length();
        float angle = Mathf::Acos(dot / length) * Mathf::RadToDeg;

        return angle;
    }

    Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t) {
        Vector2 ret;
        ret.x = Mathf::Lerp(a.x, b.x, t);
        ret.y = Mathf::Lerp(a.y, b.y, t);
        return ret;
    }

    Vector2 Vector2::Reflect(const Vector2& inDirection, const Vector2& inNormal) {
        Vector2 ret;
        ret = inDirection - (2.0f * Vector2::Dot(inDirection, inNormal) * inNormal);
        return ret;
    }

    Vector2 Vector2::Scale(const Vector2& a, const Vector2& b) {
        Vector2 ret;
        ret.x = a.x * b.x;
        ret.y = a.y * b.y;
        return ret;
    }
}




