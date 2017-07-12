#pragma once

#include "GraphicsDefs.h"
#include "../Util/types.h"

namespace Pyro
{
    struct StencilOpDescription {
        StencilOpDescription();

        bool operator ==(const StencilOpDescription& rhs) const;
        bool operator !=(const StencilOpDescription& rhs) const;

        StencilOp stencilFailOp;
        StencilOp stencilPassOp;
        StencilOp depthFailOp;
        CompareFunc stencilFunc;
    };

    struct DepthStencilStateDescription {
        DepthStencilStateDescription();

        bool operator ==(const DepthStencilStateDescription& rhs) const;
        bool operator !=(const DepthStencilStateDescription& rhs) const;

        bool depthEnable;
        bool stencilEnable;
        bool depthWrite;
        CompareFunc depthFunc;
        StencilOpDescription frontFace;
        StencilOpDescription backFace;
    };
}