#pragma once
#include "../Core/Object.h"
#include "../Containers/Str.h"
#include "../Containers/HashMap.h"

#include "Common.h"
#include "Enums.h"
#include "PipelineState.h"

namespace Pyro
{
	class RenderDevice;
    class BlendState;
    class DepthStencilState;
    class RasterizerState;
    class SamplerState;
    class InputLayout;
    class VertexBuffer;
    class IndexBuffer;
    class ConstantBuffer;
    class StructuredBuffer;
    class D3DTexture;
    class Shader;
    class RenderTargetView;
    class DepthStencilView;
    class ShaderResourceView;
    class Viewport;

    struct Color;

	class RenderContext : public RefCounted {
		REFCOUNTED(RenderContext);

		friend class RenderDevice;

	private:
        /// D3D device context
        DeviceContextPtr context;
        PipelineState currentPipelineState;
        PipelineState desiredPipelineState;

		HashMap<uint, SharedPtr<BlendState>> blendStates;
		HashMap<uint, SharedPtr<DepthStencilState>> depthStencilStates;
		HashMap<uint, SharedPtr<RasterizerState>> rasterizerStates;
		HashMap<uint, SharedPtr<SamplerState>> samplerStates;
        HashMap<uint, SharedPtr<InputLayout>> inputLayouts;
        HashMap<uint, SharedPtr<VertexBuffer>> vertexBuffers;
        HashMap<uint, SharedPtr<IndexBuffer>> indexBuffers;
        HashMap<uint, SharedPtr<ConstantBuffer>> constantBuffers;
        HashMap<uint, SharedPtr<StructuredBuffer>> structuredBuffers;
        HashMap<uint, SharedPtr<D3DTexture>> textures;
        HashMap<uint, SharedPtr<Shader>> shaders;
        HashMap<uint, SharedPtr<RenderTargetView>> renderTargetViews;
        HashMap<uint, SharedPtr<DepthStencilView>> depthStencilViews;
        HashMap<uint, SharedPtr<ShaderResourceView>> shaderResourceViews;
        HashMap<uint, SharedPtr<Viewport>> viewports;

	public:
		/// Construct
		RenderContext();
		/// Destruct
		~RenderContext();

        /// Apply current pipeline state
        void Apply();
        /// Clear pipeline state
        void ClearState();

        /// Return D3D device context
        DeviceContextPtr GetContext() const { return context; }

        /// Sets render target views to null
        void ResetRenderTargets();
        /// Clear render target to color
        void ClearRenderTargets(const Color& color);
        /// Cleas depth stencil view
        void ClearDepthStencilView(float depth);

        /// Set index buffer
        void IASetIndexBuffer(IndexBuffer* buffer);
        /// Set index buffer format
        void IASetFormat(DXGI_FORMAT format);
        /// Set vertex buffer
        void IASetVertexBuffer(VertexBuffer* buffer, uint stride, uint offset, uint slot);
        /// Set input layout
        void IASetInputLayout(InputLayout* inputLayout);
        /// Set topology type
        void IASetTopology(TopologyType type);

        /// Set rasterizer state
        void RSSetRasterizerState(RasterizerState* rasterizerState);
        /// Set viewport
        void RSSetViewport(Viewport* viewport, uint slot);

        /// Set blend state
        void OMSetBlendState(BlendState* blendState);
        /// Set depth stencil state
        void OMSetDepthStencilState(DepthStencilState* depthStencilState);
        /// Set depth stencil view
        void OMSetDepthStencilView(DepthStencilView* depthStencilView);
        /// Set render target view
        void OMSetRenderTargetView(RenderTargetView* renderTarget, uint slot);
        /// Set depth stencil ref
        void OMSetDepthStencilRef(uint depthStencilRef);

        /// Set vertex shader
        void VSSetShader(Shader* shader);
        /// Set constant buffer in vertex shader
        void VSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot);
        /// Set sampler state in vertex shader
        void VSSetSampler(SamplerState* samplerState, uint slot);
        /// Set shader resource view in vertex shader
        void VSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot);

        /// Set pixel shader
        void PSSetShader(Shader* shader);
        /// Set constant buffer in pixel shader
        void PSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot);
        /// Set sampler state in pixel shader
        void PSSetSampler(SamplerState* samplerState, uint slot);
        /// Set shader resource view in pixel shader
        void PSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot);

        /// Set geometry shader
        void GSSetShader(Shader* shader);
        /// Set constant buffer in geometry shader
        void GSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot);
        /// Set sampler state in geometry shader
        void GSSetSampler(SamplerState* samplerState, uint slot);
        /// Set shader resource view in geometry shader
        void GSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot);

        /// Set compute shader
        void CSSetShader(Shader* shader);
        /// Set constant buffer in compute shader
        void CSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot);
        /// Set sampler state in compute shader
        void CSSetSampler(SamplerState* samplerState, uint slot);
        /// Set shader resource view in compute shader
        void CSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot);

        BlendState* GetBlendState(const String& name);
        DepthStencilState* GetDepthSteniclState(const String& name);
        RasterizerState* GetRasterizerState(const String& name);
        SamplerState* GetSamplerState(const String& name);
        InputLayout* GetInputLayout(const String& name);
        VertexBuffer* GetVertexBuffer(const String& name);
        IndexBuffer* GetIndexBuffer(const String& name);
        ConstantBuffer* GetConstantBuffer(const String& name);
        StructuredBuffer* GetStructuredBuffer(const String& name);
        D3DTexture* GetTexture(const String& name);
        Shader* GetShader(const String& name);
        RenderTargetView* GetRenderTargetView(const String& name);
        DepthStencilView* GetDepthStencilView(const String& name);
        ShaderResourceView* GetShaderResourceView(const String& name);
        Viewport* GetViewport(const String& name);
	};
}