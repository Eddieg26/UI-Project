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
    struct InputLayoutDescription;
    struct BufferDescription;
    struct RenderTargetViewDesc;
    struct DepthStencilViewDesc;
    struct ShaderResourceViewDesc;
    struct TextureDescription;

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
        /// Create a vertex buffer and add it to the render context if successfully created
        Result CreateVertexBuffer(const String& name, const BufferDescription& desc);
        /// Create an index buffer and add it to the render context if successfully created
        Result CreateIndexBuffer(const String& name, const BufferDescription& desc);
        /// Create a constant buffer and add it to the render context if successfully created
        Result CreateConstantBuffer(const String& name, const BufferDescription& desc);
        /// Create a structured buffer and add it to the render context if successfully created
        Result CreateStructuredBuffer(const String& name, const BufferDescription& desc);
        /// Create a texture and add it to the render context if successfully created
        Result CreateTexture(const String& name, const TextureDescription& desc);
        /// Create a shader and add it to the render context if successfully created
        Result CreateShader(const String& name, const String& shaderPath, ShaderType shaderType);
        /// Create render target view and add it to the render context if successfully created
        Result CreateRenderTargetView(const String& name, RenderTargetViewDesc& desc, ID3D11Resource* resource = nullptr);
        /// Create depth stencil view and add it to the render context if successfully created
        Result CreateDepthStencilView(const String& name, DepthStencilViewDesc& desc, ID3D11Resource* resource = nullptr);
        /// Create shader resource view and add it to the render context if successfully created
        Result CreateShaderResourceView(const String& name, ShaderResourceViewDesc& desc, ID3D11Resource* resource = nullptr);
        /// Create view port and add it to the render context if successfully created
        Result CreateViewport(const String& name, float left, float top, float width, float height);

		/// Return D3D device
		DevicePtr GetDevice() const { return device; }
        /// Return render context
        RenderContext* GetRenderContext() const { return renderContext; }
	};
}