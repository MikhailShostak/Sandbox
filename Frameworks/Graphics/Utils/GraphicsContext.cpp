#include "PrivateImplementation.hpp"

#if D3D11_SUPPORTED
#include <EngineFactoryD3D11.h>
#endif
#if D3D12_SUPPORTED
#include <EngineFactoryD3D12.h>
#endif
#if GL_SUPPORTED || GLES_SUPPORTED
#include <EngineFactoryOpenGL.h>
#endif
#if VULKAN_SUPPORTED
#include <EngineFactoryVk.h>
#endif
#if METAL_SUPPORTED
#include <EngineFactoryMtl.h>
#endif

namespace
{

inline Diligent::RENDER_DEVICE_TYPE getPreferedDeviceType()
{
#if D3D12_SUPPORTED
    return Diligent::RENDER_DEVICE_TYPE_D3D12;
#elif VULKAN_SUPPORTED
    return Diligent::RENDER_DEVICE_TYPE_VULKAN;
#elif D3D11_SUPPORTED
    return Diligent::RENDER_DEVICE_TYPE_D3D11;
#elif GL_SUPPORTED
    return Diligent::RENDER_DEVICE_TYPE_GL;
#endif
}

Diligent::RENDER_DEVICE_TYPE g_DeviceType = getPreferedDeviceType();

}

namespace Graphics
{

GraphicsContext::GraphicsContext() = default;
GraphicsContext::GraphicsContext(GraphicsContext && other) = default;
GraphicsContext& GraphicsContext::operator =(GraphicsContext && other) = default;
GraphicsContext::~GraphicsContext() = default;

bool/*Result*/ GraphicsContext::Initialize(const Graphics::NativeWindow &NativeWindow, Graphics::SwapChain &SwapChain)
{
#if PLATFORM_WIN32
    Diligent::NativeWindow window(NativeWindow);

    Diligent::SwapChainDesc SCDesc;
    SCDesc.ColorBufferFormat = Data->ColorBufferFormat;
    SCDesc.DepthBufferFormat = Data->DepthBufferFormat;
    switch (g_DeviceType)
    {
#if D3D11_SUPPORTED
    case Diligent::RENDER_DEVICE_TYPE_D3D11:
    {
        Diligent::EngineD3D11CreateInfo EngineCI;
#if ENGINE_DLL
        auto *GetEngineFactoryD3D11 = Diligent::LoadGraphicsEngineD3D11();
#endif
        auto *pFactoryD3D11 = GetEngineFactoryD3D11();
        pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &Data->Device, &Handle);
        pFactoryD3D11->CreateSwapChainD3D11(Data->Device, Handle, SCDesc, Diligent::FullScreenModeDesc{}, window, &SwapChain.Data->Handle);
    }
    break;
#endif


#if D3D12_SUPPORTED
    case Diligent::RENDER_DEVICE_TYPE_D3D12:
    {
#if ENGINE_DLL
        auto GetEngineFactoryD3D12 = Diligent::LoadGraphicsEngineD3D12();
#endif
        Diligent::EngineD3D12CreateInfo EngineCI;

        auto *pFactoryD3D12 = GetEngineFactoryD3D12();
        pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &Data->Device, &Data->Handle);
        pFactoryD3D12->CreateSwapChainD3D12(Data->Device, Data->Handle, SCDesc, Diligent::FullScreenModeDesc{}, window, &SwapChain.Data->Handle);
    }
    break;
#endif


#if GL_SUPPORTED
    case Diligent::RENDER_DEVICE_TYPE_GL:
    {
#if EXPLICITLY_LOAD_ENGINE_GL_DLL
        auto GetEngineFactoryOpenGL = Diligent::LoadGraphicsEngineOpenGL();
#endif
        auto *pFactoryOpenGL = GetEngineFactoryOpenGL();

        Diligent::EngineGLCreateInfo EngineCI;
        EngineCI.Window.hWnd = window.hWnd;

        pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &Data->Device, &Data->Handle, SCDesc, &SwapChain.Data->Handle);
    }
    break;
#endif


#if VULKAN_SUPPORTED
    case Diligent::RENDER_DEVICE_TYPE_VULKAN:
    {
#if EXPLICITLY_LOAD_ENGINE_VK_DLL
        auto GetEngineFactoryVk = Diligent::LoadGraphicsEngineVk();
#endif
        Diligent::EngineVkCreateInfo EngineCI;

        auto* pFactoryVk = Diligent::GetEngineFactoryVk();

        //TODO: Rework (only one instance of logical device is allowed)
        static Diligent::RefCntAutoPtr<Diligent::IDeviceContext> Handle;
        static Diligent::RefCntAutoPtr<Diligent::IRenderDevice> Device;

        static bool initialized = false;
        if (!initialized)
        {
            pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &Device, &Handle);
            initialized = true;
        }

        Data->Device = Device;
        Data->Handle = Handle;

        if (!SwapChain.Data->Handle)
        {
            pFactoryVk->CreateSwapChainVk(Data->Device, Data->Handle, SCDesc, window, &SwapChain.Data->Handle);
        }
    }
    break;
