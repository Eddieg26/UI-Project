#pragma once

#include "Enums.h"
#include "../Util/types.h"

namespace Pyro
{
    struct BufferDescription {
        BufferDescription();

        bool operator==(const BufferDescription& rhs) const;
        bool operator!=(const BufferDescription& rhs) const;

        BufferType type;
        uint byteWidth;
        uint bindFlags;
        uint cpuAccessFlags;
        uint miscFlags;
        uint structuredByteStride;
        bool dynamic;
    };
}