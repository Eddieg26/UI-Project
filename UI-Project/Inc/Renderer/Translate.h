#pragma once

#include "Enums.h"

enum D3D_PRIMITIVE_TOPOLOGY;
enum D3D11_CULL_MODE;
enum D3D11_FILL_MODE;
enum D3D11_FILTER;
enum D3D11_TEXTURE_ADDRESS_MODE;
enum D3D11_BLEND;
enum D3D11_BLEND_OP;
enum D3D11_STENCIL_OP;
enum D3D11_COMPARISON_FUNC;
enum D3D11_UAV_DIMENSION;
enum D3D11_DSV_DIMENSION;
enum D3D11_RTV_DIMENSION;
enum D3D_SRV_DIMENSION;

namespace Pyro
{
	class TranslateDX11 {

	private:
		TranslateDX11() = delete;
		TranslateDX11(const TranslateDX11&) = delete;
		TranslateDX11& operator==(const TranslateDX11&) = delete;

	public:
        static D3D_PRIMITIVE_TOPOLOGY toD3DTopology(TopologyType type);
		static D3D11_CULL_MODE toD3DCullMode(CullMode mode);
		static D3D11_FILL_MODE toD3DFillMode(FillMode mode);
		static D3D11_FILTER toD3DFilter(TextureFilterMode filter);
        static D3D11_TEXTURE_ADDRESS_MODE ToD3DWrapMode(TextureWrapMode mode);
		static D3D11_BLEND toD3DBlend(BlendFactor factor);
		static D3D11_BLEND_OP toD3DBlendOp(BlendOp blendOp);
		static D3D11_STENCIL_OP toD3DStencilOP(StencilOp stencilOp);
		static D3D11_COMPARISON_FUNC toD3DComparisonFunc(CompareFunc compareFunc);
		static D3D11_UAV_DIMENSION toD3DUAVDimension(UAVDimension dimension);
		static D3D11_DSV_DIMENSION toD3DDSVDimension(DSVDimension dimension);
		static D3D11_RTV_DIMENSION toD3DRTVDimension(RTVDimension dimension);
		static D3D_SRV_DIMENSION toD3DSRVDimension(SRVDimension dimension);
	};
}