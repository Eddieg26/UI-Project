#include "RenderContext.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "SamplerState.h"

namespace Pyro
{
    RenderContext::RenderContext() : context(nullptr) {}

    RenderContext::~RenderContext() {
        SAFERELEASE(context);
    }

    BlendState* RenderContext::GetBlendState(const String& name) const {
        uint hash = name.ToHash();
        BlendState* blendState = blendStates[hash];
        return blendState;
    }

    DepthStencilState* RenderContext::GetDepthSteniclState(const String& name) const {
        uint hash = name.ToHash();
        DepthStencilState* depthStencilState = depthStencilStates[hash];
        return depthStencilState;
    }

    RasterizerState* RenderContext::GetRasterizerState(const String& name) const {
        uint hash = name.ToHash();
        RasterizerState* rasterizerState = rasterizerStates[hash];
        return rasterizerState;
    }

    SamplerState* RenderContext::GetSamplerState(const String& name) const {
        uint hash = name.ToHash();
        SamplerState* samplerState = samplerStates[hash];
        return samplerState;
    }
}