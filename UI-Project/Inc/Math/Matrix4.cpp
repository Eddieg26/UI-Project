#include "Matrix4.h"

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Mathf.h"

namespace Pyro
{
    Matrix4::Matrix4() {
        _11 = _12 = _13 = _14 = _21 = _22 = _23 = _24 = _31 = _32 = _33 = _34 = _41 = _42 = _43 = _44 = 0.0f;
    }

    Matrix4::Matrix4(const float _m11, const float _m12, const float _m13, const float _m14,
        const float _m21, const float _m22, const float _m23, const float _m24,
        const float _m31, const float _m32, const float _m33, const float _m34,
        const float _m41, const float _m42, const float _m43, const float _m44) {
        _11 = _m11; _12 = _m12; _13 = _m13; _14 = _m14;
        _21 = _m21; _22 = _m22; _23 = _m23; _24 = _m24;
        _31 = _m31; _32 = _m32; _33 = _m33; _34 = _m34;
        _41 = _m41; _42 = _m42; _43 = _m43; _44 = _m44;
    }

    Matrix4::Matrix4(const Matrix3& mat) {
        _11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = 0;
        _21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = 0;
        _31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = 0;
        _41 = 0;	   _42 = 0;		  _43 = 0;		 _44 = 0;
    }

    Matrix4::Matrix4(const XMMATRIX& mat) {
        XMStoreFloat4x4((XMFLOAT4X4*)this, mat);
    }

    bool Matrix4::operator==(const Matrix4& rhs) const {
        for (size_t i = 0; i < 16; i++) {
            if (m[i] - rhs.m[i] >= Mathf::Epsilon)
                return false;
        }

        return true;
    }

    Matrix4& Matrix4::operator=(const Matrix3& rhs) {
        _11 = rhs._11; _12 = rhs._12; _13 = rhs._13;
        _21 = rhs._21; _22 = rhs._22; _23 = rhs._23;
        _31 = rhs._31; _32 = rhs._32; _33 = rhs._33;

        return *this;
    }

    Matrix4& Matrix4::operator=(const Matrix4& rhs) {
        _11 = rhs._11; _12 = rhs._12; _13 = rhs._13; _14 = rhs._14;
        _21 = rhs._21; _22 = rhs._22; _23 = rhs._23; _24 = rhs._24;
        _31 = rhs._31; _32 = rhs._32; _33 = rhs._33; _34 = rhs._34;
        _41 = rhs._41; _42 = rhs._42; _43 = rhs._43; _44 = rhs._44;

        return *this;
    }

    Matrix4& Matrix4::operator=(const XMFLOAT3X3& rhs) { return operator=(*(Matrix3*)&rhs); }
    Matrix4& Matrix4::operator=(const XMFLOAT4X4& rhs) { return operator=(*(Matrix4*)&rhs); }

    Matrix4& Matrix4::operator=(const XMMATRIX& rhs) {
        XMStoreFloat4x4((XMFLOAT4X4*)this, rhs);

        return *this;
    }

    Matrix4 Matrix4::operator+(const Matrix4& rhs) const {
        return{
            _11 + rhs._11, _12 + rhs._12, _13 + rhs._13, _14 + rhs._14,
            _21 + rhs._21, _22 + rhs._22, _23 + rhs._23, _24 + rhs._24,
            _31 + rhs._31, _32 + rhs._32, _33 + rhs._33, _34 + rhs._34,
            _41 + rhs._41, _42 + rhs._42, _43 + rhs._43, _44 + rhs._44
        };
    }

    Matrix4& Matrix4::operator+=(const Matrix4& rhs) { return *this = *this + rhs; }

    Matrix4 Matrix4::operator-(const Matrix4& rhs) const {
        return{
            _11 - rhs._11, _12 - rhs._12, _13 - rhs._13, _14 - rhs._14,
            _21 - rhs._21, _22 - rhs._22, _23 - rhs._23, _24 - rhs._24,
            _31 - rhs._31, _32 - rhs._32, _33 - rhs._33, _34 - rhs._34,
            _41 - rhs._41, _42 - rhs._42, _43 - rhs._43, _44 - rhs._44
        };
    }

    Matrix4& Matrix4::operator-=(const Matrix4& rhs) { return *this = *this - rhs; }

