#include "DepthStencilState.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"

namespace Pyro
{
    D3D11_DEPTH_STENCILOP_DESC translateDepthStencilOpDesc(const StencilOpDescription& desc) {
        D3D11_DEPTH_STENCILOP_DESC stencilOpDesc;
        ZeroMemory(&stencilOpDesc,sizeof(stencilOpDesc));
        stencilOpDesc.StencilPassOp = TranslateDX11::toD3DStencilOP(desc.stencilPassOp);
        stencilOpDesc.StencilFailOp = TranslateDX11::toD3DStencilOP(desc.stencilFailOp);
        stencilOpDesc.StencilDepthFailOp = TranslateDX11::toD3DStencilOP(desc.depthFailOp);
        stencilOpDesc.StencilFunc = TranslateDX11::toD3DComparisonFunc(desc.stencilFunc);

        return stencilOpDesc;
    }

    D3D11_DEPTH_STENCIL_DESC translateDepthStencilDesc(const DepthStencilStateDescription& desc) {
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
        depthStencilDesc.DepthEnable = desc.depthEnable;
        depthStencilDesc.StencilEnable = desc.stencilEnable;
        depthStencilDesc.DepthWriteMask = desc.depthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
        depthStencilDesc.DepthFunc = TranslateDX11::toD3DComparisonFunc(desc.depthFunc);
        depthStencilDesc.FrontFace = translateDepthStencilOpDesc(desc.frontFace);
        depthStencilDesc.BackFace = translateDepthStencilOpDesc(desc.backFace);
        depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

        return depthStencilDesc;
    }

	DepthStencilState::DepthStencilState() : depthStencilState(nullptr) {}

	DepthStencilState::~DepthStencilState() {
        Release();
	}

	Result DepthStencilState::Create(RenderDevice& renderDevice, const DepthStencilStateDescription& desc) {
        Release();

        D3D11_DEPTH_STENCIL_DESC depthStencilDesc = translateDepthStencilDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);

        depthStencilDescription = desc;
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
	}

    void DepthStencilState::Release() {
        SAFERELEASE(depthStencilState);
    }

}
