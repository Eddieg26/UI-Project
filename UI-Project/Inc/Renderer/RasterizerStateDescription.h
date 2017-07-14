#pragma once

#include "Enums.h"
#include "../Util/types.h"

namespace Pyro
{
    struct RasterizerStateDescription {
        RasterizerStateDescription();

        bool operator==(const RasterizerStateDescription& desc) const;
        bool operator!=(const RasterizerStateDescription& desc) const;

        FillMode fillMode;
        CullMode cullMode;
        int depthBias;
        float biasClamp;
        float slopeBias;
        bool frontFace;
        bool depthClipEnable;
        bool scissorEnable;
        bool multiSampleEnable;
        bool antialiasedLineEnable;
    };
}