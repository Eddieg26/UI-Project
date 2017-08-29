#include "Viewport.h"

namespace Pyro
{
    Viewport::Viewport() {
        SetDimensions(0.0f, 0.0f, 0.0f, 0.0f);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
    }

    Viewport::Viewport(float left, float top, float width, float height) {
        SetDimensions(left, top, width, height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
    }

    void Viewport::SetDimensions(float left, float top, float width, float height) {
        viewport.TopLeftX = left;
        viewport.TopLeftY = top;
        viewport.Width = width;
        viewport.Height = height;
    }
}