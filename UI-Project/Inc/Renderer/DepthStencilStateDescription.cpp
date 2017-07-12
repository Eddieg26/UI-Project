#include "DepthStencilStateDescription.h"

namespace Pyro
{
    StencilOpDescription::StencilOpDescription() :
        stencilFailOp(StencilOp::Keep),
        stencilPassOp(StencilOp::Keep),
        depthFailOp(StencilOp::Keep),
        stencilFunc(CompareFunc::Always) {}

    bool StencilOpDescription::operator ==(const StencilOpDescription& rhs) const {
        bool success = true;
        success &= stencilFailOp == rhs.stencilFailOp;
        success &= stencilPassOp == rhs.stencilPassOp;
        success &= depthFailOp == rhs.depthFailOp;
        success &= stencilFunc == rhs.stencilFunc;
        return success;
    }

    bool StencilOpDescription::operator !=(const StencilOpDescription& rhs) const {
        return !(*this == rhs);
    }

    DepthStencilStateDescription::DepthStencilStateDescription() :
        depthEnable(true),
        stencilEnable(false),
        depthWrite(true),
        depthFunc(CompareFunc::Less) {}

    bool DepthStencilStateDescription::operator ==(const DepthStencilStateDescription& rhs) const {
        bool success = true;
        success &= depthEnable == rhs.depthEnable;
        success &= stencilEnable == rhs.stencilEnable;
        success &= depthWrite == rhs.depthWrite;
        success &= depthFunc == rhs.depthFunc;
        success &= frontFace == rhs.frontFace;
        success &= backFace == rhs.backFace;
        return success;
    }

    bool DepthStencilStateDescription::operator !=(const DepthStencilStateDescription& rhs) const {
        return !(*this == rhs);
    }
}