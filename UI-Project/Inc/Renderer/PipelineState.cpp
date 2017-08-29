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
#include "Shader.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "ShaderResourceView.h"
#include "Viewport.h"
#include "Translate.h"

namespace Pyro
{
    Vector<BufferPtr> GetVertexBuffers(const Vector<VertexBuffer*>& vertexBuffers) {
        Vector<BufferPtr> ret;
        for (uint i = 0; i < vertexBuffers.Size(); ++i)
            ret.Add(vertexBuffers[i] ? vertexBuffers[i]->GetBuffer() : nullptr);

        return ret;
    }

    Vector<BufferPtr> GetConstantBuffers(const Vector<ConstantBuffer*>& constantBuffers) {
        Vector<BufferPtr> ret;
        for (uint i = 0; i < constantBuffers.Size(); ++i)
            ret.Add(constantBuffers[i] ? constantBuffers[i]->GetBuffer() : nullptr);

        return ret;
    }

    Vector<SamplerStatePtr> GetSamplerState(const Vector<SamplerState*>& samplers) {
        Vector<SamplerStatePtr> ret;
        for (uint i = 0; i < samplers.Size(); ++i)
            ret.Add(samplers[i] ? samplers[i]->GetSamplerState() : nullptr);

        return ret;
    }

    Vector<ShaderResourceViewPtr> GetShaderResourceViews(const Vector<ShaderResourceView*>& shaderResourceViews) {
        Vector<ShaderResourceViewPtr> ret;
        for (uint i = 0; i < shaderResourceViews.Size(); ++i)
            ret.Add(shaderResourceViews[i] ? shaderResourceViews[i]->GetShaderResourceView() : nullptr);

        return ret;
    }

    Vector<D3D11_VIEWPORT> GetViewports(const Vector<Viewport*>& viewports) {
        Vector<D3D11_VIEWPORT> ret;
        for (uint i = 0; i < viewports.Size(); ++i) {
            Viewport* viewport = viewports[i];
            ret.Add(viewport ? viewport->GetViewport() : D3D11_VIEWPORT());
        }

        return ret;
    }

    Vector<RenderTargetViewPtr> GetRenderTargets(const Vector<RenderTargetView*>& renderTargetViews) {
        Vector<RenderTargetViewPtr> ret;
        for (uint i = 0; i < renderTargetViews.Size(); ++i) {
            RenderTargetView* view = renderTargetViews[i];
            ret.Add(view ? view->GetRenderTargetView() : nullptr);
        }

        return ret;
    }

    PipelineState::PipelineState() {
        Clear();
    }

    PipelineState& PipelineState::operator=(const PipelineState& rhs) {
        if (this != &rhs) {
            inputAssembler.indexBuffer = rhs.inputAssembler.indexBuffer;
            inputAssembler.format = rhs.inputAssembler.format;
            inputAssembler.vertexBuffers = rhs.inputAssembler.vertexBuffers;
            inputAssembler.offsets = rhs.inputAssembler.offsets;
            inputAssembler.strides = rhs.inputAssembler.strides;
            inputAssembler.inputLayout = rhs.inputAssembler.inputLayout;
            inputAssembler.topologyType = rhs.inputAssembler.topologyType;

            rasterizer.rasterizerState = rhs.rasterizer.rasterizerState;
            rasterizer.viewports = rhs.rasterizer.viewports;

            outputMerger.blendState = rhs.outputMerger.blendState;
            outputMerger.depthStencilState = rhs.outputMerger.depthStencilState;
            outputMerger.depthStencilView = rhs.outputMerger.depthStencilView;
            outputMerger.renderTargetViews = rhs.outputMerger.renderTargetViews;
            outputMerger.depthtStencilRef = rhs.outputMerger.depthtStencilRef;

            vertexShaderState.shader = rhs.vertexShaderState.shader;
            vertexShaderState.constantBuffers = rhs.vertexShaderState.constantBuffers;
            vertexShaderState.samplers = rhs.vertexShaderState.samplers;
            vertexShaderState.shaderResourceViews = rhs.vertexShaderState.shaderResourceViews;

            pixelShaderState.shader = rhs.pixelShaderState.shader;
            pixelShaderState.constantBuffers = rhs.pixelShaderState.constantBuffers;
            pixelShaderState.samplers = rhs.pixelShaderState.samplers;
            pixelShaderState.shaderResourceViews = rhs.pixelShaderState.shaderResourceViews;

            geometryShaderState.shader = rhs.geometryShaderState.shader;
            geometryShaderState.constantBuffers = rhs.geometryShaderState.constantBuffers;
            geometryShaderState.samplers = rhs.geometryShaderState.samplers;
            geometryShaderState.shaderResourceViews = rhs.geometryShaderState.shaderResourceViews;

            computeShaderState.shader = rhs.computeShaderState.shader;
            computeShaderState.constantBuffers = rhs.computeShaderState.constantBuffers;
            computeShaderState.samplers = rhs.computeShaderState.samplers;
            computeShaderState.shaderResourceViews = rhs.computeShaderState.shaderResourceViews;
        }

        return *this;
    }

