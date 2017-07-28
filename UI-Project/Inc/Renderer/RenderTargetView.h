#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "RenderTargetViewDesc.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class RenderTargetView : public RefCounted {
        REFCOUNTED(RenderTargetView);

    private:
        /// D3D render target view
        RenderTargetViewPtr renderTargetView;
        /// Render target view desc
        RenderTargetViewDesc renderTargetViewDesc;

    public:
        /// Construct
        RenderTargetView();
        /// Destruct
        ~RenderTargetView();

        /// Create render target view
        Result Create(RenderDevice& renderDevice, const RenderTargetViewDesc& desc, ID3D11Resource* resource = nullptr);
        /// Release render target view
        void Release();

        /// Return render target view
        RenderTargetViewPtr GetRenderTargetView() const { return renderTargetView; }
        /// Return render target view desc
        RenderTargetViewDesc RenderTargetDesc() const { return renderTargetViewDesc; }
    };
}