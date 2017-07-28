#pragma once
#include "../Core/RefCounted.h"

#include <d3d11.h>

namespace Pyro
{
    class Viewport : public RefCounted {
        REFCOUNTED(Viewport);

    private:
        D3D11_VIEWPORT viewport;

    public:
        /// Construct
        Viewport();
        Viewport(float _left, float _top, float _width, float _height);

        /// Set the viewport dimensions
        void SetDimensions(float left, float top, float width, float height);

        /// Return D3D11 viewport
        const D3D11_VIEWPORT& GetViewport() const { return viewport; }
    };
}