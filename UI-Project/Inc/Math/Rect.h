#pragma once

namespace Pyro
{
    struct Vector2;
    struct Vector4;

    /// A 2D Rectangle defined by X and Y position, width and height. (Position is the top left corner)
    struct Rect {

    public:
        float x;
        float y;
        float width;
        float height;

    public:
        Rect();
        Rect(const Vector2& position, const Vector2& size);
        Rect(float x, float y, float width, float height);
        Rect(const Rect& rect);
        Rect& operator=(const Rect& rect);

        Vector2 Position() const;
        Vector2 Size() const;
        Vector2 Center() const;
        Vector2 Min() const;
        Vector2 Max() const;

        float left() const;
        float right() const;
        float top() const;
        float bottom() const;

        const float* Data() const;

        bool Contains(const Vector2& point) const;
        bool Overlaps(const Rect& rect) const;

        void Set(float x, float y, float width, float height);
    };
}
