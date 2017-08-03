#include "Graphics.h"
#include "RenderContext.h"
#include "RenderDevice.h"
#include "RenderTargetView.h"
#include "Viewport.h"

namespace Pyro
{
    Graphics::Graphics(Context* context) : Object(context),
        renderContext(nullptr),
        renderDevice(nullptr),
        swapChain(nullptr) {}

    Graphics::~Graphics() {
        SAFERELEASE(swapChain);
    }

    Result Graphics::Initialize() {
        renderContext = new RenderContext();
        renderDevice = new RenderDevice();
        if (renderDevice->CreateDevice(renderContext) == Result::Failed || CreateSwapChain() == Result::Failed)
            return Result::Failed;

        return Result::Success;
    }

    void Graphics::Draw(uint startVertex, uint vertexCount) const {
        renderContext->GetContext()->Draw(vertexCount, startVertex);
    }

    void Graphics::DrawIndexed(uint startIndex, uint indexCount, uint startVertex) const {
        renderContext->GetContext()->DrawIndexed(indexCount, startIndex, startVertex);
    }

    void Graphics::Dispatch(uint threadCountX, uint threadCountY, uint threadCountZ) const {
        renderContext->GetContext()->Dispatch(threadCountX, threadCountY, threadCountZ);
    }

    void Graphics::Update() {

    }

    void Graphics::Render() {
        swapChain->Present(renderSettings.vsync, 0);
    }

    Result Graphics::CreateSwapChain() {
        return Result::Failed;
    }

}