#include "DepthStencilViewDesc.h"

namespace Pyro
{
    DepthStencilViewDesc::DepthStencilViewDesc() {
        ZeroMemory(this, sizeof(DepthStencilViewDesc));
    }

    bool DepthStencilViewDesc::operator==(const DepthStencilViewDesc& rhs) const {
        bool success = true;
        success &= dimension == rhs.dimension;
        success &= format == rhs.format;
        success &= flags == rhs.flags;
        success &= mipSlice == rhs.mipSlice;
        success &= firstArraySlice == rhs.firstArraySlice;
        success &= arraySize == rhs.arraySize;
        return success;
    }

    bool DepthStencilViewDesc::operator!=(const DepthStencilViewDesc& rhs) const {
        return !(*this == rhs);
    }
}