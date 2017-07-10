#include "Sphere.h"

#include "BoundingBox.h"

namespace Pyro
{
    Sphere::Sphere() {
        center = Vector3::Zero();
    }

    Sphere::Sphere(const Vector3& center, float radius) {
        this->center = center;
        this->radius = radius;
    }

    Sphere::Sphere(const Sphere& sphere) {
        center = sphere.center;
        radius = sphere.radius;
    }

    Sphere& Sphere::operator=(const Sphere& sphere) {
        if (this != &sphere) {
            center = sphere.center;
            radius = sphere.radius;
        }

        return *this;
    }

    Vector3 Sphere::Center() const { return center; }

    const float Sphere::Radius() const { return radius; }

    Intersection Sphere::Contains(const Vector3& point) const {

        float distance = (point - center).MagnitudeSq();
        if (distance < radius * radius)
            return Intersection::Inside;
        else
            return Intersection::Outside;
    }

    Intersection Sphere::Intersects(const Sphere& sphere) const {

        float distance = (center - sphere.center).Magnitude();
        if (distance >= radius + sphere.radius)
            return Intersection::Outside;
        else if (distance + sphere.radius < radius)
            return Intersection::Inside;
        else
            return Intersection::Intersects;
    }

    Intersection Sphere::Intersects(const BoundingBox& box) const {

        float radiusSquared = radius * radius;
        float distSquared = 0;
        float temp;
        Vector3 min = box.Min();
        Vector3 max = box.Max();

        if (center.x < min.x)
        {
            temp = center.x - min.x;
            distSquared += temp * temp;
        }
        else if (center.x > max.x)
        {
            temp = center.x - max.x;
            distSquared += temp * temp;
        }
        if (center.y < min.y)
        {
            temp = center.y - min.y;
            distSquared += temp * temp;
        }
        else if (center.y > max.y)
        {
            temp = center.y - max.y;
            distSquared += temp * temp;
        }
        if (center.z < min.z)
        {
            temp = center.z - min.z;
            distSquared += temp * temp;
        }
        else if (center.z > max.z)
        {
            temp = center.z - max.z;
            distSquared += temp * temp;
        }

        if (distSquared >= radiusSquared)
            return Intersection::Outside;

        min -= center;
        max -= center;

        Vector3 tempVec = min; // - - -
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.x = max.x; // + - -
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.y = max.y; // + + -
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.x = min.x; // - + -
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.z = max.z; // - + +
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.y = min.y; // - - +
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.x = max.x; // + - +
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;
        tempVec.y = max.y; // + + +
        if (tempVec.LengthSq() >= radiusSquared)
            return Intersection::Intersects;

        return Intersection::Inside;
    }
}