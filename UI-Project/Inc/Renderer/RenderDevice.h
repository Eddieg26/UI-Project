#pragma once
#include "../Core/Object.h"
#include "../Containers/Str.h"

#include "Common.h"
#include "Enums.h"

namespace Pyro
{
	class RenderContext;
    struct BlendStateDescription;
    struct DepthStencilStateDescription;
    struct RasterizerStateDescription;
    struct SamplerStateDescription;
    struct BufferDescription;
    struct InputLayoutDescription;

	class RenderDevice : public RefCounted {
		REFCOUNTED(RenderDevice);

	private:
		/// D3D Device
		DevicePtr device;
		/// Render context
		SharedPtr<RenderContext> renderContext;

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
		Result CreateDepthStencilState(const String& name, const DepthStencilStateDescription& desc);
		/// Create a rasterizer state and add it to the render context if successfully created
		Result CreateRasterizerState(const String& name, const RasterizerStateDescription& desc);
		/// Create a sampler state and add it to the render context if successfully created
		Result CreateSamplerState(const String& name, const SamplerStateDescription& desc);
        /// Create an input layout and add it to the render context if successfully created
        Result CreateInputLayout(const String& name, const InputLayoutDescription& desc);

		/// Return D3D device
		DevicePtr GetDevice() const { return device; }
	};
}