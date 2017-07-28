#include "ShaderResourceView.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"

namespace Pyro
{
    D3D11_SHADER_RESOURCE_VIEW_DESC translateShaderResourceDesc(const ShaderResourceViewDesc& desc) {
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;
        ZeroMemory(&shaderResourceDesc, sizeof(shaderResourceDesc));
        shaderResourceDesc.ViewDimension = TranslateDX11::toD3DSRVDimension(desc.dimension);
        shaderResourceDesc.Format = desc.format;
        shaderResourceDesc.Buffer.FirstElement = desc.firstElement;
        shaderResourceDesc.Buffer.NumElements = desc.numElements;
        shaderResourceDesc.Texture1DArray.FirstArraySlice = desc.firstArraySlice;
        shaderResourceDesc.Texture1DArray.ArraySize = desc.arraySize;

        return shaderResourceDesc;
    }

    ShaderResourceView::ShaderResourceView() :
        shaderResourceView(nullptr) {}

    ShaderResourceView::~ShaderResourceView() {
        Release();
    }

    Result ShaderResourceView::Create(RenderDevice& renderDevice, const ShaderResourceViewDesc& desc, ID3D11Resource* resource) {
        Release();

        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc = translateShaderResourceDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateShaderResourceView(resource, &shaderResourceDesc, &shaderResourceView);

        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }
    
    void ShaderResourceView::Release() {
        SAFERELEASE(shaderResourceView);
    }
}