    void PipelineState::Bind(DeviceContextPtr context, const PipelineState& desiredState) {
        if (inputAssembler.indexBuffer != desiredState.inputAssembler.indexBuffer ||
            inputAssembler.format != desiredState.inputAssembler.format) {

            inputAssembler.indexBuffer = desiredState.inputAssembler.indexBuffer;
            inputAssembler.format = desiredState.inputAssembler.format;

            context->IASetIndexBuffer(desiredState.inputAssembler.indexBuffer->GetBuffer(), desiredState.inputAssembler.format, 0);
        }

        if (inputAssembler.vertexBuffers != desiredState.inputAssembler.vertexBuffers ||
            inputAssembler.offsets != desiredState.inputAssembler.offsets ||
            inputAssembler.strides != desiredState.inputAssembler.strides) {

            Vector<BufferPtr> buffers = GetVertexBuffers(desiredState.inputAssembler.vertexBuffers);

            inputAssembler.vertexBuffers = desiredState.inputAssembler.vertexBuffers;
            inputAssembler.offsets = desiredState.inputAssembler.offsets;
            inputAssembler.strides = desiredState.inputAssembler.strides;

            context->IASetVertexBuffers(0, buffers.Size(), buffers.Data(), desiredState.inputAssembler.strides.Data(), desiredState.inputAssembler.offsets.Data());
        }

        if (inputAssembler.inputLayout != desiredState.inputAssembler.inputLayout) {
            inputAssembler.inputLayout = desiredState.inputAssembler.inputLayout;
            context->IASetInputLayout(desiredState.inputAssembler.inputLayout->GetInputLayout());
        }

        if (inputAssembler.topologyType != desiredState.inputAssembler.topologyType) {
            inputAssembler.topologyType = desiredState.inputAssembler.topologyType;
            context->IASetPrimitiveTopology(TranslateDX11::toD3DTopology(desiredState.inputAssembler.topologyType));
        }

        if (rasterizer.rasterizerState != desiredState.rasterizer.rasterizerState) {
            rasterizer.rasterizerState = desiredState.rasterizer.rasterizerState;
            context->RSSetState(desiredState.rasterizer.rasterizerState->GetRasterizerState());
        }

        if (rasterizer.viewports != desiredState.rasterizer.viewports) {
            Vector<D3D11_VIEWPORT> viewports = GetViewports(desiredState.rasterizer.viewports);
            rasterizer.viewports = desiredState.rasterizer.viewports;
            context->RSSetViewports(viewports.Size(), viewports.Data());
        }

        if (outputMerger.blendState != desiredState.outputMerger.blendState) {
            float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
            outputMerger.blendState = desiredState.outputMerger.blendState;
            context->OMSetBlendState(desiredState.outputMerger.blendState->GetBlendState(), blendFactor, D3D11_DEFAULT_SAMPLE_MASK);
        }

        if (outputMerger.depthStencilState != desiredState.outputMerger.depthStencilState ||
            outputMerger.depthtStencilRef != desiredState.outputMerger.depthtStencilRef) {

            outputMerger.depthStencilState = desiredState.outputMerger.depthStencilState;
            outputMerger.depthtStencilRef = desiredState.outputMerger.depthtStencilRef;

            context->OMSetDepthStencilState(desiredState.outputMerger.depthStencilState->GetDepthStencilState(), desiredState.outputMerger.depthtStencilRef);
        }

        if (outputMerger.depthStencilView != desiredState.outputMerger.depthStencilView ||
            outputMerger.renderTargetViews != desiredState.outputMerger.renderTargetViews) {

            Vector<RenderTargetViewPtr> renderTargets = GetRenderTargets(desiredState.outputMerger.renderTargetViews);
            DepthStencilView* depthStencilView = desiredState.outputMerger.depthStencilView;

            outputMerger.renderTargetViews = desiredState.outputMerger.renderTargetViews;
            outputMerger.depthStencilView = desiredState.outputMerger.depthStencilView;

            context->OMSetRenderTargets(renderTargets.Size(), renderTargets.Data(), depthStencilView->GetDepthStencilView());
        }

        if (vertexShaderState.shader != desiredState.vertexShaderState.shader) {
            Shader* shader = desiredState.vertexShaderState.shader;
            vertexShaderState.shader = desiredState.vertexShaderState.shader;
            context->VSSetShader(shader ? shader->GetVertexShader() : nullptr, nullptr, 0);
        }

        if (vertexShaderState.constantBuffers != desiredState.vertexShaderState.constantBuffers) {
            Vector<BufferPtr> buffers = GetConstantBuffers(desiredState.vertexShaderState.constantBuffers);
            vertexShaderState.constantBuffers = desiredState.vertexShaderState.constantBuffers;
            context->VSSetConstantBuffers(0, buffers.Size(), buffers.Data());
        }

        if (vertexShaderState.samplers != desiredState.vertexShaderState.samplers) {
            Vector<SamplerStatePtr> samplers = GetSamplerState(desiredState.vertexShaderState.samplers);
            vertexShaderState.samplers = desiredState.vertexShaderState.samplers;
            context->VSSetSamplers(0, samplers.Size(), samplers.Data());
        }

        if (vertexShaderState.shaderResourceViews != desiredState.vertexShaderState.shaderResourceViews) {
            Vector<ShaderResourceViewPtr> shaderResourceViews = GetShaderResourceViews(desiredState.vertexShaderState.shaderResourceViews);
            vertexShaderState.shaderResourceViews = desiredState.vertexShaderState.shaderResourceViews;
            context->VSSetShaderResources(0, shaderResourceViews.Size(), shaderResourceViews.Data());
        }

        if (pixelShaderState.shader != desiredState.pixelShaderState.shader) {
            Shader* shader = desiredState.pixelShaderState.shader;
            pixelShaderState.shader = desiredState.pixelShaderState.shader;
            context->PSSetShader(shader ? shader->GetPixelShader() : nullptr, nullptr, 0);
        }

        if (pixelShaderState.constantBuffers != desiredState.pixelShaderState.constantBuffers) {
            Vector<BufferPtr> buffers = GetConstantBuffers(desiredState.pixelShaderState.constantBuffers);
            pixelShaderState.constantBuffers = desiredState.pixelShaderState.constantBuffers;
            context->PSSetConstantBuffers(0, buffers.Size(), buffers.Data());
        }

        if (pixelShaderState.samplers != desiredState.pixelShaderState.samplers) {
            Vector<SamplerStatePtr> samplers = GetSamplerState(desiredState.pixelShaderState.samplers);
            pixelShaderState.samplers = desiredState.pixelShaderState.samplers;
            context->PSSetSamplers(0, samplers.Size(), samplers.Data());
        }

        if (pixelShaderState.shaderResourceViews != desiredState.pixelShaderState.shaderResourceViews) {
            Vector<ShaderResourceViewPtr> shaderResourceViews = GetShaderResourceViews(desiredState.pixelShaderState.shaderResourceViews);
            pixelShaderState.shaderResourceViews = desiredState.pixelShaderState.shaderResourceViews;
            context->PSSetShaderResources(0, shaderResourceViews.Size(), shaderResourceViews.Data());
        }

        if (geometryShaderState.shader != desiredState.geometryShaderState.shader) {
            Shader* shader = desiredState.geometryShaderState.shader;
            context->GSSetShader(shader ? shader->GetGeometryShader() : nullptr, nullptr, 0);
        }

        if (geometryShaderState.constantBuffers != desiredState.geometryShaderState.constantBuffers) {
            Vector<BufferPtr> buffers = GetConstantBuffers(desiredState.geometryShaderState.constantBuffers);
            context->GSSetConstantBuffers(0, buffers.Size(), buffers.Data());
        }

        if (geometryShaderState.samplers != desiredState.geometryShaderState.samplers) {
            Vector<SamplerStatePtr> samplers = GetSamplerState(desiredState.geometryShaderState.samplers);
            context->GSSetSamplers(0, samplers.Size(), samplers.Data());
        }

        if (geometryShaderState.shaderResourceViews != desiredState.geometryShaderState.shaderResourceViews) {
            Vector<ShaderResourceViewPtr> shaderResourceViews = GetShaderResourceViews(desiredState.geometryShaderState.shaderResourceViews);
            context->GSSetShaderResources(0, shaderResourceViews.Size(), shaderResourceViews.Data());
        }

        if (computeShaderState.shader != desiredState.computeShaderState.shader) {
            Shader* shader = desiredState.computeShaderState.shader;
            context->CSSetShader(shader ? shader->GetComputeShader() : nullptr, nullptr, 0);
        }

        if (computeShaderState.constantBuffers != desiredState.computeShaderState.constantBuffers) {
            Vector<BufferPtr> buffers = GetConstantBuffers(desiredState.computeShaderState.constantBuffers);
            context->CSSetConstantBuffers(0, buffers.Size(), buffers.Data());
        }

        if (computeShaderState.samplers != desiredState.computeShaderState.samplers) {
            Vector<SamplerStatePtr> samplers = GetSamplerState(desiredState.computeShaderState.samplers);
            context->CSSetSamplers(0, samplers.Size(), samplers.Data());
        }

        if (computeShaderState.shaderResourceViews != desiredState.computeShaderState.shaderResourceViews) {
            Vector<ShaderResourceViewPtr> shaderResourceViews = GetShaderResourceViews(desiredState.computeShaderState.shaderResourceViews);
            context->CSSetShaderResources(0, shaderResourceViews.Size(), shaderResourceViews.Data());
        }

        *this = desiredState;
    }

