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
}