#pragma once

#include "Enums.h"
#include "Common.h"
#include "../Util/types.h"

namespace Pyro
{
    struct RenderTargetViewDesc {
        RenderTargetViewDesc();

        bool operator==(const RenderTargetViewDesc& rhs) const;
        bool operator!=(const RenderTargetViewDesc& rhs) const;

        RTVDimension dimension;
        DXGI_FORMAT format;
        union {
            uint firstElement;
            uint elementOffset;
            uint mipSlice;
            uint firstArraySliceMS;
        };
        union {
            uint numElements;
            uint elementWidth;
            uint firstArraySlice;
            uint arraySizeMS;
            uint firstWSlice;
        };
        union {
            uint arraySize;
            uint wSize;
        };
    };
}