#endif
    default:
        std::cerr << "Unknown/unsupported device type";
        return { false };
        break;
    }

    return { Data->Device != nullptr && Data->Handle != nullptr && SwapChain.Data->Handle != nullptr };
#else
    //TODO: fix runtime on non windows platforms
    return { false };
#endif
}

void GraphicsContext::CreateDrawBatch(Graphics::DrawBatchBase &Batch)
{
    auto [count, buffer, size, max] = Batch.GetLayoutInfo();
    Diligent::BufferDesc desc;
    desc.Name = "Instance data buffer";
    desc.Usage = Diligent::USAGE_DEFAULT;
    desc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
    desc.uiSizeInBytes = max;
    Data->Device->CreateBuffer(desc, nullptr, &Batch.Data->Handle);
}

void CreateUniformBuffer(Diligent::RefCntAutoPtr<Diligent::IRenderDevice> &device, size_t size, const char *name, Diligent::RefCntAutoPtr<Diligent::IBuffer> &buffer)
{
    Diligent::BufferDesc CBDesc;
    CBDesc.Name = name;
    CBDesc.uiSizeInBytes = size;
    CBDesc.Usage = Diligent::USAGE_DYNAMIC;
    CBDesc.BindFlags = Diligent::BIND_UNIFORM_BUFFER;
    CBDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;
    device->CreateBuffer(CBDesc, nullptr, &buffer);
}

void GraphicsContext::CreateConstants(Graphics::ShaderMetatype &Constants)
{
    if (Constants.Data->Handle)
    {
        return;
    }

    CreateUniformBuffer(Data->Device, Constants.DataSize, Constants.Name, Constants.Data->Handle);
}

void CreateVertexBuffer(Graphics::Mesh &Mesh, Diligent::RefCntAutoPtr<Diligent::IRenderDevice> &Device)
{
    if (Mesh.Data->VBHandle)
    {
        return;
    }

    Diligent::BufferData VBData;
    VBData.pData = Mesh.Vertices.data();
    VBData.DataSize = sizeof(Graphics::Vertex) * Mesh.Vertices.size();

    Diligent::BufferDesc VertBuffDesc;
    VertBuffDesc.Name = "VertexBuffer";
    VertBuffDesc.Usage = Diligent::USAGE_IMMUTABLE;
    VertBuffDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
    VertBuffDesc.uiSizeInBytes = VBData.DataSize;

    Device->CreateBuffer(VertBuffDesc, &VBData, &Mesh.Data->VBHandle);
}

void CreateIndexBuffer(Graphics::Mesh &Mesh, Diligent::RefCntAutoPtr<Diligent::IRenderDevice> &Device)
{
    if (Mesh.Data->IBHandle)
    {
        return;
    }

    Diligent::BufferData IBData;
    IBData.pData = Mesh.Faces.data();
    IBData.DataSize = sizeof(Graphics::Face) * Mesh.Faces.size();

    Diligent::BufferDesc IndBuffDesc;
    IndBuffDesc.Name = "IndexBuffer";
    IndBuffDesc.Usage = Diligent::USAGE_IMMUTABLE;
    IndBuffDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
    IndBuffDesc.uiSizeInBytes = IBData.DataSize;

    Device->CreateBuffer(IndBuffDesc, &IBData, &Mesh.Data->IBHandle);
}

void GraphicsContext::CreateMesh(Graphics::Mesh &Mesh)
{
    CreateVertexBuffer(Mesh, Data->Device);
    CreateIndexBuffer(Mesh, Data->Device);
}

enum class TextureBufferType
{
    Texture,
    RenderTarget,
    DepthStencil
};

