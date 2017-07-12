#pragma once

#include "GraphicsDefs.h"
#include "../Util/types.h"

namespace Pyro
{
    struct BlendStateDescription {
        BlendStateDescription();

        bool operator==(const BlendStateDescription& desc) const;
        bool operator!=(const BlendStateDescription& desc) const;

        BlendFactor blendSource;
        BlendFactor blendDestination;

        BlendFactor alphaSource;
        BlendFactor alphaDestination;

        byte colorWriteMask;
        bool enableBlend;
        bool alphaToCoverage;
    };
}