    XMMATRIX Matrix4::operator*(const Matrix4& rhs) const { return XMMatrixMultiply(XMLoadFloat4x4(this), XMLoadFloat4x4(&rhs)); }
    XMMATRIX Matrix4::operator*(const XMMATRIX& rhs) const { return XMMatrixMultiply(XMLoadFloat4x4(this), rhs); }
    Matrix4& Matrix4::operator*=(const Matrix4& rhs) { return *this = *this * rhs; }
    Matrix4& Matrix4::operator*=(const XMMATRIX& rhs) { return *this = *this * rhs; }

    Vector4 Matrix4::operator*(const Vector4& rhs) const {
        Vector4 vec;
        XMStoreFloat4(&vec, XMVector4Transform(XMLoadFloat4(&rhs), XMLoadFloat4x4(this)));

        return vec;
    }

    Matrix4 Matrix4::operator*(const float rhs) const {
        return{
            _11 * rhs, _12 * rhs, _13 * rhs, _14 * rhs,
            _21 * rhs, _22 * rhs, _23 * rhs, _24 * rhs,
            _31 * rhs, _32 * rhs, _33 * rhs, _34 * rhs,
            _41 * rhs, _42 * rhs, _43 * rhs, _44 * rhs
        };
    }

    Matrix4& Matrix4::operator*=(const float rhs) { return *this = *this * rhs; }

    Matrix4 Matrix4::operator/(const float rhs) const {
        float temp = 1 / rhs;

        return *this * temp;
    }

    Matrix4& Matrix4::operator/=(const float rhs) { return *this = *this / rhs; }

    Vector3 Matrix4::Forward() const { return Vector3(_31, _32, _33).Normalize(); }

    Vector3 Matrix4::Right() const { return Vector3(_11, _12, _13).Normalize(); }

    Vector3 Matrix4::Up() const { return Vector3(_21, _22, _23).Normalize(); }

    Vector3 Matrix4::Translation() const { return{ _41, _42, _43 }; }

    Matrix4 Matrix4::Transpose() const {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixTranspose(XMLoadFloat4x4(this)));

