#pragma once

#include "Vector3.h"

namespace Pyro
{
    struct Sphere;
    enum class Intersection;

    struct BoundingBox {

    private:
        Vector3 min;
        Vector3 max;

    public:
        BoundingBox();
        BoundingBox(const Vector3& min, const Vector3& max);
        BoundingBox(const Vector3* vertices, unsigned count);
        BoundingBox(const BoundingBox& box);
        BoundingBox& operator=(const BoundingBox& box);

        /// Return min
        Vector3 Min() const;
        /// Return max
        Vector3 Max() const;
        /// Return center
        Vector3 Center() const;
        /// Return size
        Vector3 Size() const;
        /// Return half-size
        Vector3 HalfSize() const;

        /// Test if point is inside
        Intersection Contains(const Vector3& point) const;

        /// Test if another box is inside, outside, or intersects
        Intersection Intersects(const BoundingBox& box) const;

        /// Test is a sphere is inside, outside, or intersects
        Intersection Intersects(const Sphere& sphere) const;
    };
}
