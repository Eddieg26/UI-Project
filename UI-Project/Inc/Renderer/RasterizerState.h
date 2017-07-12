#pragma once

#include "../Core/RefCounted.h"
#include "RasterizerStateDescription.h"
#include "Common.h"

namespace Pyro
{
    class RenderContext;

    class RasterizerState : public RefCounted {
        REFCOUNTED(RasterizerState)

    private:
        /// D3D rasterizer state
        RasterizerStatePtr rasterizerState;
        /// Rasterizer state desecription
        RasterizerStateDescription rasterizerStateDescription;

    public:
        /// Construct
        RasterizerState();
        /// Destruct
        ~RasterizerState();

        /// Create rasterizer state and return result
        Result Create(RenderContext& renderContext, const RasterizerStateDescription& desc);
        /// Blind rasterizer state to pipeline
        void Bind(RenderContext& renderContext, bool force = false) const;

        /// Return D3D Rasterizer state
        RasterizerStatePtr GetRasterizerState() const { return rasterizerState; }
        /// Return rasterizer state description
        const RasterizerStateDescription& RasterizerDesc() const { return rasterizerStateDescription; }
    };
}