#include "RenderContext.h"
#include "PipelineState.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "StructuredBuffer.h"
#include "D3DTexture.h"
#include "Shader.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "ShaderResourceView.h"
#include "Viewport.h"

#include "../Math/Color.h"

namespace Pyro
{
    RenderContext::RenderContext() : context(nullptr) {}

    RenderContext::~RenderContext() {
        SAFERELEASE(context);
    }

    void RenderContext::Apply() {
        currentPipelineState.Apply(context, desiredPipelineState);
    }

    void RenderContext::ClearState() {
        desiredPipelineState.Clear();
        Apply();
    }

    void RenderContext::ResetRenderTargets() {
        for (uint i = 0; i < desiredPipelineState.outputMerger.renderTargetViews.Size(); ++i)
            desiredPipelineState.outputMerger.renderTargetViews[i] = nullptr;
    }

    void RenderContext::ClearRenderTargets(const Color& color) {
        uint renderTargetCount = desiredPipelineState.outputMerger.renderTargetViews.Size();
        const float* colorData = color.data;
        for (uint i = 0; i < renderTargetCount; ++i) {
            RenderTargetView* renderTargetView = desiredPipelineState.outputMerger.renderTargetViews[i];
            if (renderTargetView) {
                context->ClearRenderTargetView(renderTargetView->GetRenderTargetView(), color.Data());
            }
        }
    }

    void RenderContext::ClearDepthStencilView(float depth) {
        DepthStencilView* depthStencilView = desiredPipelineState.outputMerger.depthStencilView;
        if (depthStencilView)
            context->ClearDepthStencilView(depthStencilView->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, 0);
    }

    void RenderContext::IASetIndexBuffer(IndexBuffer* buffer) {
        desiredPipelineState.inputAssembler.indexBuffer = buffer;
    }

    void RenderContext::IASetFormat(DXGI_FORMAT format) {
        desiredPipelineState.inputAssembler.format = format;
    }

    void RenderContext::IASetVertexBuffer(VertexBuffer* buffer, uint stride, uint offset, uint slot) {
        desiredPipelineState.inputAssembler.vertexBuffers[slot] = buffer;
        desiredPipelineState.inputAssembler.strides[slot] = stride;
        desiredPipelineState.inputAssembler.offsets[slot] = offset;
    }

    void RenderContext::IASetInputLayout(InputLayout* inputLayout) {
        desiredPipelineState.inputAssembler.inputLayout = inputLayout;
    }

    void RenderContext::IASetTopology(TopologyType type) {
        desiredPipelineState.inputAssembler.topologyType = type;
    }

    void RenderContext::RSSetRasterizerState(RasterizerState* rasterizerState) {
        desiredPipelineState.rasterizer.rasterizerState = rasterizerState;
    }

    void RenderContext::RSSetViewport(Viewport* viewport, uint slot) {
        desiredPipelineState.rasterizer.viewports[slot] = viewport;
    }

    void RenderContext::OMSetBlendState(BlendState* blendState) {
        desiredPipelineState.outputMerger.blendState = blendState;
    }

    void RenderContext::OMSetDepthStencilState(DepthStencilState* depthStencilState) {
        desiredPipelineState.outputMerger.depthStencilState = depthStencilState;
    }

    void RenderContext::OMSetDepthStencilView(DepthStencilView* depthStencilView) {
        desiredPipelineState.outputMerger.depthStencilView = depthStencilView;
    }

    void RenderContext::OMSetRenderTargetView(RenderTargetView* renderTarget, uint slot) {
        desiredPipelineState.outputMerger.renderTargetViews[slot] = renderTarget;
    }

    void RenderContext::OMSetDepthStencilRef(uint depthStencilRef) {
        desiredPipelineState.outputMerger.depthtStencilRef = depthStencilRef;
    }

    void RenderContext::VSSetShader(Shader* shader) {
        desiredPipelineState.vertexShaderState.shader = shader;
    }

