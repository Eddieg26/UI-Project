#pragma once

namespace Pyro
{
    enum class Result {
        Success,
        Failed
    };

    enum class TopologyType {
        Undefined,
        TriangleList,
        LineList,
        PointList,
        TriangleStrip,
        LineStrip,
        TriangleFan,
    };

    enum class FillMode {
        Solid,
        WireFrame
    };

    enum class CullMode {
        None,
        Front,
        Back
    };

    /// Texture unit. Each unit corresponds to a slot in the pixel shader
    enum class TextureUnit {
        Diffuse = 0,
        Normal = 1,
        Specular = 2,
        Emissive = 3,
        Max
    };

    enum class TextureWrapMode {
        Wrap = 0,
        Mirror,
        Clamp,
        Border,
        MirrorOnce
    };

    enum class TextureFilterMode {
        Default,
        Nearest,
        Bilinear,
        Trilinear,
        Anisotropic
    };

    enum class BlendMode {
        None = 0,
        Additive = 1,
        AdditiveSoft = 2,
        Alpha = 3,
        Premulalpha = 4,
        Multiply = 5,
        MultiplyDouble = 6,
        AdditiveMultiply = 7,
        Depth = 8,
    };

    enum class RasterizerType {
        Opaque,
        Transparent,
        Wireframe,
        Skybox
    };

    enum class DepthStencilType {
        Object,
        Skybox,
        Depthless,
        Depthlessequal
    };

    enum class BlendFactor {
        DestColor,
        SourceColor,
        Zero,
        One,
        OneMinusDestColor,
        OneMinusSrcColor,
        SourceAlpha,
        DestAlpha,
        OneMinusSrcAlpha,

        UnknownBlendFactor,
    };

    enum class BlendOp {
        Add,
        Subtract,
        RevSubtract,
        Min,
        Max
    };

    enum class ColorWriteMask {
        Red = 1,
        Green = 2,
        Blue = 4,
        Alpha = 8,
        All = ((unsigned)ColorWriteMask::Red | (unsigned)ColorWriteMask::Green
        | (unsigned)ColorWriteMask::Blue | (unsigned)ColorWriteMask::Alpha)
    };

    enum class StencilOp {
        Keep,
        Zero,
        Replace,
        IncrSat,
        DecrSat,
        Invert,
        Incr,
        Decr
    };

    enum class CompareFunc {
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
    };

    enum class BufferType {
        Vertex,
        Index,
        Constant,
        Structured,

        Unknown
    };

    enum class DSVDimension {
        Unknown,
        Texture1D,
        Texture1DArray,
        Texture2D,
        Texture2DArray,
        Texture2DMS,
        Texture2DMSArray
    };

    enum class RTVDimension {
        Unknown,
        Buffer,
        Texture1D,
        Texture1DArray,
        Texture2D,
        Texture2DArray,
        Texture2DMS,
        Texture2DMSArray,
        Texture3D
    };

    enum class UAVDimension {
        Unknown,
        Buffer,
        Texture1D,
        Texture1DArray,
        Texture2D,
        Texture2DArray,
        Texture3D
    };

    enum class SRVDimension {
        Unknown,
        Buffer,
        Texture1D,
        Texture1DArray,
        Texture2D,
        Texture2DArray,
        Texture2DMS,
        Texture2DMSArray,
        Texture3D,
        TextureCube,
        TextureCubeArray,
        BufferEx
    };
}