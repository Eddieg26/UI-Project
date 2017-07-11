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

    bool BlendStateDescription::operator==(const BlendStateDescription& desc) const { return false; }
    bool BlendStateDescription::operator!=(const BlendStateDescription& desc) const { return false; }

}