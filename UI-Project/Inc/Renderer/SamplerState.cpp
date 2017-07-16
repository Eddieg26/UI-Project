#include "SamplerState.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"
#include "../Math/Mathf.h"

namespace Pyro
{
    D3D11_SAMPLER_DESC translateSamplerDesc(const SamplerStateDescription& desc) {
        D3D11_SAMPLER_DESC samplerDesc;
        ZeroMemory(&samplerDesc, sizeof(samplerDesc));
        samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = TranslateDX11::ToD3DWrapMode(desc.textureWrapMode);
        samplerDesc.Filter = TranslateDX11::toD3DFilter(desc.textureFilterMode);
        samplerDesc.MaxAnisotropy = 0;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MaxLOD = Mathf::FloatMax;
        samplerDesc.MinLOD = -Mathf::FloatMax;
        memcpy(samplerDesc.BorderColor, desc.color.Data(), sizeof(float) * 4);

        return samplerDesc;
    }

	SamplerState::SamplerState() : samplerState(nullptr) {}

	SamplerState::~SamplerState() {
        Release();
	}

	Result SamplerState::Create(RenderDevice& renderDevice, const SamplerStateDescription& desc) {
        Release();

        D3D11_SAMPLER_DESC samplerDesc = translateSamplerDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateSamplerState(&samplerDesc, &samplerState);

        return SUCCEEDED(result) ? Result::Success : Result::Failed;
	}

	void SamplerState::Bind(RenderContext& renderContext, bool force) const {

	}

    void SamplerState::Release() {
        SAFERELEASE(samplerState);
    }

}