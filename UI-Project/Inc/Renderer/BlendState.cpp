#include "BlendState.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"

namespace Pyro
{
    D3D11_BLEND_DESC translateBlendDesc(const BlendStateDescription& desc) {
        D3D11_BLEND_DESC blendDesc;
        ZeroMemory(&blendDesc, sizeof(blendDesc));
        blendDesc.AlphaToCoverageEnable = desc.alphaToCoverage;
        blendDesc.IndependentBlendEnable = false;
        blendDesc.RenderTarget[0].BlendEnable = desc.enableBlend;
        blendDesc.RenderTarget[0].SrcBlend = TranslateDX11::toD3DBlend(desc.blendSource);
        blendDesc.RenderTarget[0].DestBlend = TranslateDX11::toD3DBlend(desc.blendDestination);
        blendDesc.RenderTarget[0].BlendOp = TranslateDX11::toD3DBlendOp(desc.blendOp);
        blendDesc.RenderTarget[0].SrcBlendAlpha = TranslateDX11::toD3DBlend(desc.alphaSource);
        blendDesc.RenderTarget[0].DestBlendAlpha = TranslateDX11::toD3DBlend(desc.alphaDestination);
        blendDesc.RenderTarget[0].BlendOpAlpha = TranslateDX11::toD3DBlendOp(desc.alphaBlendOp);
        blendDesc.RenderTarget[0].RenderTargetWriteMask = desc.colorWriteMask;

        return blendDesc;
    }

	BlendState::BlendState() : blendState(nullptr) {}

	BlendState::~BlendState() {
        Release();
	}

	Result BlendState::Create(RenderDevice& renderDevice, const BlendStateDescription& desc) {
        Release();

        D3D11_BLEND_DESC blendDesc = translateBlendDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateBlendState(&blendDesc, &blendState);

        blendStateDescription = desc;
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
	}

	void BlendState::Bind(RenderContext& renderContext, bool force) const {
	}

    void BlendState::Release() {
        SAFERELEASE(blendState);
    }

}