#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "DepthStencilStateDescription.h"

namespace Pyro
{
	class RenderDevice;
	class RenderContext;

	class DepthStencilState : public RefCounted {
		REFCOUNTED(DepthStencilState);

	private:
		/// D3D depth stencil state
		DepthStencilStatePtr depthStencilState;
		/// Depth stencil state description
		DepthStencilStateDescription depthStencilDescription;

	public:
		/// Construct
		DepthStencilState();
		/// Destruct
		~DepthStencilState();

		/// Create rasterizer state and return result
		Result Create(RenderDevice& renderDevice, const DepthStencilStateDescription& desc);
		/// Blind rasterizer state to pipeline
		void Bind(RenderContext& renderContext, bool force = false) const;

		/// Return D3D depth stencil state
		DepthStencilStatePtr GetDepthStencilState() const { return depthStencilState; }
		/// Return depth stencil description
		DepthStencilStateDescription DepthStencilDesc() const { return depthStencilDescription; }
	};
}