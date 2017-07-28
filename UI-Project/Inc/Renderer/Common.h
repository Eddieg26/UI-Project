#pragma once

#include <d3d11.h>

namespace Pyro
{
#define SAFERELEASE(ptr) if(ptr){ptr->Release(); ptr = nullptr;}
#define SAFEDELETE(ptr) if(ptr){delete ptr; ptr = nullptr;}
#define SAFEDELETEARRAY(ptr) if(ptr){delete[] ptr; ptr = nullptr;} 

#if defined(_DEBUG) || defined(DEBUG)
#define SET_DEBUG_NAME(resource, name) resource->SetPrivateData(WKPDID_D3DDebugObjectName, (UINT)strlen(name), name);
#else
#define SET_DEBUG_NAME(resource, name)
#endif

    typedef IDXGISwapChain* SwapChainPtr;
    typedef ID3D11Device* DevicePtr;
    typedef ID3D11DeviceContext* DeviceContextPtr;

    typedef ID3D11BlendState* BlendStatePtr;
    typedef ID3D11RasterizerState* RasterizerStatePtr;
	typedef ID3D11DepthStencilState* DepthStencilStatePtr;
	typedef ID3D11SamplerState* SamplerStatePtr;
    typedef ID3D11ShaderResourceView* ShaderResourceViewPtr;
    typedef ID3D11RenderTargetView* RenderTargetViewPtr;
    typedef ID3D11DepthStencilView* DepthStencilViewPtr;
    typedef ID3D11Resource* ResourcePtr;
    typedef ID3D11Texture1D* Texture1DPtr;
    typedef ID3D11Texture2D* Texture2DPtr;
    typedef ID3D11Texture3D* Texture3DPtr;

    typedef ID3D11InputLayout* InputLayoutPtr;
    typedef ID3D11Buffer* BufferPtr;
    typedef ID3DBlob* BlobPtr;

    typedef ID3D11VertexShader* VertexShaderPtr;
    typedef ID3D11PixelShader* PixelShaderPtr;
    typedef ID3D11GeometryShader* GeometryShaderPtr;
    typedef ID3D11ComputeShader* ComputeShaderPtr;

}