#include "Buffer.h"
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Pyro
{
    D3D11_BUFFER_DESC translateBufferDesc(const BufferDescription& desc) {
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

    Buffer::Buffer() :
        buffer(nullptr),
        deviceContext(nullptr) {}

    Buffer::~Buffer() {
        Release();
    }

    Result Buffer::Create(RenderDevice& renderDevice, const BufferDescription& desc) {
        if (!(desc.bindFlags & (uint)D3D11_BIND_VERTEX_BUFFER))
            return Result::Failed;

        D3D11_BUFFER_DESC bufferDesc = translateBufferDesc(desc);
        HRESULT result = renderDevice.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer);

        bufferDescription = desc;
        return SUCCEEDED(result) ? Result::Success : Result::Failed;
    }

    void Buffer::Bind(RenderContext& renderContext, uint slot, bool force) const {

    }

    void Buffer::Release() {
        SAFERELEASE(buffer);
    }

    void* Buffer::Map(uint start) {
        void* hwData = nullptr;

        if (buffer) {
            D3D11_MAPPED_SUBRESOURCE subResource;
            ZeroMemory(&subResource, sizeof(subResource));

            deviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

            hwData = subResource.pData;
        }

        return hwData;
    }

    void Buffer::UnMap() {
        deviceContext->Unmap(buffer, 0);
    }

}