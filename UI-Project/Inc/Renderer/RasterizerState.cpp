#include "RasterizerState.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"

namespace Pyro
{
    D3D11_RASTERIZER_DESC translateRasterizerDesc(const RasterizerStateDescription& desc) {
        D3D11_RASTERIZER_DESC rasterizerDesc;
        ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
        rasterizerDesc.FillMode = TranslateDX11::toD3DFillMode(desc.fillMode);
        rasterizerDesc.CullMode = TranslateDX11::toD3DCullMode(desc.cullMode);
        rasterizerDesc.FrontCounterClockwise = desc.frontFace;
        rasterizerDesc.DepthBias = desc.depthBias;
        rasterizerDesc.DepthBiasClamp = desc.biasClamp;
        rasterizerDesc.SlopeScaledDepthBias = desc.slopeBias;
        rasterizerDesc.DepthClipEnable = desc.depthClipEnable;
        rasterizerDesc.ScissorEnable = desc.scissorEnable;
        rasterizerDesc.MultisampleEnable = desc.multiSampleEnable;
        rasterizerDesc.AntialiasedLineEnable = desc.antialiasedLineEnable;

        return rasterizerDesc;
    }

	RasterizerState::RasterizerState() : rasterizerState(nullptr) {}

	RasterizerState::~RasterizerState() {
        Release();
	}

	Result RasterizerState::Create(RenderDevice& renderDevice, const RasterizerStateDescription& desc) {
        Release();

        D3D11_RASTERIZER_DESC rasterizerDesc = translateRasterizerDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

        rasterizerStateDescription = desc;
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
	}

	void RasterizerState::Bind(RenderContext& renderContext, bool force) const {
	}

    void RasterizerState::Release() {
        SAFERELEASE(rasterizerState);
    }

}