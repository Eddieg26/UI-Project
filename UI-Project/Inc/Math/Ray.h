#pragma once

#include "Vector3.h"

namespace Pyro
{
    struct Ray {
        Vector3 origin;
        Vector3 direction;

    public:
        Ray();
        Ray(const Vector3& origin, const Vector3& direction);
        Ray(const Ray& ray);
        Ray& operator=(const Ray& ray);
    };
}