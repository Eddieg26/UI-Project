#pragma once

#include <d3d11.h>

namespace Pyro
{
#define SAFERELEASE(ptr) if(ptr){ptr->Release(); ptr = nullptr;}
#define SAFEDELETE(ptr) if(ptr){delete ptr; ptr = nullptr;}
#define SAFEDELETEARRAY(ptr) if(ptr){delete[] ptr; ptr = nullptr;} 

    typedef IDXGISwapChain* SwapChainPtr;
    typedef ID3D11Device* DevicePtr;
    typedef ID3D11DeviceContext* DeviceContextPtr;

    typedef ID3D11BlendState* BlendStatePtr;
    typedef ID3D11RasterizerState* RasterizerStatePtr;
	typedef ID3D11DepthStencilState* DepthStencilStatePtr;
}