#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "BufferDescription.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class ConstantBuffer : public RefCounted {
        REFCOUNTED(ConstantBuffer);

    private:
        /// D3D buffer
        BufferPtr buffer;
        /// D3D device context
        DeviceContextPtr deviceContext;
        /// Buffer description
        BufferDescription bufferDescription;

    public:
        /// Construct
        ConstantBuffer();
        /// Destruct
        ~ConstantBuffer();

        /// Create buffer and return result
        Result Create(RenderDevice& renderDevice, const BufferDescription& desc);
        /// Release buffer
        void Release();

        /// Set all the data in the buffer
        template <typename T> void SetData(const T* data);

        /// Return buffer
        BufferPtr GetBuffer() const { return buffer; }

    private:
        /// Map the GPU buffer into CPU memory
        void* Map();
        /// Unmap the GPU buffer
        void UnMap();
    };

    template <typename T> void ConstantBuffer::SetData(const T* data) {
        if (!data || !buffer)
            return;

        void* hwData = Map();
        if (hwData) {
            memcpy(hwData, data, size);
            UnMap();
        }
    }

}