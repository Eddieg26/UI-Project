#pragma once

#include "../Containers/Vector.h"
#include "Common.h"
#include "Enums.h"

namespace Pyro
{
    class BlendState;
    class DepthStencilState;
    class RasterizerState;
    class SamplerState;
    class InputLayout;
    class VertexBuffer;
    class IndexBuffer;
    class ConstantBuffer;
    class StructuredBuffer;
    class Shader;
    class RenderTargetView;
    class DepthStencilView;
    class ShaderResourceView;
    class Viewport;

    struct PipelineState {
        PipelineState();

        PipelineState& operator=(const PipelineState& rhs);

        void Apply(DeviceContextPtr context, const PipelineState& desiredState);
        void Clear();

        struct InputAssembler {
            IndexBuffer* indexBuffer;
            DXGI_FORMAT format;

            Vector<VertexBuffer*> vertexBuffers;
            Vector<uint> strides;
            Vector<uint> offsets;

            InputLayout* inputLayout;
            TopologyType topologyType;
        };

        struct Rasterizer {
            RasterizerState* rasterizerState;
            Vector<Viewport*> viewports;
        };

        struct OutputMerger {
            BlendState* blendState;
            DepthStencilState* depthStencilState;
            DepthStencilView* depthStencilView;
            Vector<RenderTargetView*> renderTargetViews;

            uint depthtStencilRef;
        };

        struct VertexShaderState {
            Shader* shader;
            Vector<ConstantBuffer*> constantBuffers;
            Vector<SamplerState*> samplers;
            Vector<ShaderResourceView*> shaderResourceViews;
        };

        struct PixelShaderState {
            Shader* shader;
            Vector<ConstantBuffer*> constantBuffers;
            Vector<SamplerState*> samplers;
            Vector<ShaderResourceView*> shaderResourceViews;
        };

        struct GeometryShaderState {
            Shader* shader;
            Vector<ConstantBuffer*> constantBuffers;
            Vector<SamplerState*> samplers;
            Vector<ShaderResourceView*> shaderResourceViews;
        };

        struct ComputeShaderState {
            Shader* shader;
            Vector<ConstantBuffer*> constantBuffers;
            Vector<SamplerState*> samplers;
            Vector<ShaderResourceView*> shaderResourceViews;
        };

        InputAssembler inputAssembler;
        Rasterizer rasterizer;
        OutputMerger outputMerger;
        VertexShaderState vertexShaderState;
        PixelShaderState pixelShaderState;
        GeometryShaderState geometryShaderState;
        ComputeShaderState computeShaderState;
    };
}