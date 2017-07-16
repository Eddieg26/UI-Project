#pragma once

#include "Enums.h"
#include "../Util/types.h"

namespace Pyro
{
    struct BlendStateDescription {
        BlendStateDescription();

        bool operator==(const BlendStateDescription& desc) const;
        bool operator!=(const BlendStateDescription& desc) const;

        BlendFactor blendSource;
        BlendFactor blendDestination;
        BlendOp blendOp;

        BlendFactor alphaSource;
        BlendFactor alphaDestination;
        BlendOp alphaBlendOp;

        byte colorWriteMask;
        bool enableBlend;
        bool alphaToCoverage;
    };
}