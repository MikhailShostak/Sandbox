#pragma once

#include <BasicMath.hpp>
#include <RefCntAutoPtr.hpp>

#include <RenderDevice.h>
#include <DeviceContext.h>
#include <SwapChain.h>
#include <MapHelper.hpp>
#include <GraphicsUtilities.h>

namespace Graphics
{

struct ShaderHelperPrivateData
{
    Diligent::RefCntAutoPtr<Diligent::IBuffer> Handle;
};

struct DrawBatchPrivateData
{
    Diligent::RefCntAutoPtr<Diligent::IBuffer> Handle;
};

struct GraphicsContextPrivateData
{
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> Handle;
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> Device;

    Diligent::TEXTURE_FORMAT ColorBufferFormat = Diligent::TEX_FORMAT_RGBA8_UNORM;
    Diligent::TEXTURE_FORMAT DepthBufferFormat = Diligent::TEX_FORMAT_D32_FLOAT;
    
    Map<Graphics::Material *, Graphics::PipelineState> Pipelines;
};

struct MeshPrivateData
{
    Diligent::RefCntAutoPtr<Diligent::IBuffer> VBHandle;
    Diligent::RefCntAutoPtr<Diligent::IBuffer> IBHandle;
};

struct RenderBufferPrivateData
{
    size_t Size = 1;
    bool HasDepthBuffer = true;
    bool HasStencilBuffer = true;
    StaticArray<Diligent::ITextureView *, Diligent::MAX_RENDER_TARGETS> RenderTargets = {};
    Diligent::ITextureView* DepthStencilBuffer = nullptr;
};

struct ShaderPrivateData
{
    Diligent::RefCntAutoPtr<Diligent::IShader> Handle;
};

struct SwapChainPrivateData
{
    Diligent::RefCntAutoPtr<Diligent::ISwapChain> Handle;
};

struct TexturePrivateData
{
    Diligent::RefCntAutoPtr<Diligent::ITexture> Handle;
};

class PipelineStatePrivateData
{
public:
    Diligent::GraphicsPipelineStateCreateInfo PSOCreateInfo;
    Diligent::RefCntAutoPtr<Diligent::IPipelineState> Handle;
    Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> Binding;

    Graphics::Material *material = nullptr;
    const Graphics::RenderBuffer *renderBuffer = nullptr;

    void Setup()
    {
        //TODO: Implement blending settings
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = false;
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = Diligent::BLEND_FACTOR_ONE;
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOp = Diligent::BLEND_OPERATION_ADD;
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlendAlpha = Diligent::BLEND_FACTOR_ONE;
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlendAlpha = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
        PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOpAlpha = Diligent::BLEND_OPERATION_ADD;

        PSOCreateInfo.PSODesc.Name = "Graphics PSO";

        PSOCreateInfo.PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS;
        PSOCreateInfo.PSODesc.ResourceLayout.DefaultVariableType = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_STATIC;
        PSOCreateInfo.GraphicsPipeline.PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        PSOCreateInfo.GraphicsPipeline.RasterizerDesc.FillMode = material->Settings.Wireframe ? Diligent::FILL_MODE_WIREFRAME : Diligent::FILL_MODE_SOLID;
        PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = material->Settings.Cullback ? Diligent::CULL_MODE_BACK : Diligent::CULL_MODE_NONE;

        PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.StencilEnable = material->Settings.StencilEnabled;
        PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.StencilReadMask = material->Settings.StencilReadMask;
        PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.StencilWriteMask = material->Settings.StencilWriteMask;

        PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = material->Settings.DepthTestEnabled ? Diligent::True : Diligent::False;
        PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthWriteEnable = material->Settings.DepthWriteEnabled ? Diligent::True : Diligent::False;
        PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthFunc = Diligent::COMPARISON_FUNC_LESS;
        //TODO: Implement Graphics::DepthFunction enum
        /*PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthFunc = [&]() {
            switch (settings.DepthFunction)
            {
            case Graphics::DepthFunction::Never:
                return Diligent::COMPARISON_FUNC_NEVER;
            case Graphics::DepthFunction::Less:
                return Diligent::COMPARISON_FUNC_LESS;
            case Graphics::DepthFunction::Equal:
                return Diligent::COMPARISON_FUNC_EQUAL;
            case Graphics::DepthFunction::LessOrEqual:
                return Diligent::COMPARISON_FUNC_LESS_EQUAL;
            case Graphics::DepthFunction::Greater:
                return Diligent::COMPARISON_FUNC_GREATER;
            case Graphics::DepthFunction::NotEqual:
                return Diligent::COMPARISON_FUNC_NOT_EQUAL;
            case Graphics::DepthFunction::GreaterOrEqual:
                return Diligent::COMPARISON_FUNC_GREATER_EQUAL;
            case Graphics::DepthFunction::Always:
                return Diligent::COMPARISON_FUNC_ALWAYS;
            default:
                return Diligent::COMPARISON_FUNC_ALWAYS;
            }
        }();*/

        PSOCreateInfo.GraphicsPipeline.NumRenderTargets = material->RenderBuffer.Data->Size;
        for (size_t i = 0; i < material->RenderBuffer.Data->Size; ++i)
        {
            PSOCreateInfo.GraphicsPipeline.RTVFormats[i] = material->RenderBuffer.Data->RenderTargets[i]->GetDesc().Format;
        }

        if (material->RenderBuffer.Data->DepthStencilBuffer)
        {
            PSOCreateInfo.GraphicsPipeline.DSVFormat = material->RenderBuffer.Data->DepthStencilBuffer->GetDesc().Format;
        }
    }

