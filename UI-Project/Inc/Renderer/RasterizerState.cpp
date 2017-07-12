#include "RasterizerState.h"

namespace Pyro
{
    RasterizerState::RasterizerState() : rasterizerState(nullptr) {}

    RasterizerState::~RasterizerState() {
        SAFERELEASE(rasterizerState);
    }

    Result RasterizerState::Create(RenderContext& renderContext, const RasterizerStateDescription& desc) {
        // TODO: Need to create RenderContext class

        return Result::Failed;
    }

    void RasterizerState::Bind(RenderContext& renderContext, bool force = false) const {
        // TODO: Need to create RenderContext class
    }

}