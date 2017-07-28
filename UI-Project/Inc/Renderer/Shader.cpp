#include "Shader.h"
#include "ConstantBuffer.h"
#include "RenderDevice.h"
#include "RenderContext.h"
#include "../IO/File.h"
#include "../Core/Context.h"

#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

namespace Pyro
{
    Shader::Shader() :
        cachedShader(nullptr),
        type(ShaderType::Vertex),
        vertexShader(nullptr) {}

    Shader::~Shader() {
        Release();
    }

    Result Shader::LoadShader(RenderDevice& renderDevice, const String& shaderPath, ShaderType shaderType) {
        SharedPtr<File> file(new File(nullptr, shaderPath));
        if (!file->IsOpen())
            return Result::Failed;

        uint fileSize = file->GetSize();
        if (FAILED(D3DCreateBlob(fileSize, &cachedShader)))
            return Result::Failed;

        SharedArrayPtr<char> shaderData(new char[fileSize]);
        file->Read(shaderData, fileSize);

        memcpy(cachedShader->GetBufferPointer(), shaderData, fileSize);

        DevicePtr device = renderDevice.GetDevice();

        HRESULT result;
        switch (type)
        {
        case Pyro::ShaderType::Vertex:
            result = device->CreateVertexShader(cachedShader->GetBufferPointer(), fileSize, nullptr, &vertexShader);
            break;
        case Pyro::ShaderType::Pixel:
            result = device->CreatePixelShader(cachedShader->GetBufferPointer(), fileSize, nullptr, &pixelShader);
            break;
        case Pyro::ShaderType::Geometry:
            result = device->CreateGeometryShader(cachedShader->GetBufferPointer(), fileSize, nullptr, &geometryShader);
            break;
        case Pyro::ShaderType::Compute:
            result = device->CreateComputeShader(cachedShader->GetBufferPointer(), fileSize, nullptr, &computeShader);
            break;
        }

        type = shaderType;
        
        if (FAILED(result))
            return Result::Failed;

        return Result::Success;
    }

    ConstantBuffer* Shader::GetConstantBuffer(const String& name) {
        uint hash = name.ToHash();
        return constantBuffers[hash].constantBuffer;
    }

    void Shader::ReflectShader() {
        ID3D11ShaderReflection* reflector = nullptr;
        HRESULT hr = D3DReflect(cachedShader->GetBufferPointer(), cachedShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflector);
        if (SUCCEEDED(hr)) {
            D3D11_SHADER_DESC shaderDesc;
            reflector->GetDesc(&shaderDesc);

            for (unsigned int i = 0; i < shaderDesc.ConstantBuffers; ++i) {
                D3D11_SHADER_BUFFER_DESC constantBufferDesc;
                ID3D11ShaderReflectionConstantBuffer* reflectedConstantBuffer = reflector->GetConstantBufferByIndex(i);
                reflectedConstantBuffer->GetDesc(&constantBufferDesc);
                String constantBufferName(constantBufferDesc.Name);
                uint hash = constantBufferName.ToHash();
                SharedPtr<ConstantBuffer> buffer(new ConstantBuffer);
                BufferDescription bufferDesc;
                bufferDesc.byteWidth = constantBufferDesc.Size;
                BufferBinding binding(constantBufferName, i, buffer);
                constantBuffers.Add(hash, BufferBinding(constantBufferName, i, buffer));
            }

            SAFERELEASE(reflector);
        }
    }

    void Shader::Release() {
        switch (type)
        {
        case Pyro::ShaderType::Vertex:
            SAFERELEASE(vertexShader);
            break;
        case Pyro::ShaderType::Pixel:
            SAFERELEASE(pixelShader);
            break;
        case Pyro::ShaderType::Geometry:
            SAFERELEASE(geometryShader);
            break;
        case Pyro::ShaderType::Compute:
            SAFERELEASE(computeShader);
            break;
        }
    }
}