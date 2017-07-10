#pragma once

#include "Vector3.h"
#include "MathDefs.h"

namespace Pyro
{
    struct BoundingBox;

    struct Sphere {

    private:
        Vector3 center;
        float radius;

    public:
        Sphere();
        Sphere(const Vector3& center, float radius);
        Sphere(const Sphere& sphere);
        Sphere& operator=(const Sphere& sphere);

        /// Return center
        Vector3 Center() const;
        /// Return radius
        const float Radius() const;

        /// Test if point is inside
        Intersection Contains(const Vector3& point) const;

        /// Test is another sphere is inside, outside, or intersects
        Intersection Intersects(const Sphere& sphere) const;

        /// Test if a box is inside, outside, or intersects
        Intersection Intersects(const BoundingBox& box) const;
    };
}