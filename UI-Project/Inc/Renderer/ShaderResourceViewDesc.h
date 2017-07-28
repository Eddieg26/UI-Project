#pragma once

#include "Common.h"
#include "Enums.h"
#include "../Util/types.h"

namespace Pyro
{
    struct ShaderResourceViewDesc {
        ShaderResourceViewDesc();

        bool operator==(const ShaderResourceViewDesc& rhs) const;
        bool operator!=(const ShaderResourceViewDesc& rhs) const;

        SRVDimension dimension;
        DXGI_FORMAT format;
        union {
            uint firstElement;
            uint mipSlice;
            uint mostDetailedMip;
            uint firstArraySliceMS;
        };
        union {
            uint numElements;
            uint elementWidth;
            uint mipLevels;
            uint arraySizeMS;
        };
        union {
            uint firstArraySlice;
            uint first2DArrayFace;
            uint flags;
        };
        union {
            uint arraySize;
            uint numCubes;
        };
    };
}