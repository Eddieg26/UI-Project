#include "BufferDescription.h"

namespace Pyro
{
    BufferDescription::BufferDescription() :
        type(BufferType::Vertex),
        byteWidth(0),
        bindFlags(0),
        cpuAccessFlags(0),
        miscFlags(0),
        structuredByteStride(0),
        dynamic(false) {}

    bool BufferDescription::operator==(const BufferDescription& rhs) const {
        bool success = true;
        success &= type == rhs.type;
        success &= byteWidth == rhs.byteWidth;
        success &= bindFlags == rhs.bindFlags;
        success &= cpuAccessFlags == rhs.cpuAccessFlags;
        success &= miscFlags == rhs.miscFlags;
        success &= structuredByteStride == rhs.structuredByteStride;
        success &= dynamic == rhs.dynamic;
        return success;
    }

    bool BufferDescription::operator!=(const BufferDescription& rhs) const {
        return !(*this == rhs);
    }
}