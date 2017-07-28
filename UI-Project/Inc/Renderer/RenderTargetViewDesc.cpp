#include "RenderTargetViewDesc.h"

namespace Pyro
{
    RenderTargetViewDesc::RenderTargetViewDesc() {
        ZeroMemory(this, sizeof(RenderTargetViewDesc));
    }

    bool RenderTargetViewDesc::operator==(const RenderTargetViewDesc& rhs) const {
        bool success = true;
        success &= dimension == rhs.dimension;
        success &= format == rhs.format;
        success &= firstElement == rhs.firstElement;
        success &= numElements == rhs.numElements;
        success &= arraySize == rhs.arraySize;
        return success;
    }

    bool RenderTargetViewDesc::operator!=(const RenderTargetViewDesc& rhs) const {
        return !(*this == rhs);
    }
}