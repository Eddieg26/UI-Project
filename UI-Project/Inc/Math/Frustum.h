#pragma once

#include "Plane.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "MathDefs.h"

namespace Pyro
{
    struct Sphere;
    struct BoundingBox;

    struct Frustum {

    public:
        static const unsigned NUM_FRUSTUM_PLANES = 6;
        static const unsigned NUM_FRUSTUM_VERTICES = 8;

        /// Frustum planes.
        Plane planes[NUM_FRUSTUM_PLANES];
        /// Frustum vertices.
        Vector3 vertices[NUM_FRUSTUM_VERTICES];

    public:
        Frustum();
        Frustum(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4& transform);
        Frustum(const Frustum& frustum);
        Frustum& operator=(const Frustum& frustum);

        /// Define with near and far dimension vectors and a transform matrix.
        void Define(const Vector3& near, const Vector3& far, const Matrix4& transform = Matrix4::Identity());

        /// Transform the frutum by a 4x4 matrix
        void Transform(const Matrix4& transform);

        /// Test if a point is inside or outside.
        Intersection Contains(const Vector3& point) const;

        /// Test if a sphere is inside, outside or intersects.
        Intersection Intersects(const Sphere& sphere) const;

        /// Test if a bounding box is inside, outside or intersects.
        Intersection Intersects(const BoundingBox& box) const;

    private:
        /// Update the planes. Called internally.
        void UpdatePlanes();
    };
}
