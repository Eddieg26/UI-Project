#include "BlendState.h"
#include "RenderContext.h"

namespace Pyro
{
	BlendState::BlendState() : blendState(nullptr) {}

	BlendState::~BlendState() {
		SAFERELEASE(blendState);
	}

	Result Create(RenderDevice& renderDevice, const BlendStateDescription& desc) {

		return Result::Failed;
	}

	void BlendState::Bind(RenderContext& renderContext, bool force) const {
	}

}