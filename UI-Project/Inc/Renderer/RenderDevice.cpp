#include "RenderDevice.h"
#include "RenderContext.h"
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

#include <d3d11.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")

namespace Pyro
{
    bool FindAdapter(IDXGIFactory1** factory, IDXGIAdapter1** adapter) {
        HRESULT hr;
        IDXGIAdapter1* temp = nullptr;
        DXGI_ADAPTER_DESC1 bestDesc;

        hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory));
        if (!SUCCEEDED(hr)) return false;

        UINT index = 0;
        while ((*factory)->EnumAdapters1(index++, &temp) != DXGI_ERROR_NOT_FOUND) {
            DXGI_ADAPTER_DESC1 desc;
            ZeroMemory(&desc, sizeof(desc));
            temp->GetDesc1(&desc);

            if (*adapter == nullptr) {
                *adapter = temp;
                bestDesc = desc;
            }
            else if (bestDesc.DedicatedSystemMemory < desc.DedicatedSystemMemory) {
                (*adapter)->Release();
                *adapter = temp;
                bestDesc = desc;
            }
            else
                temp->Release();
        }

        return true;
    }

    RenderDevice::RenderDevice() :
        device(nullptr),
        renderContext(nullptr) {}

    RenderDevice::~RenderDevice() {
        SAFERELEASE(device);
        renderContext = nullptr;
    }

    Result RenderDevice::CreateDevice(RenderContext* renderContext) {
        this->renderContext = renderContext;

        HRESULT result;

        const D3D_FEATURE_LEVEL lvl[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1 };

        D3D_FEATURE_LEVEL supportedLvl;

        UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        IDXGIFactory1* factory = nullptr;
        IDXGIAdapter1* adapter = nullptr;

        if (!FindAdapter(&factory, &adapter))
            return Result::Failed;

        DeviceContextPtr deviceContext = renderContext->GetContext();
        result = D3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, flags, lvl, ARRAYSIZE(lvl), D3D11_SDK_VERSION, &device, &supportedLvl, &deviceContext);
        if (!SUCCEEDED(result)) 
            return Result::Failed;

        //adapter->EnumOutputs(0, &videoOutput);

        /*SET_DEBUG_NAME(device, "Device");
        SET_DEBUG_NAME(deviceContext, "Context");*/

        SAFERELEASE(factory);
        SAFERELEASE(adapter);

        return Result::Success;
    }

    Result RenderDevice::CreateBlendState(const String& name, const BlendStateDescription& desc) {
        SharedPtr<BlendState> blendState(new BlendState);
        if (blendState->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->blendStates.Add(name.ToHash(), blendState) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateDepthStencilState(const String& name, const DepthStencilStateDescription& desc) {
        SharedPtr<DepthStencilState> depthStencilState(new DepthStencilState);
        if (depthStencilState->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->depthStencilStates.Add(name.ToHash(), depthStencilState) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateRasterizerState(const String& name, const RasterizerStateDescription& desc) {
        SharedPtr<RasterizerState> rasterizerState(new RasterizerState);
        rasterizerState->Create(*this, desc);
        return renderContext->rasterizerStates.Add(name.ToHash(), rasterizerState) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateSamplerState(const String& name, const SamplerStateDescription& desc) {
        SharedPtr<SamplerState> samplerState(new SamplerState);
        if (samplerState->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->samplerStates.Add(name.ToHash(), samplerState) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateInputLayout(const String& name, const InputLayoutDescription& desc) {
        SharedPtr<InputLayout> inputLayout(new InputLayout);
        if (inputLayout->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->inputLayouts.Add(name.ToHash(), inputLayout) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateVertexBuffer(const String& name, const BufferDescription& desc) {
        SharedPtr<VertexBuffer> vertexBuffer(new VertexBuffer);
        if (vertexBuffer->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->vertexBuffers.Add(name.ToHash(), vertexBuffer) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateIndexBuffer(const String& name, const BufferDescription& desc) {
        SharedPtr<IndexBuffer> indexBuffer(new IndexBuffer);
        if (indexBuffer->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->indexBuffers.Add(name.ToHash(), indexBuffer) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateConstantBuffer(const String& name, const BufferDescription& desc) {
        SharedPtr<ConstantBuffer> constantBuffer(new ConstantBuffer);
        if (constantBuffer->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->constantBuffers.Add(name.ToHash(), constantBuffer) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateStructuredBuffer(const String& name, const BufferDescription& desc) {
        SharedPtr<StructuredBuffer> structuredBuffer(new StructuredBuffer);
        if (structuredBuffer->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->structuredBuffers.Add(name.ToHash(), structuredBuffer) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateTexture(const String& name, const TextureDescription& desc) {
        SharedPtr<D3DTexture> texture(new D3DTexture);
        if (texture->Create(*this, desc) == Result::Failed)
            return Result::Failed;

        return renderContext->textures.Add(name.ToHash(), texture) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateShader(const String& name, const String& shaderPath, ShaderType shaderType) {
        SharedPtr<Shader> shader(new Shader);
        if (shader->LoadShader(*this, shaderPath, shaderType) == Result::Failed)
            return Result::Failed;

        return renderContext->shaders.Add(name.ToHash(), shader) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateRenderTargetView(const String& name, RenderTargetViewDesc& desc, ID3D11Resource* resource) {
        SharedPtr<RenderTargetView> renderTarget(new RenderTargetView);
        if (renderTarget->Create(*this, desc, resource) == Result::Failed)
            return Result::Failed;

        return renderContext->renderTargetViews.Add(name.ToHash(), renderTarget) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateDepthStencilView(const String& name, DepthStencilViewDesc& desc, ID3D11Resource* resource) {
        SharedPtr<DepthStencilView> depthStencilView(new DepthStencilView);
        if (depthStencilView->Create(*this, desc, resource) == Result::Failed)
            return Result::Failed;

        return renderContext->depthStencilViews.Add(name.ToHash(), depthStencilView) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateShaderResourceView(const String& name, ShaderResourceViewDesc& desc, ID3D11Resource* resource) {
        SharedPtr<ShaderResourceView> shaderResourceView(new ShaderResourceView);
        if (shaderResourceView->Create(*this, desc, resource) == Result::Failed)
            return Result::Failed;

        return renderContext->shaderResourceViews.Add(name.ToHash(), shaderResourceView) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateViewport(const String& name, float left, float top, float width, float height) {
        SharedPtr<Viewport> viewport(new Viewport);
        viewport->SetDimensions(left, top, width, height);

        return renderContext->viewports.Add(name.ToHash(), viewport) ? Result::Success : Result::Failed;
    }
}