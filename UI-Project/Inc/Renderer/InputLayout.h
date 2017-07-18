#pragma once
#include "../Core/RefCounted.h"

#include "Enums.h"
#include "Common.h"
#include "InputLayoutDescription.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class InputLayout : public RefCounted {
        REFCOUNTED(InputLayout);

    private:
        /// D3D Input layout
        InputLayoutPtr inputLayout;
        /// Input layout description
        InputLayoutDescription inputLayoutDescription;

    public:
        /// Construct
        InputLayout();
        /// Destruct
        ~InputLayout();

        /// Create input layout and add it to render context if successfully created
        Result Create(RenderDevice& renderDevice, const InputLayoutDescription& desc);
        /// Bind input layout to the pipeline
        void Bind(RenderContext& renderContext, bool force = false) const;
        /// Release input layout
        void Release();

        /// Return D3D input layout
        InputLayoutPtr GetInputLayout() const { return inputLayout; }
        /// Return input layout description
        InputLayoutDescription GetInputLayoutDesc() const { return inputLayoutDescription; }
    };
}