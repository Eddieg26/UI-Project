#include "RenderSettings.h"

namespace Pyro
{
    RenderSettings::RenderSettings() :
        msaaQuality(0),
        msaaCount(0),
        anistropicCount(0),
        multiSampleEnabled(false),
        antiAliasedLineEnabled(false),
        vsync(false) {}
}