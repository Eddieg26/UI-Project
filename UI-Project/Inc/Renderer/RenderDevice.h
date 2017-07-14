#pragma once
#include "../Core/Object.h"
#include "../Containers/Str.h"

#include "Common.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "SamplerState.h"

namespace Pyro
{
	class RenderContext;

	class RenderDevice : public RefCounted {
		REFCOUNTED(RenderDevice);

	private:
		/// D3D Device
		DevicePtr device;
		/// Render context
		RenderContext* renderContext;

	public:
		/// Construct
		RenderDevice();
		/// Destruct
		~RenderDevice();

		/// Creates the D3D device
		Result CreateDevice(RenderContext* renderContext);

		/// Create a blend state and add it to the render context if successfully created
		Result CreateBlendState(const String& name, const BlendStateDescription& desc);
		/// Create a depth stencil state and add it to the render context if successfully created
		Result CreateDepthStencilState(const String& name, const DepthStencilState& desc);
		/// Create a rasterizer state and add it to the render context if successfully created
		Result CreateRasterizerState(const String& name, const RasterizerStateDescription& desc);
		/// Create a sampler state and add it to the render context if successfully created
		Result CreateSamplerState(const String& name, const SamplerState& desc);

		/// Return D3D device
		DevicePtr GetDevice() const { return device; }
	};
}