#include "Plane.h"

namespace Pyro
{
    void Plane::Define(const Vector3& normal, float distance) {
        this->normal = normal;
        this->distance = distance;
    }

    void Plane::Define(const Vector3& point0, const Vector3& point1, const Vector3 &point2) {
        Vector3 dist1 = point1 - point0;
        Vector3 dist2 = point2 - point0;

        Define(Vector3::Cross(dist1, dist2), point0);
    }

    void Plane::Define(const Vector3& normal, const Vector3& point) {
        this->normal = normal.Norm();
        this->distance = -Vector3::Dot(this->normal, point);
    }

    void Plane::Define(const Vector4& plane) {
        normal = Vector3(plane.x, plane.y, plane.z);
        distance = plane.w;
    }

    void Plane::Transform(const Matrix4& transform) {
        Define(transform.Inverse().Transpose() * ToVector4());
    }

    Vector3 Plane::Reflect(const Vector3& direction) const {
        return Vector3::Reflect(direction, normal);
    }

    float Plane::Distance(const Vector3& point) const { return normal * point + distance; }
}
