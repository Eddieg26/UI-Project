#pragma once

#include "../Containers/Str.h"

#include <d3d11.h>

namespace Pyro
{
    struct InputElementDescription {
        InputElementDescription();

        bool operator==(const InputElementDescription& rhs) const;
        bool operator!=(const InputElementDescription& rhs) const;

        String semanticName;
        uint semanticIndex;
        DXGI_FORMAT format;
        uint inputSlot;
        uint alignedByteOffset;
        uint instanceStepRate;
        bool isVertexSlot;
    };

    struct InputLayoutDescription {
        InputLayoutDescription();

        bool operator==(const InputLayoutDescription& rhs) const;
        bool operator!=(const InputLayoutDescription& rhs) const;

        Vector<InputElementDescription> inputElements;
        void* shaderByteCode;
        uint byteCodeLength;
    };
}