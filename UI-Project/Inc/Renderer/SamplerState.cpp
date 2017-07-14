#include "SamplerState.h"

namespace Pyro
{
	SamplerState::SamplerState() : samplerState(nullptr) {}

	SamplerState::~SamplerState() {
		SAFERELEASE(samplerState);
	}

	Result SamplerState::Create(RenderDevice& renderDevice, const SamplerStateDescription& desc) {
		return Result::Failed;
	}

	void SamplerState::Bind(RenderContext& renderContext, bool force) const {

	}
}