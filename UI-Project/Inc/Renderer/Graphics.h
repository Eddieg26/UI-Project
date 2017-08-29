#pragma once

#include "../Core/Object.h"

#include "Common.h"
#include "Enums.h"
#include "RenderSettings.h"

namespace Pyro
{
    class RenderContext;
    class RenderDevice;
    class RenderTargetView;
    class Viewport;

    class Graphics : public Object {
        PYRO_OBJECT(Graphics, Object);

    private:
        /// Render context
        SharedPtr<RenderContext> renderContext;
        /// Render device
        SharedPtr<RenderDevice> renderDevice;
        /// D3D swap chain
        SwapChainPtr swapChain;
        /// Render target view
        SharedPtr<RenderTargetView> renderTargetView;
        /// Viewport
        SharedPtr<Viewport> viewport;
        /// Render settings
        RenderSettings renderSettings;

    public:
        /// Construct
        Graphics(Context* context);
        /// Destruct
        ~Graphics();

        /// Initialize the graphics engine. Create render context and render device
        Result Initialize();
        /// Update render pipeline
        void Update();
        /// Render geometry
        void Render();

        /// Draw geometry
        void Draw(uint startVertex, uint vertexCount) const;
        /// Draw indexed geometry
        void DrawIndexed(uint startIndex, uint indexCount, uint startVertex) const;
        /// Executes a command list from a thread group
        void Dispatch(uint threadCountX, uint threadCountY, uint threadCountZ) const;

        /// Return render context
        RenderContext* GetRenderContext() const { return renderContext; }
        /// Return render device
        RenderDevice* GetRenderDevice() const { return renderDevice; }
        /// Return swapchain
        SwapChainPtr GetSwaphChain() const { return swapChain; }
        /// Return render settings
        RenderSettings& GetRenderSettings() { return renderSettings; }
        /// Return render settings
        const RenderSettings& GetRenderSettings() const { return renderSettings; }

    private:
        Result CreateSwapChain();
    };
}