void CreateTextureBuffer(Graphics::Texture &Texture, TextureBufferType BufferType, Diligent::RefCntAutoPtr<Diligent::IRenderDevice> &Device)
{
    if (Texture.Data->Handle)
    {
        return;
    }

    Diligent::RefCntAutoPtr<Diligent::ITexture> result;
    Diligent::TextureDesc desc;
    desc.Type = Diligent::RESOURCE_DIM_TEX_2D;
    switch (Texture.Channels)
    {
    case 1:
        desc.Format = Diligent::TEX_FORMAT_R8_UNORM;
        break;
    case 2:
        desc.Format = Diligent::TEX_FORMAT_RG8_UNORM;
        break;
    default:
        desc.Format = Diligent::TEX_FORMAT_RGBA8_UNORM;
        break;
    }
    desc.Width = Texture.Size.x;
    desc.Height = Texture.Size.y;
    desc.MipLevels = 1;
    desc.BindFlags = Diligent::BIND_SHADER_RESOURCE;
    if (BufferType == TextureBufferType::Texture)
    {
        //desc.Usage = USAGE_STATIC;
        StaticArray<Diligent::TextureSubResData, 1> subdata = {
            Diligent::TextureSubResData{ Texture.Buffer.data(), StaticCast<Diligent::Uint32>(Texture.Size.i32[0] * Texture.Channels) }
        };

        Diligent::TextureData data;
        data.pSubResources = subdata.data();
        data.NumSubresources = subdata.size();

        Device->CreateTexture(desc, &data, &Texture.Data->Handle);
    }
    else
    {
        if (BufferType == TextureBufferType::RenderTarget)
        {
            desc.BindFlags = desc.BindFlags | Diligent::BIND_RENDER_TARGET;
        }
        else
        {
            desc.Format = Diligent::TEX_FORMAT_D32_FLOAT;
            desc.BindFlags = desc.BindFlags | Diligent::BIND_DEPTH_STENCIL;
        }
        Device->CreateTexture(desc, nullptr, &Texture.Data->Handle);
    }
}

void GraphicsContext::Create2DTexture(Graphics::Texture &Texture)
{
    CreateTextureBuffer(Texture, Graphics::TextureBufferType::Texture, Data->Device);
}

void GraphicsContext::CreateRenderTarget(Graphics::RenderTarget &RenderTarget)
{
    for (auto &texture : RenderTarget.Targets)
    {
        CreateTextureBuffer(*texture, Graphics::TextureBufferType::RenderTarget, Data->Device);
    }

    if (RenderTarget.DepthStencil)
    {
        CreateTextureBuffer(*RenderTarget.DepthStencil, TextureBufferType::DepthStencil, Data->Device);
    }

    RenderTarget.IsCompiled = true;
}

void CompileShader(Graphics::Shader &shader, const String &samplers, Diligent::SHADER_TYPE type, const String &name, GraphicsContext &context)
{
    String buffer;
    for (auto &constants : shader.Constants)
    {
        buffer.append(constants->GetCode());
        context.CreateConstants(*constants);
    }
    for (auto &variables : shader.Variables)
    {
        buffer.append(variables->GetCode());
        context.CreateConstants(*variables);
    }
    buffer.append(shader.InputLayout->GetCode());
    buffer.append(shader.OutputLayout->GetCode());
    buffer.append(samplers);
    buffer.append(shader.SourceCode);

    Diligent::ShaderCreateInfo ShaderCI;
    ShaderCI.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;
    ShaderCI.UseCombinedTextureSamplers = true;

    ShaderCI.Desc.ShaderType = type;
    ShaderCI.EntryPoint = "main";
    ShaderCI.Desc.Name = name.data();
    ShaderCI.Source = buffer.data();
    context.Data->Device->CreateShader(ShaderCI, &shader.Data->Handle);
    
    if (!shader.Data->Handle)
    {
        fmt::print("Failed to compile shader ({}):\n{}\n", name, buffer);
    }
}

void GraphicsContext::CreateMaterial(Graphics::Material &Material)
{
    if (Material.IsCompiled)
    {
        return;
    }

    String VertexSamplers;
    String PixelSamplers;
    auto Generate2DSamplerCode = [](const String &name)
    {
        return
            "Texture2D " + name + ";\n"
            "SamplerState " + name + "_sampler;\n";
    };
    for (const Graphics::TextureSampler &sampler : Material.TextureSamplers)
    {
        if (sampler.Flags & Graphics::ShaderFlags::UseInVertexShader)
        {
            VertexSamplers.append(Generate2DSamplerCode(sampler.Name));
        }
        if (sampler.Flags & Graphics::ShaderFlags::UseInPixelShader)
        {
            PixelSamplers.append(Generate2DSamplerCode(sampler.Name));
        }
    }

    CompileShader(Material.VertexShader, VertexSamplers, Diligent::SHADER_TYPE_VERTEX, "Vertex shader", *this);
    CompileShader(Material.PixelShader, PixelSamplers, Diligent::SHADER_TYPE_PIXEL, "Pixel shader", *this);

    Material.IsCompiled = true;
}

