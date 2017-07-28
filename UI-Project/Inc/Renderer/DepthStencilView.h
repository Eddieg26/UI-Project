#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "Enums.h"
#include "DepthStencilViewDesc.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class DepthStencilView : public RefCounted {
        REFCOUNTED(DepthStencilView);

    private:
        /// D3D11 depth stencil view
        DepthStencilViewPtr depthStencilView;
        /// Depth stenicl view desc
        DepthStencilViewDesc depthStencilViewDesc;

    public:
        /// Construct
        DepthStencilView();
        /// Destruct
        ~DepthStencilView();

        /// Create depth stencil view
        Result Create(RenderDevice& renderDevice, const DepthStencilViewDesc& desc, ID3D11Resource* resource = nullptr);
        /// Release depth stencil view
        void Release();

        /// Return depth stencil view
        DepthStencilViewPtr GetDepthStencilView() const { return depthStencilView; }
        /// Return depth stencil view desc
        DepthStencilViewDesc GetDepthStencilDesc() const { return depthStencilViewDesc; }
    };
}