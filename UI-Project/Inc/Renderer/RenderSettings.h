#pragma once

#include "../Util/types.h"

namespace Pyro
{
    struct RenderSettings {
        RenderSettings();

        int32 msaaQuality;
        uint msaaCount;
        uint anistropicCount;
        bool multiSampleEnabled;
        bool antiAliasedLineEnabled;
        bool vsync;
    };
}