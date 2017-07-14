#include "Translate.h"

#include <d3d11.h>

namespace Pyro
{
	D3D11_CULL_MODE TranslateDX11::toD3DCullMode(CullMode mode) {
		switch (mode)
		{
		case CullMode::Back:
			return D3D11_CULL_MODE::D3D11_CULL_BACK;
			break;

		case CullMode::Front:
			return D3D11_CULL_MODE::D3D11_CULL_FRONT;
			break;

		case CullMode::None:
			return D3D11_CULL_MODE::D3D11_CULL_NONE;
			break;
		}

		return D3D11_CULL_MODE::D3D11_CULL_NONE;
	}

	D3D11_FILL_MODE TranslateDX11::toD3DFillMode(FillMode mode) {
		switch (mode)
		{
		case FillMode::Solid:
			return D3D11_FILL_MODE::D3D11_FILL_SOLID;
			break;

		case FillMode::WireFrame:
			return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
			break;
		}

		return D3D11_FILL_MODE::D3D11_FILL_SOLID;
	}

	D3D11_FILTER TranslateDX11::toD3DFilter(TextureFilterMode filter) {
		switch (filter)
		{
		case Pyro::TextureFilterMode::Default:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case Pyro::TextureFilterMode::Nearest:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case Pyro::TextureFilterMode::Bilinear:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case Pyro::TextureFilterMode::Trilinear:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			break;
		case Pyro::TextureFilterMode::Anisotropic:
			return D3D11_FILTER_ANISOTROPIC;
			break;
		}

		return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	}

	D3D11_BLEND TranslateDX11::toD3DBlend(BlendFactor factor) {
		switch (factor)
		{
		case Pyro::BlendFactor::DestColor:
			return D3D11_BLEND_DEST_COLOR;
			break;
		case Pyro::BlendFactor::SourceColor:
			return D3D11_BLEND_SRC_COLOR;
			break;
		case Pyro::BlendFactor::Zero:
			return D3D11_BLEND_ZERO;
			break;
		case Pyro::BlendFactor::One:
			return D3D11_BLEND_ONE;
			break;
		case Pyro::BlendFactor::OneMinusDestColor:
			return D3D11_BLEND_INV_DEST_COLOR;
			break;
		case Pyro::BlendFactor::OneMinusSrcColor:
			return D3D11_BLEND_INV_SRC_COLOR;
			break;
		case Pyro::BlendFactor::SourceAlpha:
			return D3D11_BLEND_SRC_ALPHA;
			break;
		case Pyro::BlendFactor::DestAlpha:
			return D3D11_BLEND_DEST_ALPHA;
			break;
		case Pyro::BlendFactor::OneMinusSrcAlpha:
			return D3D11_BLEND_INV_SRC_ALPHA;
			break;
		case Pyro::BlendFactor::UnknownBlendFactor:
			return D3D11_BLEND_ZERO;
			break;
		}

		return D3D11_BLEND_ZERO;
	}
	D3D11_BLEND_OP TranslateDX11::toD3DBlendOp(BlendOp blendOp) {
		switch (blendOp) {
		case Pyro::BlendOp::Add:
			return D3D11_BLEND_OP_ADD;
			break;
		case Pyro::BlendOp::Subtract:
			return D3D11_BLEND_OP_SUBTRACT;
			break;
		case Pyro::BlendOp::RevSubtract:
			return D3D11_BLEND_OP_SUBTRACT;
			break;
		case Pyro::BlendOp::Min:
			return D3D11_BLEND_OP_MIN;
			break;
		case Pyro::BlendOp::Max:
			return D3D11_BLEND_OP_MAX;
			break;
		}

		return D3D11_BLEND_OP_ADD;
	}

