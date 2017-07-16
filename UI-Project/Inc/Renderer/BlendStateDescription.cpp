#include "BlendStateDescription.h"

namespace Pyro
{
    BlendStateDescription::BlendStateDescription() :
        blendSource(BlendFactor::SourceAlpha),
        blendDestination(BlendFactor::OneMinusSrcAlpha),
        blendOp(BlendOp::Add),
        alphaSource(BlendFactor::One),
        alphaDestination(BlendFactor::OneMinusSrcAlpha),
        alphaBlendOp(BlendOp::Add),
        colorWriteMask((uint8)ColorWriteMask::All),
        enableBlend(false),
        alphaToCoverage(false) {}

    bool BlendStateDescription::operator==(const BlendStateDescription& desc) const { 
        bool success = true;
        success &= blendSource == desc.blendSource;
        success &= blendDestination == desc.blendDestination;
        success &= blendOp == desc.blendOp;
        success &= alphaSource == desc.alphaSource;
        success &= alphaDestination == desc.alphaDestination;
        success &= alphaBlendOp == desc.alphaBlendOp;
        success &= colorWriteMask == desc.colorWriteMask;
        success &= enableBlend == desc.enableBlend;
        success &= alphaToCoverage == desc.alphaToCoverage;
        return success;
    }

    bool BlendStateDescription::operator!=(const BlendStateDescription& desc) const { 
        return !(*this == desc);
    }
}