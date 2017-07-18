#include "RenderDevice.h"
#include "RenderContext.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "InputLayout.h"

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
        blendState->Create(*this, desc);
        return renderContext->blendStates.Add(name.ToHash(), SharedPtr<BlendState>(blendState)) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateDepthStencilState(const String& name, const DepthStencilStateDescription& desc) {
        SharedPtr<DepthStencilState> depthStencilState(new DepthStencilState);
        depthStencilState->Create(*this, desc);
        return renderContext->depthStencilStates.Add(name.ToHash(), SharedPtr<DepthStencilState>(depthStencilState)) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateRasterizerState(const String& name, const RasterizerStateDescription& desc) {
        SharedPtr<RasterizerState> rasterizerState(new RasterizerState);
        rasterizerState->Create(*this, desc);
        return renderContext->rasterizerStates.Add(name.ToHash(), SharedPtr<RasterizerState>(rasterizerState)) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateSamplerState(const String& name, const SamplerStateDescription& desc) {
        SharedPtr<SamplerState> samplerState(new SamplerState);
        samplerState->Create(*this, desc);
        return renderContext->samplerStates.Add(name.ToHash(), SharedPtr<SamplerState>(samplerState)) ? Result::Success : Result::Failed;
    }

    Result RenderDevice::CreateInputLayout(const String& name, const InputLayoutDescription& desc) {
        SharedPtr<InputLayout> inputLayout(new InputLayout);
        inputLayout->Create(*this, desc);
        return renderContext->inputLayouts.Add(name.ToHash(), SharedPtr<InputLayout>(inputLayout)) ? Result::Success : Result::Failed;
    }

}