#include "RenderTargetView.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "Translate.h"

namespace Pyro
{
    D3D11_RENDER_TARGET_VIEW_DESC translateRenderTargetDesc(const RenderTargetViewDesc& desc) {
        D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
        ZeroMemory(&renderTargetDesc, sizeof(renderTargetDesc));
        renderTargetDesc.ViewDimension = TranslateDX11::toD3DRTVDimension(desc.dimension);
        renderTargetDesc.Format = desc.format;
        renderTargetDesc.Buffer.FirstElement = desc.firstElement;
        renderTargetDesc.Buffer.NumElements = desc.numElements;
        renderTargetDesc.Texture2DArray.ArraySize = desc.arraySize;

        return renderTargetDesc;
    }

    RenderTargetView::RenderTargetView() :
        renderTargetView(nullptr) {}

    RenderTargetView::~RenderTargetView() {
        Release();
    }

    Result RenderTargetView::Create(RenderDevice& renderDevice, const RenderTargetViewDesc& desc, ID3D11Resource* resource) {
        Release();

        D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc = translateRenderTargetDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateRenderTargetView(resource, &renderTargetDesc, &renderTargetView);

        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void RenderTargetView::Release() {
        SAFERELEASE(renderTargetView);
    }
}