	D3D11_STENCIL_OP TranslateDX11::toD3DStencilOP(StencilOp stencilOp) {
		switch (stencilOp) {
		case Pyro::StencilOp::Keep:
			return D3D11_STENCIL_OP_KEEP;
			break;
		case Pyro::StencilOp::Zero:
			return D3D11_STENCIL_OP_ZERO;
			break;
		case Pyro::StencilOp::Replace:
			return D3D11_STENCIL_OP_REPLACE;
			break;
		case Pyro::StencilOp::IncrSat:
			return D3D11_STENCIL_OP_INCR_SAT;
			break;
		case Pyro::StencilOp::DecrSat:
			return D3D11_STENCIL_OP_DECR_SAT;
			break;
		case Pyro::StencilOp::Invert:
			return D3D11_STENCIL_OP_INVERT;
			break;
		case Pyro::StencilOp::Incr:
			return D3D11_STENCIL_OP_INCR;
			break;
		case Pyro::StencilOp::Decr:
			return D3D11_STENCIL_OP_DECR;
			break;
		}
		
		return D3D11_STENCIL_OP_KEEP;
	}
	D3D11_COMPARISON_FUNC TranslateDX11::toD3DComparisonFunc(CompareFunc compareFunc) {
		switch (compareFunc) {
		case Pyro::CompareFunc::Never:
			return D3D11_COMPARISON_NEVER;
			break;
		case Pyro::CompareFunc::Less:
			return D3D11_COMPARISON_LESS;
			break;
		case Pyro::CompareFunc::Equal:
			return D3D11_COMPARISON_EQUAL;
			break;
		case Pyro::CompareFunc::LessEqual:
			return D3D11_COMPARISON_LESS_EQUAL;
			break;
		case Pyro::CompareFunc::Greater:
			return D3D11_COMPARISON_GREATER;
			break;
		case Pyro::CompareFunc::NotEqual:
			return D3D11_COMPARISON_NOT_EQUAL;
			break;
		case Pyro::CompareFunc::GreaterEqual:
			return D3D11_COMPARISON_GREATER_EQUAL;
			break;
		case Pyro::CompareFunc::Always:
			return D3D11_COMPARISON_ALWAYS;
			break;
		}

		return D3D11_COMPARISON_NEVER;
	}
	D3D11_UAV_DIMENSION TranslateDX11::toD3DUAVDimension(UAVDimension dimension){
		switch (dimension) {
		case Pyro::UAVDimension::Unknown:
			return D3D11_UAV_DIMENSION_UNKNOWN;
			break;
		case Pyro::UAVDimension::Buffer:
			return D3D11_UAV_DIMENSION_BUFFER;
			break;
		case Pyro::UAVDimension::Texture1D:
			return D3D11_UAV_DIMENSION_TEXTURE1D;
			break;
		case Pyro::UAVDimension::Texture1DArray:
			return D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
			break;
		case Pyro::UAVDimension::Texture2D:
			return D3D11_UAV_DIMENSION_TEXTURE2D;
			break;
		case Pyro::UAVDimension::Texture2DArray:
			return D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
			break;
		case Pyro::UAVDimension::Texture3D:
			return D3D11_UAV_DIMENSION_TEXTURE3D;
			break;
		}

		return D3D11_UAV_DIMENSION_UNKNOWN;
	}
	D3D11_DSV_DIMENSION TranslateDX11::toD3DDSVDimension(DSVDimension dimension) {
		switch (dimension) {
		case Pyro::DSVDimension::Unknown:
			return D3D11_DSV_DIMENSION_UNKNOWN;
			break;
		case Pyro::DSVDimension::Texture1D:
			return D3D11_DSV_DIMENSION_TEXTURE1D;
			break;
		case Pyro::DSVDimension::Texture1DArray:
			return D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
			break;
		case Pyro::DSVDimension::Texture2D:
			return D3D11_DSV_DIMENSION_TEXTURE2D;
			break;
		case Pyro::DSVDimension::Texture2DArray:
			return D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			break;
		case Pyro::DSVDimension::Texture2DMS:
			return D3D11_DSV_DIMENSION_TEXTURE2DMS;
			break;
		case Pyro::DSVDimension::Texture2DMSArray:
			return D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
			break;
		}

		return D3D11_DSV_DIMENSION_UNKNOWN;
	}
	D3D11_RTV_DIMENSION TranslateDX11::toD3DRTVDimension(RTVDimension dimension){
		switch (dimension) {
		case Pyro::RTVDimension::Unknown:
			return D3D11_RTV_DIMENSION_UNKNOWN;
			break;
		case Pyro::RTVDimension::Buffer:
			return D3D11_RTV_DIMENSION_BUFFER;
			break;
		case Pyro::RTVDimension::Texture1D:
			return D3D11_RTV_DIMENSION_TEXTURE1D;
			break;
		case Pyro::RTVDimension::Texture1DArray:
			return D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
			break;
		case Pyro::RTVDimension::Texture2D:
			return D3D11_RTV_DIMENSION_TEXTURE2D;
			break;
		case Pyro::RTVDimension::Texture2DArray:
			return D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			break;
		case Pyro::RTVDimension::Texture2DMS:
			return D3D11_RTV_DIMENSION_TEXTURE2DMS;
			break;
		case Pyro::RTVDimension::Texture2DMSArray:
			return D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
			break;
		case Pyro::RTVDimension::Texture3D:
			return D3D11_RTV_DIMENSION_TEXTURE3D;
			break;
		}

		return D3D11_RTV_DIMENSION_UNKNOWN;
	}
	D3D_SRV_DIMENSION TranslateDX11::toD3DSRVDimension(SRVDimension dimension){
		switch (dimension) {
		case Pyro::SRVDimension::Unknown:
			return D3D11_SRV_DIMENSION_UNKNOWN;
			break;
		case Pyro::SRVDimension::Buffer:
			return D3D11_SRV_DIMENSION_BUFFER;
			break;
		case Pyro::SRVDimension::Texture1D:
			return D3D11_SRV_DIMENSION_TEXTURE1D;
			break;
		case Pyro::SRVDimension::Texture1DArray:
			return D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
			break;
		case Pyro::SRVDimension::Texture2D:
			return D3D11_SRV_DIMENSION_TEXTURE2D;
			break;
		case Pyro::SRVDimension::Texture2DArray:
			return D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			break;
		case Pyro::SRVDimension::Texture2DMS:
			return D3D11_SRV_DIMENSION_TEXTURE2DMS;
			break;
		case Pyro::SRVDimension::Texture2DMSArray:
			return D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			break;
		case Pyro::SRVDimension::Texture3D:
			return D3D11_SRV_DIMENSION_TEXTURE3D;
			break;
		case Pyro::SRVDimension::TextureCube:
			return D3D11_SRV_DIMENSION_TEXTURECUBE;
			break;
		case Pyro::SRVDimension::TextureCubeArray:
			return D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
			break;
		case Pyro::SRVDimension::BufferEx:
			return D3D11_SRV_DIMENSION_BUFFEREX;
			break;
		}

		return D3D11_SRV_DIMENSION_UNKNOWN;
	}
}