    StaticArray<Diligent::LayoutElement, 8> Layout;

    void SetupInputLayout()
    {
        //TODO: Make it customizable. UV, Color layers, etc.
        Layout = {
            Diligent::LayoutElement{ 0, 0, 4, Diligent::VT_FLOAT32, Diligent::False }, //pos
            Diligent::LayoutElement{ 1, 0, 4, Diligent::VT_FLOAT32, Diligent::False }, //normal
            Diligent::LayoutElement{ 2, 0, 4, Diligent::VT_FLOAT32, Diligent::False }, //uv
            Diligent::LayoutElement{ 3, 0, 4, Diligent::VT_FLOAT32, Diligent::False }, //data

            //instance transform
            Diligent::LayoutElement{ 4, 1, 4, Diligent::VT_FLOAT32, Diligent::False, Diligent::INPUT_ELEMENT_FREQUENCY_PER_INSTANCE },
            Diligent::LayoutElement{ 5, 1, 4, Diligent::VT_FLOAT32, Diligent::False, Diligent::INPUT_ELEMENT_FREQUENCY_PER_INSTANCE },
            Diligent::LayoutElement{ 6, 1, 4, Diligent::VT_FLOAT32, Diligent::False, Diligent::INPUT_ELEMENT_FREQUENCY_PER_INSTANCE },
            Diligent::LayoutElement{ 7, 1, 4, Diligent::VT_FLOAT32, Diligent::False, Diligent::INPUT_ELEMENT_FREQUENCY_PER_INSTANCE },
        };

        PSOCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = Layout.data();
        PSOCreateInfo.GraphicsPipeline.InputLayout.NumElements = Layout.size();
    }

    Array<Diligent::ShaderResourceVariableDesc> Variables;
    Array<Diligent::ImmutableSamplerDesc> Samplers;

    void RegisterSampler(const Graphics::TextureSampler &sampler)
    {
        auto f = [&sampler]() {
            switch (sampler.Texture->Filtration)
            {
            case Graphics::TextureFiltration::Nearest:
                return Diligent::FILTER_TYPE_POINT;
            case Graphics::TextureFiltration::Bilinear:
                return Diligent::FILTER_TYPE_LINEAR;
            case Graphics::TextureFiltration::Trilinear:
                return Diligent::FILTER_TYPE_ANISOTROPIC;
            case Graphics::TextureFiltration::Anisotropic:
                return Diligent::FILTER_TYPE_ANISOTROPIC;
            };
            return Diligent::FILTER_TYPE_LINEAR;
        }();

        auto w = [&sampler]() {
            switch (sampler.Texture->Wrapping)
            {
            case Graphics::TextureWrapping::TiledWrapping:
                return Diligent::TEXTURE_ADDRESS_WRAP;
            case Graphics::TextureWrapping::HorizontalTiledWrapping:
                return Diligent::TEXTURE_ADDRESS_WRAP;
            case Graphics::TextureWrapping::VerticalTiledWrapping:
                return Diligent::TEXTURE_ADDRESS_WRAP;
            case Graphics::TextureWrapping::MirroredTiledWrapping:
                return Diligent::TEXTURE_ADDRESS_MIRROR;
            case Graphics::TextureWrapping::HorizontalMirroredTiledWrapping:
                return Diligent::TEXTURE_ADDRESS_MIRROR;
            case Graphics::TextureWrapping::VerticalMirroredTiledWrapping:
                return Diligent::TEXTURE_ADDRESS_MIRROR;
            case Graphics::TextureWrapping::WrapToBorder:
                return Diligent::TEXTURE_ADDRESS_BORDER;
            case Graphics::TextureWrapping::WrapToEdge:
                return Diligent::TEXTURE_ADDRESS_CLAMP;
            }
            return Diligent::TEXTURE_ADDRESS_WRAP;
        }();

        auto AddSamplerForShader = [&](Diligent::SHADER_TYPE shaderType) {
            Samplers.push_back({ shaderType, sampler.Name.data(), Diligent::SamplerDesc{
                f, f, f,
                w, w, w,
                } });
            Variables.push_back({ shaderType, sampler.Name.data(), Diligent::SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE });
        };

        if (sampler.Flags & Graphics::ShaderFlags::UseInPixelShader)
        {
            AddSamplerForShader(Diligent::SHADER_TYPE_PIXEL);
        }
        if (sampler.Flags & Graphics::ShaderFlags::UseInVertexShader)
        {
            AddSamplerForShader(Diligent::SHADER_TYPE_VERTEX);
        }
    }

