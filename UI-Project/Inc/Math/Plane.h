#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace Pyro
{
    struct Plane {
        /// Plane normal
        Vector3 normal;
        /// Plane distance
        float distance;

    public:
        /// Construct
        Plane() {
            normal = Vector3::Up();
            distance = 0.0f;
        }

        /// Consruct from normal and distance
        Plane(const Vector3& normal, float distance) {
            Define(normal, distance);
        }

        /// Construct from 3 points
        Plane(const Vector3& point0, const Vector3& point1, const Vector3 &point2) {
            Define(point0, point1, point2);
        }

        /// Construct from another plane
        Plane(const Plane& plane) {
            this->normal = plane.normal;
            this->distance = plane.distance;
        }

        /// Assign from another plane
        Plane& operator=(const Plane& plane) {
            if (this != &plane) {
                this->normal = plane.normal;
                this->distance = plane.distance;
            }

            return *this;
        }

        /// Define from a vector3 and distance
        void Define(const Vector3& normal, float distance);

        /// Define from 3 points
        void Define(const Vector3& point0, const Vector3& point1, const Vector3 &point2);

        /// Define from a normal vector and a point on the plane.
        void Define(const Vector3& normal, const Vector3& point);

        /// Define from a 4-dimensional vector, where the w coordinate is the distance
        void Define(const Vector4& plane);

        /// Transform plane by a 4x4 matrix
        void Transform(const Matrix4& transform);

        /// Return signed distance to a point.
        float Distance(const Vector3& point) const;

        /// Reflect a normalized direction vector.
        Vector3 Reflect(const Vector3& direction) const;

        /// Return as a vector
        Vector4 ToVector4() const { return Vector4(normal.x, normal.y, normal.z, distance); }
    };
}
