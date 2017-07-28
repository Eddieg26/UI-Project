#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "Enums.h"
#include "ShaderResourceViewDesc.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class ShaderResourceView : public RefCounted {
        REFCOUNTED(ShaderResourceView);

    private:
        /// D3D shader resource view
        ShaderResourceViewPtr shaderResourceView;
        /// Shader resource view description
        ShaderResourceViewDesc shaderResourceViewDesc;

    public:
        /// Construct
        ShaderResourceView();
        /// Destruct
        ~ShaderResourceView();

        /// Create shader resource view
        Result Create(RenderDevice& renderDevice, const ShaderResourceViewDesc& desc, ID3D11Resource* resource = nullptr);
        /// Release the shader resource view
        void Release();

        /// Return shader resource view
        ShaderResourceViewPtr GetShaderResourceView() const { return shaderResourceView; }
        /// Return shader resource view description
        ShaderResourceViewDesc ShaderResourceDesc() const { return shaderResourceViewDesc; }
    };
}
