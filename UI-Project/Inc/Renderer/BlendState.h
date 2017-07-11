#pragma once

#include "../Core/RefCounted.h"
#include "BlendStateDescription.h"
#include "Common.h"

namespace Pyro
{
    class RenderContext;

    class BlendState : public RefCounted {
        REFCOUNTED(BlendState)

    private:
        /// D3D Blend state
        BlendStatePtr blendState;
        /// Blend state description
        BlendStateDescription blendStateDescription;

    public:
        /// Construct
        BlendState();
        /// Destruct
        ~BlendState();

        /// Create blend state and return result
        Result Create(RenderContext& renderContext, const BlendStateDescription& desc);
        /// Blind blend state to pipeline
        void Bind(RenderContext& renderContext, bool force = false) const;

        /// Return D3D Blend state
        BlendStatePtr GetBlendState() const { return blendState; }
        /// Return blendState description
        const BlendStateDescription& Desc() const { return blendStateDescription; }
    };
}