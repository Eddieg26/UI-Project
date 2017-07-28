#pragma once
#include "../Core/RefCounted.h"

#include "Common.h"
#include "BufferDescription.h"

namespace Pyro
{
    class RenderDevice;
    class RenderContext;

    class StructuredBuffer : public RefCounted {
        REFCOUNTED(StructuredBuffer);

    private:
        /// D3D buffer
        BufferPtr buffer;
        /// D3D device context
        DeviceContextPtr deviceContext;
        /// Buffer description
        BufferDescription bufferDescription;

    public:
        /// Construct
        StructuredBuffer();
        /// Destruct
        ~StructuredBuffer();

        /// Create buffer and return result
        Result Create(RenderDevice& renderDevice, const BufferDescription& desc);
        /// Release buffer
        void Release();

        /// Set the data in the buffer
        template <typename T> void SetData(const T* data, uint count);

    private:
        /// Map the GPU buffer into CPU memory
        void* Map();
        /// Unmap the GPU buffer
        void UnMap();
    };

    template <typename T> void StructuredBuffer::SetData(const T* data, uint count) {
        if (!data || !count || !buffer)
            return;

        void* hwData = Map();
        if (hwData) {
            memcpy(hwData, data, size * count);
            UnMap();
        }
    }
}