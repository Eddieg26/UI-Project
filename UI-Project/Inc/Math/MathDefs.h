#pragma once

#include "BoundingBox.h"
#include "Color.h"
#include "Frustum.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Ray.h"
#include "Rect.h"
#include "Sphere.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Pyro
{
    typedef Vector2 float2;
    typedef Vector3 float3;
    typedef Vector4 float4;
    typedef Matrix3 float3x3;
    typedef Matrix4 float4x4;

    /// Intersection test result
    enum class Intersection {
        Outside,
        Intersects,
        Inside
    };

    /// Frustum planes.
    enum class FrustumPlane {
        Near,
        Left,
        Right,
        Up,
        Down,
        Far,
    };
}