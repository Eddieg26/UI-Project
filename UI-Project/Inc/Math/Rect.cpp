#include "Rect.h"

#include "Vector2.h"
#include "Vector4.h"

namespace Pyro
{
    Rect::Rect() {
        x = y = width = height = 0;
    }

    Rect::Rect(const Vector2& position, const Vector2& size) {
        x = position.x;
        y = position.y;
        width = size.x;
        height = size.y;
    }

    Rect::Rect(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Rect::Rect(const Rect& rect) {
        x = rect.x;
        y = rect.y;
        width = rect.width;
        height = rect.height;
    }

    Rect& Rect::operator=(const Rect& rect) {
        if (this != &rect) {
            x = rect.x;
            y = rect.y;
            width = rect.width;
            height = rect.height;
        }

        return *this;
    }

    Vector2 Rect::Position() const { return Vector2(x, y); }
    Vector2 Rect::Size() const { return Vector2(width, height); }
    Vector2 Rect::Center() const { return Vector2(x + (width * 0.5f), y + (height * 0.5f)); }\
        Vector2 Rect::Min() const { return Vector2(x, y); }
    Vector2 Rect::Max() const { return Vector2(right(), bottom()); }

    float Rect::left() const { return x; }
    float Rect::right() const { return x + width; }
    float Rect::top() const { return y; }
    float Rect::bottom() const { return y + height; }

    const float* Rect::Data() const { return &x; }

    bool Rect::Contains(const Vector2& point) const {
        return (point.x > x && point.x < right() && point.y > y && point.y < bottom());
    }

    bool Rect::Overlaps(const Rect& rect) const {
        return (rect.x < right() && rect.right() > x && rect.y < bottom() && rect.bottom() > y);
    }

    void Rect::Set(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
}


