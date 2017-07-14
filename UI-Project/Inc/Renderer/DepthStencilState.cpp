#include "DepthStencilState.h"

namespace Pyro
{
	DepthStencilState::DepthStencilState() : depthStencilState(nullptr) {}

	DepthStencilState::~DepthStencilState() {
		SAFERELEASE(depthStencilState)
	}

	Result DepthStencilState::Create(RenderDevice& renderDevice, const DepthStencilStateDescription& desc) {

		return Result::Failed;
	}

	void DepthStencilState::Bind(RenderContext& renderContext, bool force) const {

	}
}
