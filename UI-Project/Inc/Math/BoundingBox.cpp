#include "BoundingBox.h"
#include "Sphere.h"
#include "Mathf.h"
#include "MathDefs.h"

namespace Pyro
{
    BoundingBox::BoundingBox() {
        min = max = Vector3::Zero();
    }

    BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) {
        this->min = min;
        this->max = max;
    }

    BoundingBox::BoundingBox(const Vector3* vertices, unsigned count) {
        min = Vector3(Mathf::FloatMax, Mathf::FloatMax, Mathf::FloatMax);
        max = Vector3(-Mathf::FloatMax, -Mathf::FloatMax, -Mathf::FloatMax);

        for (unsigned i = 0; i < count; ++i) {
            min.x = fminf(vertices[i].x, min.x);
            min.y = fminf(vertices[i].y, min.y);
            min.z = fminf(vertices[i].z, min.z);

            max.x = fmaxf(vertices[i].x, max.x);
            max.y = fmaxf(vertices[i].y, max.y);
            max.z = fmaxf(vertices[i].z, max.z);
        }
    }

    BoundingBox::BoundingBox(const BoundingBox& box) {
        min = box.min;
        max = box.max;
    }

    BoundingBox& BoundingBox::operator=(const BoundingBox& box) {
        if (this != &box) {
            min = box.min;
            max = box.max;
        }

        return *this;
    }

    Vector3 BoundingBox::Min() const { return min; }

    Vector3 BoundingBox::Max() const { return max; }

    Vector3 BoundingBox::Center() const { return (max + min) * 0.5f; }

    Vector3 BoundingBox::Size() const { return max - min; }

    Vector3 BoundingBox::HalfSize() const { return Size() * 0.5f; }

    Intersection BoundingBox::Contains(const Vector3& point) const {
        if (point.x < min.x || point.x > max.x || point.y < min.y || point.y > max.y ||
            point.z < min.z || point.z > max.z)
            return Intersection::Outside;
        else
            return Intersection::Inside;
    }

    Intersection BoundingBox::Intersects(const BoundingBox& box) const {
        if (box.max.x < min.x || box.min.x > max.x || box.max.y < min.y || box.min.y > max.y ||
            box.max.z < min.z || box.min.z > max.z)
            return Intersection::Outside;
        else if (box.min.x < min.x || box.max.x > max.x || box.min.y < min.y || box.max.y > max.y ||
            box.min.z < min.z || box.max.z > max.z)
            return Intersection::Intersects;
        else
            return Intersection::Inside;
    }

    Intersection BoundingBox::Intersects(const Sphere& sphere) const {

        float distSquared = 0;
        float temp;
        const Vector3& center = sphere.Center();

        if (center.x < min.x){
            temp = center.x - min.x;
            distSquared += temp * temp;
        }
        else if (center.x > max.x){
            temp = center.x - max.x;
            distSquared += temp * temp;
        }
        if (center.y < min.y){
            temp = center.y - min.y;
            distSquared += temp * temp;
        }
        else if (center.y > max.y){
            temp = center.y - max.y;
            distSquared += temp * temp;
        }
        if (center.z < min.z){
            temp = center.z - min.z;
            distSquared += temp * temp;
        }
        else if (center.z > max.z){
            temp = center.z - max.z;
            distSquared += temp * temp;
        }

        float radius = sphere.Radius();
        if (distSquared >= radius * radius)
            return Intersection::Outside;
        else if (center.x - radius < min.x || center.x + radius > max.x || center.y - radius < min.y ||
            center.y + radius > max.y || center.z - radius < min.z || center.z + radius > max.z)
            return Intersection::Intersects;
        else
            return Intersection::Inside;
    }
}