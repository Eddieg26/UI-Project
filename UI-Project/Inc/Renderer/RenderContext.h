#pragma once
#include "../Core/Object.h"
#include "../Containers/Str.h"
#include "../Containers/HashMap.h"

#include "Common.h"
#include "Enums.h"

namespace Pyro
{
	class RenderDevice;
    class BlendState;
    class DepthStencilState;
    class RasterizerState;
    class SamplerState;
    class InputLayout;

	class RenderContext : public RefCounted {
		REFCOUNTED(RenderContext);

		friend class RenderDevice;

	private:
        /// D3D device context
        DeviceContextPtr context;
		HashMap<uint, SharedPtr<BlendState>> blendStates;
		HashMap<uint, SharedPtr<DepthStencilState>> depthStencilStates;
		HashMap<uint, SharedPtr<RasterizerState>> rasterizerStates;
		HashMap<uint, SharedPtr<SamplerState>> samplerStates;
        HashMap<uint, SharedPtr<InputLayout>> inputLayouts;

	public:
		/// Construct
		RenderContext();
		/// Destruct
		~RenderContext();

        /// Return D3D device context
        DeviceContextPtr GetContext() const { return context; }

        BlendState* GetBlendState(const String& name);
        DepthStencilState* GetDepthSteniclState(const String& name);
        RasterizerState* GetRasterizerState(const String& name);
        SamplerState* GetSamplerState(const String& name);
        InputLayout* GetInputLayout(const String& name);
	};
}