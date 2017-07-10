#include "Ray.h"

namespace Pyro
{
    Ray::Ray(){}

    Ray::Ray(const Vector3& origin, const Vector3& direction) {
        this->origin = origin;
        this->direction = direction;
    }

    Ray::Ray(const Ray& ray) {
        origin = ray.origin;
        direction = ray.direction;
    }

    Ray& Ray::operator=(const Ray& ray) {
        if (this != &ray) {
            origin = ray.origin;
            direction = ray.direction;
        }

        return *this;
    }
}