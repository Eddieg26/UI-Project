#pragma once
#include "../Core/RefCounted.h"

#include "TextureDescription.h"

namespace Pyro
{
    class RenderDevice;

    class D3DTexture : public RefCounted {
        REFCOUNTED(D3DTexture);

    private:
        union {
            Texture1DPtr texture1D;
            Texture2DPtr texture2D;
            Texture3DPtr texture3D;
        };
        /// Texture description
        TextureDescription textureDescription;

    public:
        /// Construct
        D3DTexture();
        /// Destruct
        ~D3DTexture();

        /// Create the d3d texture
        Result Create(RenderDevice& renderDevice, const TextureDescription& desc);
        /// Release the d3d texture
        void Release();

        /// Return d3d texture
        ResourcePtr GetResource() const { return texture1D; }
        /// Return texture description
        TextureDescription GetDescription() const { return textureDescription; }
    };
}