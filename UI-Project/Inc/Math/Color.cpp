#include "Color.h"
#include "Mathf.h"
#include "../Containers/Str.h"

namespace Pyro
{
    Color::Color() { r = g = b = a = 1.0f; }

    Color::Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color(const Color& color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }

    Color& Color::operator=(const Color& color) {
        if (this != &color) {
            r = color.r;
            g = color.g;
            b = color.b;
            a = color.a;
        }

        return *this;
    }

    Color Color::Lerp(const Color& color, float ratio) const {
        Color col;
        col.r = Mathf::Lerp(r, color.r, ratio);
        col.g = Mathf::Lerp(g, color.g, ratio);
        col.b = Mathf::Lerp(b, color.b, ratio);
        col.a = Mathf::Lerp(a, color.a, ratio);
        return col;
    }

    float Color::Average() const { return (r + g + b) / 3.0f; }

    Color Color::Red() { return Color(1, 0, 0); }
    Color Color::Green() { return Color(0, 1, 0); }
    Color Color::Blue() { return Color(0, 0, 1); }
    Color Color::Yellow() { return Color(1, 1, 0); }
    Color Color::Cyan() { return Color(0, 1, 1); }
    Color Color::Transparent() { return Color(0, 0, 0, 0); }
    Color Color::White() { return Color(1, 1, 1, 1); }
    Color Color::Black() { return Color(0, 0, 0, 1); }
    Color Color::Clear() { return Color{ 0,0,0,0 }; }
}