#include "InputLayout.h"
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Pyro
{
    D3D11_INPUT_ELEMENT_DESC translateInputElementDesc(const InputElementDescription& desc) {
        D3D11_INPUT_ELEMENT_DESC inputDesc;
        ZeroMemory(&inputDesc, sizeof(inputDesc));
        inputDesc.SemanticName = desc.semanticName.CString();
        inputDesc.SemanticIndex = desc.semanticIndex;
        inputDesc.Format = desc.format;
        inputDesc.InputSlot = desc.inputSlot;
        inputDesc.AlignedByteOffset = desc.alignedByteOffset;
        inputDesc.InstanceDataStepRate = desc.instanceStepRate;
        inputDesc.InputSlotClass = desc.isVertexSlot ? D3D11_INPUT_PER_VERTEX_DATA : D3D11_INPUT_PER_INSTANCE_DATA;

        return inputDesc;
    }

    InputLayout::InputLayout() : inputLayout(nullptr) {}

    InputLayout::~InputLayout() {
        Release();
    }

    Result InputLayout::Create(RenderDevice& renderDevice, const InputLayoutDescription& desc) {
        Vector<D3D11_INPUT_ELEMENT_DESC> inputElements;
        for (uint i = 0; i < desc.inputElements.Size(); ++i) {
            inputElements.Add(translateInputElementDesc(desc.inputElements[i]));
        }

        HRESULT result = renderDevice.GetDevice()->CreateInputLayout(inputElements.Data(), inputElements.Size(), desc.shaderByteCode, desc.byteCodeLength, &inputLayout);

        inputLayoutDescription = desc;
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void InputLayout::Bind(RenderContext& renderContext, bool force) const {

    }

    void InputLayout::Release() {
        SAFERELEASE(inputLayout);
    }
}