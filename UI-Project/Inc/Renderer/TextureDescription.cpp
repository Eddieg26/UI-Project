#include "TextureDescription.h"

namespace Pyro
{
    TextureDescription::TextureDescription() :
        dimension(TextureDimension::Unknown),
        format(DXGI_FORMAT_UNKNOWN),
        usage(D3D11_USAGE_DEFAULT),
        width(0),
        height(0),
        depthOrMipLevels(0),
        bindFlags(0),
        cpuAccessFlags(0) {}
}