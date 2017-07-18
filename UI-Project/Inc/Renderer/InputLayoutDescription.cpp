#include "InputLayoutDescription.h"

namespace Pyro
{
    InputElementDescription::InputElementDescription() :
        semanticName(""),
        semanticIndex(0),
        format(DXGI_FORMAT_UNKNOWN),
        inputSlot(0),
        alignedByteOffset(0),
        instanceStepRate(0),
        isVertexSlot(false) {}

    bool InputElementDescription::operator==(const InputElementDescription& rhs) const {
        bool success = true;
        success &= semanticName == rhs.semanticName;
        success &= semanticIndex == rhs.semanticIndex;
        success &= format == rhs.format;
        success &= inputSlot == rhs.inputSlot;
        success &= alignedByteOffset == rhs.alignedByteOffset;
        success &= instanceStepRate == rhs.instanceStepRate;
        success &= isVertexSlot == rhs.isVertexSlot;
        return success;
    }

    bool InputElementDescription::operator!=(const InputElementDescription& rhs) const {
        return !(*this == rhs);
    }

    InputLayoutDescription::InputLayoutDescription() :
        shaderByteCode(nullptr),
        byteCodeLength(0) {}

    bool InputLayoutDescription::operator==(const InputLayoutDescription& rhs) const {
        if (inputElements.Size() != rhs.inputElements.Size())
            return false;

        for (uint i = 0; i < inputElements.Size(); ++i) {
            if (inputElements[i] != rhs.inputElements[i])
                return false;
        }

        if (shaderByteCode != rhs.shaderByteCode || byteCodeLength != rhs.byteCodeLength)
            return false;

        return true;
    }

    bool InputLayoutDescription::operator!=(const InputLayoutDescription& rhs) const {
        return !(*this == rhs);
    }

}