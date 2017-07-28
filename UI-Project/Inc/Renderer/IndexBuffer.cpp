#include "IndexBuffer.h"
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Pyro
{
    D3D11_BUFFER_DESC translateIndexBufferDesc(const BufferDescription& desc) {
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

    IndexBuffer::IndexBuffer() :
        buffer(nullptr),
        deviceContext(nullptr) {}

    IndexBuffer::~IndexBuffer() {
        Release();
    }

    Result IndexBuffer::Create(RenderDevice& renderDevice, const BufferDescription& desc) {
        D3D11_BUFFER_DESC bufferDesc = translateIndexBufferDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer);

        bufferDescription = desc;
        deviceContext = renderDevice.GetRenderContext()->GetContext();
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void IndexBuffer::Release() {
        SAFERELEASE(buffer);
    }

    void* IndexBuffer::Map(uint start) {
        void* hwData = nullptr;

        if (buffer) {
            D3D11_MAPPED_SUBRESOURCE subResource;
            ZeroMemory(&subResource, sizeof(subResource));

            deviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

            hwData = subResource.pData;
        }

        return hwData;
    }

    void IndexBuffer::UnMap() {
        deviceContext->Unmap(buffer, 0);
    }
}