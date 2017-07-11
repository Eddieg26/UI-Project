#include "BlendState.h"
#include "RenderContext.h"

namespace Pyro
{
    BlendState::BlendState() : blendState(nullptr) {}

    BlendState::~BlendState() {
        SAFERELEASE(blendState);
    }

    Result BlendState::Create(RenderContext& renderContext, const BlendStateDescription& desc) {

        return Result::Failed;
    }

    void BlendState::Bind(RenderContext& renderContext, bool force) const {
        // TODO:
    }

}