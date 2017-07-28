#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "BufferDescription.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class VertexBuffer : public RefCounted {
        REFCOUNTED(VertexBuffer);

    private:
        /// D3D buffer
        BufferPtr buffer;
        /// D3D device context
        DeviceContextPtr deviceContext;
        /// Buffer description
        BufferDescription bufferDescription;

    public:
        /// Construct
        VertexBuffer();
        /// Destruct
        ~VertexBuffer();

        /// Create buffer and return result
        Result Create(RenderDevice& renderDevice, const BufferDescription& desc);
        /// Release buffer
        void Release();

        /// Set all the data in the buffer
        template <typename T> void SetData(const T* data, uint count);
        /// Sets a range of data in the buffer
        template <typename T> void SetDataRange(const T* data, uint start, uint count);

        /// Return D3D buffer
        BufferPtr GetBuffer() const { return buffer; }
        /// Return buffer description
        BufferDescription BufferDesc() const { return bufferDescription; }

    private:
        /// Map the GPU buffer into CPU memory
        void* Map(uint start = 0);
        /// Unmap the GPU buffer
        void UnMap();
    };

    template <typename T> void VertexBuffer::SetData(const T* data, uint count) {
        if (!data || !count)
            return;

        void* hwData = Map();
        if (hwData) {
            memcpy(hwData, data, sizeof(T) * count);
            UnMap();
        }
    }

    template <typename T> void VertexBuffer::SetDataRange(const T* data, uint start, uint count) {
        if (!data || !count || !count)
            return;

        void* hwData = Map(start);
        if (hwData) {
            memcpy(hwData, data, sizeof(T) * count);
            UnMap();
        }
    }
}