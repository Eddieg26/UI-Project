#include "ShaderResourceViewDesc.h"

namespace Pyro
{
    ShaderResourceViewDesc::ShaderResourceViewDesc() {
        ZeroMemory(this, sizeof(ShaderResourceViewDesc));
    }

    bool ShaderResourceViewDesc::operator==(const ShaderResourceViewDesc& rhs) const {
        bool success = true;
        success &= firstElement == rhs.firstElement;
        success &= numElements == rhs.numElements;
        success &= firstArraySlice == rhs.firstArraySlice;
        success &-arraySize == rhs.arraySize;
        return success;
    }

    bool ShaderResourceViewDesc::operator!=(const ShaderResourceViewDesc& rhs) const {
        return !(*this == rhs);
    }
}