#pragma once
#include "../Core/RefCounted.h"

#include "SamplerStateDescription.h"
#include "Common.h"

namespace Pyro
{
	class RenderDevice;
	class RenderContext;

	class SamplerState : public RefCounted {
		REFCOUNTED(SamplerState);

	private:
		/// D3D Sampler state
		SamplerStatePtr samplerState;
		/// Sampler state description
		SamplerStateDescription samplerStateDescription;

	public:
		/// Construct
		SamplerState();
		/// Destruct
		~SamplerState();

		/// Create sampler state
		Result Create(RenderDevice& renderDevice, const SamplerStateDescription& desc);
		/// Bind sampler state
		void Bind(RenderContext& renderContext, bool force = false) const;
        /// Release D3D sampler state
        void Release();

		/// Return D3D sampler state
		SamplerStatePtr GetSamplerState() const { return samplerState; }
		/// Return sampler state description
		SamplerStateDescription SamplerStateDesc() const { return samplerStateDescription; }
	};
}