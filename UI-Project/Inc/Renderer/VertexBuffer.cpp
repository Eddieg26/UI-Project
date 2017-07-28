#include "VertexBuffer.h"
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Pyro
{
    D3D11_BUFFER_DESC translateVertexBufferDesc(const BufferDescription& desc) {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));
        bufferDesc.Usage = desc.dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = desc.byteWidth;
        bufferDesc.BindFlags = desc.bindFlags;
        bufferDesc.CPUAccessFlags = desc.cpuAccessFlags;
        bufferDesc.MiscFlags = desc.miscFlags;
        bufferDesc.StructureByteStride = desc.structuredByteStride;
        return bufferDesc;
    }

    VertexBuffer::VertexBuffer() :
        buffer(nullptr),
        deviceContext(nullptr) {}

    VertexBuffer::~VertexBuffer() {
        Release();
    }

    Result VertexBuffer::Create(RenderDevice& renderDevice, const BufferDescription& desc) {
        Release();

        D3D11_BUFFER_DESC bufferDesc = translateVertexBufferDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer);

        bufferDescription = desc;
        deviceContext = renderDevice.GetRenderContext()->GetContext();
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void VertexBuffer::Release() {
        SAFERELEASE(buffer);
    }

    void* VertexBuffer::Map(uint start) {
        void* hwData = nullptr;

        if (buffer) {
            D3D11_MAPPED_SUBRESOURCE subResource;
            ZeroMemory(&subResource, sizeof(subResource));

            deviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

            hwData = subResource.pData;
        }

        return hwData;
    }

    void VertexBuffer::UnMap() {
        deviceContext->Unmap(buffer, 0);
    }
}