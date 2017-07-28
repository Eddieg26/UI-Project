#include "D3DTexture.h"
#include "RenderDevice.h"

namespace Pyro
{
    D3DTexture::D3DTexture() : texture1D(nullptr) {}

    D3DTexture::~D3DTexture() {
        Release();
    }

    Result D3DTexture::Create(RenderDevice& renderDevice, const TextureDescription& desc) {
        Release();

        HRESULT result;
        switch (desc.dimension)
        {
        case TextureDimension::Texture1D:
        {
            D3D11_TEXTURE1D_DESC textureDesc;
            ZeroMemory(&textureDesc, sizeof(textureDesc));
            textureDesc.Width = desc.width;
            textureDesc.Usage = desc.usage;
            textureDesc.ArraySize = 1;
            textureDesc.MipLevels = desc.depthOrMipLevels;
            textureDesc.BindFlags = desc.bindFlags;
            textureDesc.CPUAccessFlags = desc.cpuAccessFlags;
            textureDesc.Format = desc.format;
            result = renderDevice.GetDevice()->CreateTexture1D(&textureDesc, nullptr, &texture1D);
        }
            break;
        case TextureDimension::Texture2D:
        {
            D3D11_TEXTURE2D_DESC textureDesc;
            ZeroMemory(&textureDesc, sizeof(textureDesc));
            textureDesc.Width = desc.width;
            textureDesc.Height = desc.height;
            textureDesc.Usage = desc.usage;
            textureDesc.SampleDesc.Quality = 1;
            textureDesc.ArraySize = 1;
            textureDesc.MipLevels = desc.depthOrMipLevels;
            textureDesc.BindFlags = desc.bindFlags;
            textureDesc.CPUAccessFlags = desc.cpuAccessFlags;
            textureDesc.Format = desc.format;
            result = renderDevice.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &texture2D);
        }
            break;
        case TextureDimension::Texture3D:
        {
            D3D11_TEXTURE3D_DESC textureDesc;
            ZeroMemory(&textureDesc, sizeof(textureDesc));
            textureDesc.Width = desc.width;
            textureDesc.Height = desc.height;
            textureDesc.Depth = desc.depthOrMipLevels;
            textureDesc.Usage = desc.usage;
            textureDesc.MipLevels = 1;
            textureDesc.BindFlags = desc.bindFlags;
            textureDesc.CPUAccessFlags = desc.cpuAccessFlags;
            textureDesc.Format = desc.format;
        }
            break;
        default:
            result = -1;
            break;
        }

        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void D3DTexture::Release() {
        SAFERELEASE(texture1D);
    }
}