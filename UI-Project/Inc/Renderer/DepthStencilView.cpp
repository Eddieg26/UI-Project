#include "DepthStencilView.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"

namespace Pyro
{
    D3D11_DEPTH_STENCIL_VIEW_DESC translateDepthStencilViewDesc(const DepthStencilViewDesc& desc) {
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
        depthStencilDesc.ViewDimension = TranslateDX11::toD3DDSVDimension(desc.dimension);
        depthStencilDesc.Format = desc.format;
        depthStencilDesc.Flags = desc.flags;
        depthStencilDesc.Texture1DArray.MipSlice = desc.mipSlice;
        depthStencilDesc.Texture1DArray.FirstArraySlice = desc.firstArraySlice;
        depthStencilDesc.Texture1DArray.ArraySize = desc.arraySize;

        return depthStencilDesc;
    }

    DepthStencilView::DepthStencilView() : depthStencilView(nullptr) {}

    DepthStencilView::~DepthStencilView() {
        Release();
    }

    Result DepthStencilView::Create(RenderDevice& renderDevice, const DepthStencilViewDesc& desc, ID3D11Resource* resource) {
        Release();

        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = translateDepthStencilViewDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateDepthStencilView(resource, &depthStencilDesc, &depthStencilView);

        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void DepthStencilView::Release() {
        SAFERELEASE(depthStencilView);
    }
}