void GraphicsContext::ClearRenderBuffers(const hlslpp::float4 &Color)
{
    for (size_t i = 0; i < CurrentRenderBuffer.Data->Size; ++i)
    {
        Data->Handle->ClearRenderTarget(CurrentRenderBuffer.Data->RenderTargets[i], &Color.f32[0], Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    }
}

void GraphicsContext::ClearDepthBuffer(float Value)
{
    Data->Handle->ClearDepthStencil(CurrentRenderBuffer.Data->DepthStencilBuffer, Diligent::CLEAR_DEPTH_FLAG, Value, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void GraphicsContext::ClearStencilBuffer(uint8_t Value)
{
    Data->Handle->ClearDepthStencil(CurrentRenderBuffer.Data->DepthStencilBuffer, Diligent::CLEAR_STENCIL_FLAG, 0, Value, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void GraphicsContext::ClearDepthStencilBuffers(float DepthValue, uint8_t StencilValue)
{
    Data->Handle->ClearDepthStencil(CurrentRenderBuffer.Data->DepthStencilBuffer, Diligent::CLEAR_DEPTH_FLAG | Diligent::CLEAR_STENCIL_FLAG, DepthValue, StencilValue, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void GraphicsContext::SetRenderBuffer(const Graphics::RenderBuffer &buffer)
{
    CurrentRenderBuffer = buffer;
    Data->Handle->SetRenderTargets(
        CurrentRenderBuffer.Data->Size,
        CurrentRenderBuffer.Data->RenderTargets.data(),
        CurrentRenderBuffer.Data->DepthStencilBuffer,
        Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
    );
}
void GraphicsContext::Render(Graphics::SwapChain &SwapChain)
{
    Data->Handle->Flush();
    SwapChain.Swap();
}

void GraphicsContext::Upload(Graphics::DrawBatchBase &Batch)
{
    auto [count, buffer, size, max] = Batch.GetLayoutInfo();
    Data->Handle->UpdateBuffer(Batch.Data->Handle, 0, size, buffer, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void GraphicsContext::ApplyConstants(Graphics::ShaderMetatype &Constants)
{
    CreateConstants(Constants);
    Diligent::MapHelper<uint8_t> helper(Data->Handle, Constants.Data->Handle, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
    memcpy(&helper[0], Constants.getDataPointer(), Constants.DataSize);
}

void GraphicsContext::SetState(PipelineState &State)
{
    Data->Handle->SetPipelineState(State.Data->Handle);
    Data->Handle->CommitShaderResources(State.Data->Binding, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void GraphicsContext::Draw(Graphics::Mesh &Mesh, Graphics::DrawBatchBase &Batch)
{
    if (!Mesh.IsCompiled)
    {
        CreateMesh(Mesh);
    }

    Upload(Batch);

    auto [count, buffer, size, max] = Batch.GetLayoutInfo();

    StaticArray<Diligent::Uint32, 2> offsets = { 0, 0 };
    StaticArray<Diligent::IBuffer *, 2> buffers = { Mesh.Data->VBHandle, Batch.Data->Handle };
    Data->Handle->SetVertexBuffers(0, buffers.size(), buffers.data(), offsets.data(), Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION, Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
    Data->Handle->SetIndexBuffer(Mesh.Data->IBHandle, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    Diligent::DrawIndexedAttribs DrawAttrs;
    DrawAttrs.IndexType = Diligent::VT_UINT32;
    DrawAttrs.NumIndices = 3 * Mesh.Faces.size();
    DrawAttrs.NumInstances = count;
    DrawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
    Data->Handle->DrawIndexed(DrawAttrs);

    Mesh.IsCompiled = true;
}

void GraphicsContext::ApplyMaterial(Graphics::Material &material)
{
    auto it = Data->Pipelines.find(&material);
    if (it == Data->Pipelines.end())
    {
        Graphics::PipelineState state;
        it = Data->Pipelines.insert({ &material, std::move(state) }).first;

        if (!material.RenderBuffer.Data->RenderTargets[0])
        {
            fmt::print("WARNING: Material Render is not set, current will be used instead...\n");
            material.RenderBuffer = CurrentRenderBuffer;
        }
        it->second.Data->material = &material;
        it->second.Data->CompileState(*this);
    }
    auto &pipeline = it->second;

    if (!pipeline.Data->Handle)
    {
        return;
    }

    auto ApplyShaderData = [this, &pipeline](Graphics::Shader &shader, Diligent::SHADER_TYPE type)
    {
        for (auto &constants : shader.Constants)
        {
            ApplyConstants(*constants);
        }
        for (auto &variables : shader.Variables)
        {
            ApplyConstants(*variables);
            auto handle = pipeline.Data->Binding->GetVariableByName(type, variables->Name);
            if (!handle)
            {
                fmt::print("Warning: Variable \"{}\" not found in shader code:\n{}\n", variables->Name, shader.SourceCode);
                continue;
            }
            pipeline.Data->Binding->GetVariableByName(type, variables->Name)->Set(variables->Data->Handle);
        }
    };

    ApplyShaderData(material.VertexShader, Diligent::SHADER_TYPE_VERTEX);
    ApplyShaderData(material.PixelShader, Diligent::SHADER_TYPE_PIXEL);

    pipeline.Data->BindTextures();
    SetState(pipeline);
}

void GraphicsContext::InvalidateMaterial(Graphics::Material& material)
{
    Data->Pipelines.erase(&material);
}

}