        return mat;
    }

    float Matrix4::Determinant() const {
        float det;
        XMStoreFloat(&det, XMMatrixDeterminant(XMLoadFloat4x4(this)));

        return det;
    }

    Matrix4 Matrix4::Inverse() const {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixInverse(nullptr, XMLoadFloat4x4(this)));

        return mat;
    }

    void Matrix4::RotateAround(const Vector3& point, const Vector3& axis, const float angle) {
        // translate our matrix by subracting the point so we are rotating around the origin
        _41 -= point.x; _42 -= point.y; _43 -= point.z;

        // Perform the axis rotation around the origin
        XMStoreFloat4x4(this, XMMatrixRotationAxis(XMLoadFloat3(&axis), angle) * (*this));

        // translate the matrix back by the point
        _41 += point.x; _42 += point.y; _43 += point.z;
    }

    void Matrix4::LookAt(const Vector3& position, const Vector3& lookTo) {
        Vector3 newZ = (lookTo - position).Norm();
        Vector3 newX = (Vector3().Up() ^ newZ).Norm();
        Vector3 newY = (newZ ^ newX).Norm();

        _11 = newX.x; _12 = newX.y; _13 = newX.z;
        _21 = newY.x; _22 = newY.y; _23 = newY.z;
        _31 = newZ.x; _32 = newZ.y; _33 = newZ.z;
    }

    bool Matrix4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const {
        XMVECTOR trans;
        XMVECTOR rot;
        XMVECTOR scl;

        if (XMMatrixDecompose(&scl, &rot, &trans, XMLoadFloat4x4(this)))
        {
            XMStoreFloat3(&translation, trans);
            XMStoreFloat3(&scale, scl);
            XMStoreFloat4(&rotation, rot);

            return true;
        }

        return false;
    }

    bool Matrix4::DecomposeTranslation(Vector3& translation) const {
        XMVECTOR trans;
        XMVECTOR rot;
        XMVECTOR scl;

        if (XMMatrixDecompose(&trans, &rot, &scl, XMLoadFloat4x4(this)))
        {
            XMStoreFloat3(&translation, trans);

            return true;
        }

        return false;
    }

    bool Matrix4::DecomposeRotation(Quaternion& rotation) const {
        XMStoreFloat4(&rotation, XMQuaternionRotationMatrix(XMLoadFloat4x4(this)));

        return true;
    }

    bool Matrix4::DecomposeScale(Vector3& scale) const {
        XMVECTOR trans;
        XMVECTOR rot;
        XMVECTOR scl;

        if (XMMatrixDecompose(&trans, &rot, &scl, XMLoadFloat4x4(this))) {
            XMStoreFloat3(&scale, scl);

            return true;
        }

        return false;
    }

    Vector3 Matrix4::GetRotation() const {
        Vector3 Euler;

        if (fabs(_31) != 1.0f) {
            Euler.y = -asinf(_31);

            float cosx = cosf(Euler.x);

            // Dot our forward with the global forward to determine if we need to negate our y rotation
            // This allows us to get from -180 to 180 rotation on the y
            float forward = (Forward() * Vector3::Forward());

            if (forward > 0.0f)
                Euler.y = -Euler.y + Mathf::PI;

            Euler.x = atan2f(_32 / cosf(cosx), _33 / cosf(cosx));
            Euler.z = atan2f(_21 / cosf(cosx), _11 / cosf(cosx));
        }
        else {
            Euler.z = 0;

            if (_31 == -1.0f) {
                Euler.y = (Mathf::PI / 2);
                Euler.x = atan2f(_12, _13);
            }
            else {
                Euler.y = -(Mathf::PI / 2);
                Euler.x = atan2f(-_12, -_13);
            }
        }

        return Euler;
    }

    Vector3 Matrix4::GetScale() const {
        Vector3 scale;
        scale.x = Vector3(_11, _12, _13).Length();
        scale.y = Vector3(_21, _22, _23).Length();
        scale.z = Vector3(_31, _32, _33).Length();

        return scale;
    }

    Matrix4 Matrix4::operator-() const {
        return{
            -_11, -_12, -_13, -_14,
            -_21, -_22, -_23, -_24,
            -_31, -_32, -_33, -_34,
            -_41, -_42, -_43, -_44
        };
    }

    void Matrix4::Negate() { *this = -(*this); }

    bool Matrix4::IsValid() const {
        for (uint32_t x = 0; x < 4; x++) {
            for (uint32_t y = 0; y < 4; y++) {
                if (!Mathf::IsValid(m[x][y]))
                    return false;
            }
        }

        return true;
    }

    Matrix4 Matrix4::Empty() {
        return{
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
        };
    }

    Matrix4 Matrix4::Identity() {
        return{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    }

    Matrix4 Matrix4::Translate(const float x, const float y, const float z) {
        Matrix4 mat(Matrix4::Identity());
        mat._41 = x; mat._42 = y; mat._43 = z;

        return mat;
    }

    Matrix4 Matrix4::Translate(const Vector3& vec) {
        Matrix4 mat(Matrix4::Identity());
        mat._41 = vec.x; mat._42 = vec.y; mat._43 = vec.z;

        return mat;
    }

    Matrix4 Matrix4::Translate(const Vector4& vec) {
        Matrix4 mat(Matrix4::Identity());
        mat._41 = vec.x; mat._42 = vec.y; mat._43 = vec.z;

        return mat;
    }

    Matrix4 Matrix4::RotationX(const float xRotation) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixRotationX(xRotation));

        return mat;
    }

    Matrix4 Matrix4::RotationY(const float yRotation) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixRotationY(yRotation));

        return mat;
    }

    Matrix4 Matrix4::RotationZ(const float zRotation) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixRotationZ(zRotation));

        return mat;
    }

    Matrix4 Matrix4::Scale(const float x, const float y, const float z) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixScaling(x, y, z));

        return mat;
    }

    Matrix4 Matrix4::Scale(const Vector3& vec) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixScaling(vec.x, vec.y, vec.z));

        return mat;
    }

    Matrix4 Matrix4::Scale(const Vector4& vec) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixScaling(vec.x, vec.y, vec.z));

        return mat;
    }

    Matrix4 Matrix4::Affine(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) {
        Matrix4 mat;
        XMStoreFloat4x4(&mat, XMMatrixAffineTransformation(XMLoadFloat3(&scale), XMVectorZero(), XMLoadFloat4(&rotation), XMLoadFloat3(&translation)));

        return mat;
    }

    XMMATRIX operator*(const XMMATRIX& lhs, const Matrix4& rhs) { return XMMatrixMultiply(lhs, XMLoadFloat4x4(&rhs)); }

    void Vec3TransformCoordArray(Vector3* pOut, size_t outStride, Vector3* pIn, size_t inStride, size_t count, Matrix4* matrix) {
        XMVector3TransformCoordStream(pOut, outStride, pIn, inStride, count, XMLoadFloat4x4(matrix));
    }
}
