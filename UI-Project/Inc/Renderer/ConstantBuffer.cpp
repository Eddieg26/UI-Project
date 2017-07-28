#include "ConstantBuffer.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "PipelineState.h"

namespace Pyro
{
    ConstantBuffer::ConstantBuffer() :
        buffer(nullptr),
        deviceContext(nullptr) {}

    ConstantBuffer::~ConstantBuffer() {
        Release();
    }

    Result ConstantBuffer::Create(RenderDevice& renderDevice, const BufferDescription& desc) {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bufferDesc.ByteWidth = desc.byteWidth;

        HRESULT result = renderDevice.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer);

        bufferDescription = desc;
        deviceContext = renderDevice.GetRenderContext()->GetContext();
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void ConstantBuffer::Release() {
        SAFERELEASE(buffer);
    }

    void* ConstantBuffer::Map() {
        void *hwData = nullptr;

        if (buffer) {
            D3D11_MAPPED_SUBRESOURCE subResource;
            ZeroMemory(&subResource, sizeof(subResource));

            HRESULT hr = deviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

            hwData = subResource.pData;
        }

        return hwData;
    }

    void ConstantBuffer::UnMap() {
        deviceContext->Unmap(buffer, 0);
    }
}