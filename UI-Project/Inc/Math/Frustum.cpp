#include "Frustum.h"

#include "Sphere.h"
#include "BoundingBox.h"
#include "Vector4.h"
#include "Mathf.h"

namespace Pyro
{
    Frustum::Frustum() {
        for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i) {
            vertices[i] = Vector3::Zero();
        }
    }

    Frustum::Frustum(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4& transform) {
        nearZ = Mathf::Max(nearZ, 0.0f);
        farZ = Mathf::Max(farZ, nearZ);
        float halfViewSize = Mathf::Tan(fov * Mathf::DegToRad2) / zoom;
        Vector3 near, far;

        near.z = nearZ;
        near.y = nearZ * halfViewSize;
        near.x = near.y * aspectRatio;
        far.z = farZ;
        far.y = far.z * halfViewSize;
        far.x = far.y * aspectRatio;

        Define(near, far, transform);
    }

    Frustum::Frustum(const Frustum& frustum) {
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
            planes[i] = frustum.planes[i];

        for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
            vertices[i] = frustum.vertices[i];
    }

    Frustum& Frustum::operator=(const Frustum& frustum) {

        if (this != &frustum) {
            for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
                planes[i] = frustum.planes[i];

            for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
                vertices[i] = frustum.vertices[i];
        }

        return *this;
    }

    void Frustum::Define(const Vector3& near, const Vector3& far, const Matrix4& transform) {
        vertices[0] = transform * near;
        vertices[1] = transform * Vector3(near.x, -near.y, near.z);
        vertices[2] = transform * Vector3(-near.x, -near.y, near.z);
        vertices[3] = transform * Vector3(-near.x, near.y, near.z);
        vertices[4] = transform * far;
        vertices[5] = transform * Vector3(far.x, -far.y, far.z);
        vertices[6] = transform * Vector3(-far.x, -far.y, far.z);
        vertices[7] = transform * Vector3(-far.x, far.y, far.z);
    }

    void Frustum::Transform(const Matrix4& transform) {
        for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
            vertices[i] = transform * vertices[i];

        UpdatePlanes();
    }

    Intersection Frustum::Contains(const Vector3& point) const {
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i) {
            if (planes[i].Distance(point) < 0.0f)
                return Intersection::Outside;
        }

        return Intersection::Inside;
    }

    Intersection Frustum::Intersects(const Sphere& sphere) const {
        bool allInside = true;
        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            float dist = planes[i].Distance(sphere.Center());
            if (dist < -sphere.Radius())
                return Intersection::Outside;
            else if (dist < sphere.Radius())
                allInside = false;
        }

        return allInside ? Intersection::Inside : Intersection::Intersects;
    }

    Intersection Frustum::Intersects(const BoundingBox& box) const {
        Vector3 center = box.Center();
        Vector3 edge = center - box.Min();
        bool allInside = true;

        for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
        {
            const Plane& plane = planes[i];
            float dist = (plane.normal * center) + plane.distance;
            float absDist = plane.normal.Abs() * edge;

            if (dist < -absDist)
                return Intersection::Outside;
            else if (dist < absDist)
                allInside = false;
        }

        return allInside ? Intersection::Inside : Intersection::Intersects;
    }

    void Frustum::UpdatePlanes() {
        planes[(int)FrustumPlane::Near].Define(vertices[2], vertices[1], vertices[0]);
        planes[(int)FrustumPlane::Left].Define(vertices[3], vertices[7], vertices[6]);
        planes[(int)FrustumPlane::Right].Define(vertices[1], vertices[5], vertices[4]);
        planes[(int)FrustumPlane::Up].Define(vertices[0], vertices[4], vertices[7]);
        planes[(int)FrustumPlane::Down].Define(vertices[6], vertices[5], vertices[1]);
        planes[(int)FrustumPlane::Far].Define(vertices[5], vertices[6], vertices[7]);

        // Check if we ended up with inverted planes (reflected transform) and flip in that case
        if (planes[(int)FrustumPlane::Near].Distance(vertices[5]) < 0.0f) {
            for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i) {
                planes[i].normal = -planes[i].normal;
                planes[i].distance = -planes[i].distance;
            }
        }
    }
}
