#pragma once

#include "Enums.h"
#include "Common.h"
#include "../Util/types.h"

namespace Pyro
{
    struct TextureDescription {
        TextureDescription();

        TextureDimension dimension;
        DXGI_FORMAT format;
        D3D11_USAGE usage;
        uint width;
        uint height;
        uint depthOrMipLevels;
        uint bindFlags;
        uint cpuAccessFlags;
    };
}
