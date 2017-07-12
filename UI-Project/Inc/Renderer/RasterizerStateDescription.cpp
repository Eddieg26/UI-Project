#include "RasterizerStateDescription.h"

namespace Pyro
{
    RasterizerStateDescription::RasterizerStateDescription() :
        fillMode(FillMode::Solid),
        cullMode(CullMode::None),
        depthBias(0),
        biasClamp(0.0f),
        slopeBias(0.0f),
        frontFace(false),
        depthClipEnable(true),
        scissorEnable(false),
        multiSampleEnable(false),
        antialiasedLineEnable(false) {}

    bool RasterizerStateDescription::operator!=(const RasterizerStateDescription& desc) const {
        bool success = true;
        success &= fillMode == desc.fillMode;
        success &= cullMode == desc.cullMode;
        success &= depthBias == desc.depthBias;
        success &= biasClamp == desc.biasClamp;
        success &= slopeBias == desc.slopeBias;
        success &= frontFace == desc.frontFace;
        success &= depthClipEnable == desc.depthClipEnable;
        success &= scissorEnable == desc.scissorEnable;
        success &= multiSampleEnable == desc.multiSampleEnable;
        success &= antialiasedLineEnable == desc.antialiasedLineEnable;
        return success;
    }

    bool RasterizerStateDescription::operator!=(const RasterizerStateDescription& desc) const {
        return !(*this == desc);
    }
}