    void PipelineState::Clear() {
        inputAssembler.indexBuffer = nullptr;
        inputAssembler.format = DXGI_FORMAT_UNKNOWN;
        inputAssembler.vertexBuffers.Resize(D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, nullptr);
        inputAssembler.offsets.Resize(D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, 0);
        inputAssembler.strides.Resize(D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, 0);
        inputAssembler.inputLayout = nullptr;
        inputAssembler.topologyType = TopologyType::Undefined;

        rasterizer.rasterizerState = nullptr;
        rasterizer.viewports.Resize(D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE, nullptr);

        outputMerger.blendState = nullptr;
        outputMerger.depthStencilState = nullptr;
        outputMerger.depthStencilView = nullptr;
        outputMerger.renderTargetViews.Resize(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, nullptr);
        outputMerger.depthtStencilRef = 0;

        vertexShaderState.shader = nullptr;
        vertexShaderState.constantBuffers.Resize(D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
        vertexShaderState.samplers.Resize(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
        vertexShaderState.shaderResourceViews.Resize(D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);

        pixelShaderState.shader = nullptr;
        pixelShaderState.constantBuffers.Resize(D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
        pixelShaderState.samplers.Resize(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
        pixelShaderState.shaderResourceViews.Resize(D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);

        geometryShaderState.shader = nullptr;
        geometryShaderState.constantBuffers.Resize(D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
        geometryShaderState.samplers.Resize(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
        geometryShaderState.shaderResourceViews.Resize(D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);

        computeShaderState.shader = nullptr;
        computeShaderState.constantBuffers.Resize(D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
        computeShaderState.samplers.Resize(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
        computeShaderState.shaderResourceViews.Resize(D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
    }
}