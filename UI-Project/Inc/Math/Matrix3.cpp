#include "Matrix3.h"

#include "Vector3.h"
#include "Matrix4.h"
#include "Mathf.h"

namespace Pyro
{
    Matrix3::Matrix3(){
        _11 = _12 = _13 = _21 = _22 = _23 = _31 = _32 = _33 = 0.0f;
    }

    Matrix3::Matrix3(const float _m11, const float _m12, const float _m13,
        const float _m21, const float _m22, const float _m23,
        const float _m31, const float _m32, const float _m33){
        _11 = _m11; _12 = _m12; _13 = _m13;
        _21 = _m21; _22 = _m22; _23 = _m23;
        _31 = _m31; _32 = _m32; _33 = _m33;
    }

    Matrix3::Matrix3(const Matrix4& mat){
        _11 = mat._11; _12 = mat._12; _13 = mat._13;
        _21 = mat._21; _22 = mat._22; _23 = mat._23;
        _31 = mat._31; _32 = mat._32; _33 = mat._33;
    }

    Matrix3::Matrix3(const XMMATRIX& mat) { XMStoreFloat3x3((XMFLOAT3X3*)this, mat); }

    Matrix3& Matrix3::operator=(const Matrix3& rhs){
        _11 = rhs._11; _12 = rhs._12; _13 = rhs._13;
        _21 = rhs._21; _22 = rhs._22; _23 = rhs._23;
        _31 = rhs._31; _32 = rhs._32; _33 = rhs._33;

        return *this;
    }

    Matrix3& Matrix3::operator=(const Matrix4& rhs){
        _11 = rhs._11; _12 = rhs._12; _13 = rhs._13;
        _21 = rhs._21; _22 = rhs._22; _23 = rhs._23;
        _31 = rhs._31; _32 = rhs._32; _33 = rhs._33;

        return *this;
    }

    Matrix3& Matrix3::operator=(const XMFLOAT3X3& rhs) { return operator=(*(Matrix3*)&rhs); }
    Matrix3& Matrix3::operator=(const XMFLOAT4X4& rhs) { return operator=(*(Matrix4*)&rhs); }

    Matrix3& Matrix3::operator=(const XMMATRIX& rhs){
        XMStoreFloat3x3((XMFLOAT3X3*)this, rhs);

        return *this;
    }

    bool Matrix3::operator==(const Matrix3& rhs) const {
        for (size_t i = 0; i < 9; i++){
            if (m[i] - rhs.m[i] >= Mathf::Epsilon)
                return false;
        }

        return true;
    }

    Matrix3 Matrix3::operator+(const Matrix3& rhs) const{
        return{
            _11 + rhs._11, _12 + rhs._12, _13 + rhs._13,
            _21 + rhs._21, _22 + rhs._22, _23 + rhs._23,
            _31 + rhs._31, _32 + rhs._32, _33 + rhs._33
        };
    }

    Matrix3& Matrix3::operator+=(const Matrix3& rhs) { return *this = *this + rhs; }

    Matrix3 Matrix3::operator-(const Matrix3& rhs) const{
        return{
            _11 - rhs._11, _12 - rhs._12, _13 - rhs._13,
            _21 - rhs._21, _22 - rhs._22, _23 - rhs._23,
            _31 - rhs._31, _32 - rhs._32, _33 - rhs._33
        };
    }

    Matrix3& Matrix3::operator-=(const Matrix3& rhs) { return *this = *this - rhs; }

    XMMATRIX Matrix3::operator*(const Matrix3& rhs) const { return XMMatrixMultiply(XMLoadFloat3x3(this), XMLoadFloat3x3(&rhs)); }
    XMMATRIX Matrix3::operator*(const XMMATRIX& rhs) const { return XMMatrixMultiply(XMLoadFloat3x3(this), rhs); }
    Matrix3& Matrix3::operator*=(const Matrix3& rhs) { return *this = *this * rhs; }
    Matrix3& Matrix3::operator*=(const XMMATRIX& rhs) { return *this = *this * rhs; }

    Vector3 Matrix3::operator*(const Vector3& rhs) const {
        float newX = _11 * rhs.x + _12 * rhs.y + _13 * rhs.z;
        float newY = _21 * rhs.x + _22 * rhs.y + _23 * rhs.z;
        float newZ = _31 * rhs.x + _32 * rhs.y + _33 * rhs.z;

        return{ newX, newY, newZ };
    }

    Matrix3 Matrix3::operator*(const float rhs) const{
        return{
            _11 * rhs, _12 * rhs, _13 * rhs,
            _21 * rhs, _22 * rhs, _23 * rhs,
            _31 * rhs, _32 * rhs, _33 * rhs
        };
    }

    Matrix3& Matrix3::operator*=(const float rhs) { return *this = *this * rhs; }

    Matrix3 Matrix3::operator/(const float rhs) const{
        float temp = 1 / rhs;

        return *this * temp;
    }

    Matrix3& Matrix3::operator/=(const float rhs) { return *this = *this / rhs; }

    Matrix3 Matrix3::Transpose() const{
        Matrix3 temp;
        XMStoreFloat3x3(&temp, XMMatrixTranspose(XMLoadFloat3x3(this)));

        return temp;
    }

    float Matrix3::Determinant() const{
        float det;
        XMStoreFloat(&det, XMMatrixDeterminant(XMLoadFloat3x3(this)));

        return det;
    }

    Matrix3 Matrix3::Inverse() const{
        Matrix3 temp;
        XMStoreFloat3x3(&temp, XMMatrixInverse(nullptr, XMLoadFloat3x3(this)));

        return temp;
    }

    Matrix3 Matrix3::operator-() const{
        return{
            -_11, -_12, -_13,
            -_21, -_22, -_23,
            -_31, -_32, -_33
        };
    }

    void Matrix3::Negate() { *this = -(*this); }

    bool Matrix3::IsValid() const{
        for (uint32_t x = 0; x < 3; x++){
            for (uint32_t y = 0; y < 3; y++){
                if (!Mathf::IsValid(m[x][y]))
                    return false;
            }
        }

        return true;
    }

    Matrix3 Matrix3::Identity() { return{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }; }

    XMMATRIX operator*(const XMMATRIX& lhs, const Matrix3& rhs) { return XMMatrixMultiply(lhs, XMLoadFloat3x3(&rhs)); }
}

