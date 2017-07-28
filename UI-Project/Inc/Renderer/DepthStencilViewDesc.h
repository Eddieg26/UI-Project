#pragma once

#include "Common.h"
#include "Enums.h"
#include "../Util/types.h"

namespace Pyro
{
    struct DepthStencilViewDesc {
        DepthStencilViewDesc();

        bool operator==(const DepthStencilViewDesc& rhs) const;
        bool operator!=(const DepthStencilViewDesc& rhs) const;

        DSVDimension dimension;
        DXGI_FORMAT format;
        uint flags;
        union {
            uint mipSlice;
            uint unusedField;
            uint firstArraySliceMS;
        };
        union {
            uint firstArraySlice;
            uint arraySizeMS;
        };
        union {
            uint arraySize;
        };
    };
}