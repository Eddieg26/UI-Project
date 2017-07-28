#pragma once
#include "../Core/RefCounted.h"
#include "../Containers/Str.h"
#include "../Containers/HashMap.h"
#include "../Containers/Ptr.h"

#include "Common.h"
#include "Enums.h"

namespace Pyro
{
    class Context;
    class ConstantBuffer;
    class RenderDevice;
    class RenderContext;

    struct BufferBinding {
        String bufferName;
        uint slot;
        SharedPtr<ConstantBuffer> constantBuffer;

        BufferBinding() : slot(0), constantBuffer(nullptr) {}

        BufferBinding(String name, uint bufferSlot, ConstantBuffer* buffer) :
            bufferName(name),
            slot(bufferSlot),
            constantBuffer(buffer) {}
    };

    class Shader : public RefCounted {
        REFCOUNTED(Shader);

    private:
        /// Cached shader
        BlobPtr cachedShader;
        /// D3D11 Device
        DevicePtr device;
        /// Map of constant buffer
        HashMap<uint, BufferBinding> constantBuffers;
        /// Type of shader
        ShaderType type;
        union
        {
            VertexShaderPtr vertexShader;
            PixelShaderPtr pixelShader;
            GeometryShaderPtr geometryShader;
            ComputeShaderPtr computeShader;
        };

    public:
        /// Construct
        Shader();
        /// Destruct
        ~Shader();

        /// Load the shader
        Result LoadShader(RenderDevice& renderDevice, const String& shaderPath, ShaderType shaderType);

        /// Return chached shader
        BlobPtr GetChachedShader() const { return cachedShader; }
        /// Return shader type
        ShaderType GetType() const { return type; }
        /// Return constant buffer by name
        ConstantBuffer* GetConstantBuffer(const String& name);

        /// Release shader
        void Release();

        VertexShaderPtr GetVertexShader() const { return vertexShader; }
        PixelShaderPtr GetPixelShader() const { return pixelShader; }
        GeometryShaderPtr GetGeometryShader() const { return geometryShader; }
        ComputeShaderPtr GetComputeShader() const { return computeShader; }

    private:
        /// Reflect shader and reflect constant buffers
        void ReflectShader();
    };
}