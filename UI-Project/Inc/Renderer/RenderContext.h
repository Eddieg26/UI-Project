#pragma once
#include "../Core/Object.h"
#include "../Containers/Str.h"
#include "../Containers/HashMap.h"

#include "Common.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "SamplerState.h"

namespace Pyro
{
	class RenderDevice;

	class RenderContext : public RefCounted {
		REFCOUNTED(RenderContext);

		friend class RenderDevice;

	private:
		HashMap<uint, SharedPtr<BlendState>> blendStates;
		HashMap<uint, SharedPtr<DepthStencilState>> depthStencilStates;
		HashMap<uint, SharedPtr<RasterizerState>> rasterizerStates;
		HashMap<uint, SharedPtr<SamplerState>> samplerStates;

	public:
		/// Construct
		RenderContext();
		/// Destruct
		~RenderContext();

		
	};
}