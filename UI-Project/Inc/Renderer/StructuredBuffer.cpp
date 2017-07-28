#include "StructuredBuffer.h"
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Pyro
{
    D3D11_BUFFER_DESC translateStructuredBufferDesc(const BufferDescription& desc) {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));
        bufferDesc.Usage = desc.dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = desc.byteWidth;
        bufferDesc.BindFlags = desc.bindFlags;
        bufferDesc.CPUAccessFlags = desc.cpuAccessFlags;
        bufferDesc.StructureByteStride = desc.structuredByteStride;
        bufferDesc.MiscFlags = desc.miscFlags;

        return bufferDesc;
    }

    StructuredBuffer::StructuredBuffer() :
        buffer(nullptr),
        deviceContext(nullptr) {}

    StructuredBuffer::~StructuredBuffer() {
        Release();
    }

    Result StructuredBuffer::Create(RenderDevice& renderDevice, const BufferDescription& desc) {
        Release();

        D3D11_BUFFER_DESC bufferDesc = translateStructuredBufferDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer);

        bufferDescription = desc;
        deviceContext = renderDevice.GetRenderContext()->GetContext();
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void StructuredBuffer::Release() {
        SAFERELEASE(buffer);
    }

    void* StructuredBuffer::Map() {
        void* hwData = nullptr;

        if (buffer) {
            D3D11_MAPPED_SUBRESOURCE subResource;
            ZeroMemory(&subResource, sizeof(subResource));

            deviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

            hwData = subResource.pData;
        }

        return hwData;
    }

    void StructuredBuffer::UnMap() {
        deviceContext->Unmap(buffer, 0);
    }


}