    void SetupDynamicResoruces()
    {
        PSOCreateInfo.PSODesc.ResourceLayout.Variables = Variables.data();
        PSOCreateInfo.PSODesc.ResourceLayout.NumVariables = Variables.size();
    }

    void SetupSamplers()
    {
        PSOCreateInfo.PSODesc.ResourceLayout.ImmutableSamplers = Samplers.data();
        PSOCreateInfo.PSODesc.ResourceLayout.NumImmutableSamplers = Samplers.size();
    }

    void CompileState(Graphics::GraphicsContext &context)
    {
        Setup();
        context.CreateMaterial(*material);

        auto AddShaderVariables = [&](auto shaderType, auto &shader)
        {
            for (const SharedReference<Graphics::ShaderMetatype> &type : shader.Variables)
            {
                Variables.push_back({ shaderType, type->Name, Diligent::SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE });
            }
        };

        AddShaderVariables(Diligent::SHADER_TYPE_VERTEX, material->VertexShader);
        AddShaderVariables(Diligent::SHADER_TYPE_PIXEL, material->PixelShader);

        SetupInputLayout();

        for (const Graphics::TextureSampler *sampler : material->TextureSamplers)
        {
            if (sampler->Texture)
            {
                RegisterSampler(*sampler);
                context.Create2DTexture(*sampler->Texture);
            }
        }
        SetupDynamicResoruces();
        SetupSamplers();

        PSOCreateInfo.pVS = material->VertexShader.Data->Handle;
        PSOCreateInfo.pPS = material->PixelShader.Data->Handle;

        context.Data->Device->CreateGraphicsPipelineState(PSOCreateInfo, &Handle);

        BindStaticResources();
    }

    void BindStaticResources()
    {
        for (auto &constants : material->VertexShader.Constants)
        {
            Handle->GetStaticVariableByName(Diligent::SHADER_TYPE_VERTEX, constants->Name)->Set(constants->Data->Handle);
        }
        for (auto &constants : material->PixelShader.Constants)
        {
            Handle->GetStaticVariableByName(Diligent::SHADER_TYPE_PIXEL, constants->Name)->Set(constants->Data->Handle);
        }

        Handle->CreateShaderResourceBinding(&Binding, true);
    }

    void BindTexture(const std::string &name, Diligent::RefCntAutoPtr<Diligent::ITexture> &texture)
    {
        if (!texture)
        {
            return;
        }

        auto TextureResourceView = texture->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE);
        auto handle = Binding->GetVariableByName(Diligent::SHADER_TYPE_PIXEL, name.data());
        if (!handle)
        {
            fmt::print("Warning: Texture sampler \"{}\" not found in shader code:\n{}\n", name, material->PixelShader.SourceCode);
            return;
        }
        handle->Set(TextureResourceView);
    }

    void BindTextures()
    {
        for (const Graphics::TextureSampler *sampler : material->TextureSamplers)
        {
            if (sampler->Texture)
            {
                BindTexture(sampler->Name, sampler->Texture->Data->Handle);
            }
        }
    }
};

}
