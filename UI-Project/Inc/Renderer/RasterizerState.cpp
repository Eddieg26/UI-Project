#include "RasterizerState.h"

namespace Pyro
{
	RasterizerState::RasterizerState() : rasterizerState(nullptr) {}

	RasterizerState::~RasterizerState() {
		SAFERELEASE(rasterizerState);
	}

	Result RasterizerState::Create(RenderDevice& renderDevice, const RasterizerStateDescription& desc) {

		return Result::Failed;
	}

	void RasterizerState::Bind(RenderContext& renderContext, bool force) const {
	}

}