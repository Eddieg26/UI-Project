#include "BlendStateDescription.h"

namespace Pyro
{
    BlendStateDescription::BlendStateDescription() :
        blendSource(BlendFactor::SourceAlpha),
        blendDestination(BlendFactor::OneMinusSrcAlpha),
        alphaSource(BlendFactor::One),
        alphaDestination(BlendFactor::OneMinusSrcAlpha),
        colorWriteMask((uint8)ColorWriteMask::All),
        enableBlend(false),
        alphaToCoverage(false) {}

    bool BlendStateDescription::operator==(const BlendStateDescription& desc) const { 
        bool success = true;
        success &= blendSource == desc.blendSource;
        success &= blendDestination == desc.blendDestination;
        success &= alphaSource == desc.alphaSource;
        success &= alphaDestination == desc.alphaDestination;
        success &= colorWriteMask == desc.colorWriteMask;
        success &= enableBlend == desc.enableBlend;
        success &= alphaToCoverage == desc.alphaToCoverage;
        return success;
    }

    bool BlendStateDescription::operator!=(const BlendStateDescription& desc) const { 
        return !(*this == desc);
    }
}