    void RenderContext::VSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot) {
        desiredPipelineState.vertexShaderState.constantBuffers[slot] = constantBuffer;
    }

    void RenderContext::VSSetSampler(SamplerState* samplerState, uint slot) {
        desiredPipelineState.vertexShaderState.samplers[slot] = samplerState;
    }
    void RenderContext::VSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot) {
        desiredPipelineState.vertexShaderState.shaderResourceViews[slot] = shaderResourceView;
    }

    void RenderContext::PSSetShader(Shader* shader) {
        desiredPipelineState.pixelShaderState.shader = shader;
    }

    void RenderContext::PSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot) {
        desiredPipelineState.pixelShaderState.constantBuffers[slot] = constantBuffer;
    }

    void RenderContext::PSSetSampler(SamplerState* samplerState, uint slot) {
        desiredPipelineState.pixelShaderState.samplers[slot] = samplerState;
    }
    void RenderContext::PSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot) {
        desiredPipelineState.pixelShaderState.shaderResourceViews[slot] = shaderResourceView;
    }

    void RenderContext::GSSetShader(Shader* shader) {
        desiredPipelineState.geometryShaderState.shader = shader;
    }

    void RenderContext::GSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot) {
        desiredPipelineState.geometryShaderState.constantBuffers[slot] = constantBuffer;
    }

    void RenderContext::GSSetSampler(SamplerState* samplerState, uint slot) {
        desiredPipelineState.geometryShaderState.samplers[slot] = samplerState;
    }
    void RenderContext::GSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot) {
        desiredPipelineState.geometryShaderState.shaderResourceViews[slot] = shaderResourceView;
    }

    void RenderContext::CSSetShader(Shader* shader) {
        desiredPipelineState.computeShaderState.shader = shader;
    }

    void RenderContext::CSSetConstantBuffer(ConstantBuffer* constantBuffer, uint slot) {
        desiredPipelineState.computeShaderState.constantBuffers[slot] = constantBuffer;
    }

    void RenderContext::CSSetSampler(SamplerState* samplerState, uint slot) {
        desiredPipelineState.computeShaderState.samplers[slot] = samplerState;
    }
    void RenderContext::CSSetShaderResourceView(ShaderResourceView* shaderResourceView, uint slot) {
        desiredPipelineState.computeShaderState.shaderResourceViews[slot] = shaderResourceView;
    }

    BlendState* RenderContext::GetBlendState(const String& name) {
        uint hash = name.ToHash();
        BlendState* blendState = blendStates[hash];
        return blendState;
    }

    DepthStencilState* RenderContext::GetDepthSteniclState(const String& name) {
        uint hash = name.ToHash();
        DepthStencilState* depthStencilState = depthStencilStates[hash];
        return depthStencilState;
    }

    RasterizerState* RenderContext::GetRasterizerState(const String& name) {
        uint hash = name.ToHash();
        RasterizerState* rasterizerState = rasterizerStates[hash];
        return rasterizerState;
    }

    SamplerState* RenderContext::GetSamplerState(const String& name) {
        uint hash = name.ToHash();
        SamplerState* samplerState = samplerStates[hash];
        return samplerState;
    }

    InputLayout* RenderContext::GetInputLayout(const String& name) {
        uint hash = name.ToHash();
        InputLayout* inputLayout = inputLayouts[hash];
        return inputLayout;
    }

    VertexBuffer* RenderContext::GetVertexBuffer(const String& name) {
        uint hash = name.ToHash();
        VertexBuffer* vertexBuffer = vertexBuffers[hash];
        return vertexBuffer;
    }

    IndexBuffer* RenderContext::GetIndexBuffer(const String& name) {
        uint hash = name.ToHash();
        IndexBuffer* indexBuffer = indexBuffers[hash];
        return indexBuffer;
    }

    ConstantBuffer* RenderContext::GetConstantBuffer(const String& name) {
        uint hash = name.ToHash();
        ConstantBuffer* constantBuffer = constantBuffers[hash];
        return constantBuffer;
    }

    StructuredBuffer* RenderContext::GetStructuredBuffer(const String& name) {
        uint hash = name.ToHash();
        StructuredBuffer* structuredBuffer = structuredBuffers[hash];
        return structuredBuffer;
    }

    D3DTexture* RenderContext::GetTexture(const String& name) {
        uint hash = name.ToHash();
        D3DTexture* texture = textures[hash];
        return texture;
    }

    Shader* RenderContext::GetShader(const String& name) {
        uint hash = name.ToHash();
        Shader* shader = shaders[hash];
        return shader;
    }

    RenderTargetView* RenderContext::GetRenderTargetView(const String& name) {
        uint hash = name.ToHash();
        RenderTargetView* renderTarget = renderTargetViews[hash];
        return renderTarget;
    }

    DepthStencilView* RenderContext::GetDepthStencilView(const String& name) {
        uint hash = name.ToHash();
        DepthStencilView* depthStencilView = depthStencilViews[hash];
        return depthStencilView;
    }

    ShaderResourceView* RenderContext::GetShaderResourceView(const String& name) {
        uint hash = name.ToHash();
        ShaderResourceView* shaderResourceView = shaderResourceViews[hash];
        return shaderResourceView;
    }

    Viewport* RenderContext::GetViewport(const String& name) {
        uint hash = name.ToHash();
        Viewport* viewport = viewports[hash];
        return viewport;
    }
}