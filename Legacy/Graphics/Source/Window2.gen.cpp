
//CLASSGEN GENERATED REGION: Includes
#include "Window2.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

#include "AMesh.h"
#include "GraphicsContext.h"
#include "Application2.gen.h"

#include "UIImageMaterial.g.h"
#include "UILabelMaterial.g.h"

//#include "Graphics/GraphicsComponents/Implementation/Implementation.h"

#include "Window2.gen.h"
#include "GraphicsComponent.gen.h"

#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include <vcruntime_string.h>
#include <vector>

//#include "Graphics/GraphicsComponents/Material3.gen.h"
//#include "Graphics/GraphicsComponents/Mesh3.gen.h"

#include <functional>
#include <deque>

/*Graphics::Material3 SpriteMaterial;
Graphics::Material3 TextMaterial;
PipelineState SpritePipeline;
PipelineState TextPipeline;
extern bool LabelForceRendering;
extern bool OldFocusSupport;

struct SpriteLayout
{
    Math::Matrix Transform;
};

Graphics::DrawBatch<SpriteLayout> Batch;

UnorderedDictionary<void *, ::SharedReference<Graphics::Mesh3>> meshes;*/

namespace Legacy::Graphics
{
namespace API
{

void onMeshLoad(Graphics::Mesh &mesh)
{
    /*auto m = ::SharedReference<Graphics::Mesh3>(Create<Graphics::Mesh3>());
    meshes[&mesh] = m;

    for(auto &v : mesh.getVertices())
    {
        m->Vertices.push_back(*((Graphics::Vertex*)&v));
    }
    for(auto &f : mesh.getFaces())
    {
        m->Faces.push_back({
            static_cast<uint32_t>(f.first),
            static_cast<uint32_t>(f.second),
            static_cast<uint32_t>(f.third),
        });
    }*/
}

void onMeshUnload(Graphics::Mesh &mesh)
{
    //meshes.erase(&mesh);
}

}

}

/*::SharedReference<Graphics::Mesh3> GetMesh(Graphics::Mesh* mesh, Diligent::RefCntAutoPtr<Diligent::IRenderDevice>& device)
{
    auto &m = meshes[mesh];
    if(!m->data->IBHandle)
    {
        CreateMesh(*m, device);
    }
    return m;
}


namespace Graphics
{

class GraphicsContext2 : public GraphicsContext
{
public:
    GraphicsContextPrivateData Data;

    using DrawQueue = UnorderedDictionary<Graphics::Mesh3*, Array<::SharedReference<Graphics::MaterialInterface>>>;

    DrawQueue Queue;

    
    virtual Math::IntegerVector getViewport() const override
    {
        return Math::IntegerVector{};
    }

    virtual void onActive() override
    {
    }

    virtual void onDeactive() override
    {
    }

    virtual void draw(const ::SharedReference<Graphics::Mesh3> &mesh, const ::SharedReference<Graphics::Material3> &material) override
    {

    }
    
    virtual void draw(const ::SharedReference<Graphics::Mesh> &mesh, const ::SharedReference<Graphics::MaterialInterface> &material) override
    {
        if(mesh && mesh->isLoaded() && material)
        {
            auto m = GetMesh(mesh.get(), Data.m_pDevice);
            Queue[m.get()].push_back(material);
        }
    }
};

}

namespace Graphics
{

template<>
struct ShaderMapping<AColor>
{
    static constexpr const char *n = "float4";
};

}

SHADER_BUFFER_BEGIN(EnvironmentConstants)
SHADER_VARIABLE(Math::Matrix, g_ViewProj)
SHADER_BUFFER_END()

SHADER_BUFFER_BEGIN(TextConstants)
SHADER_VARIABLE(AColor, Color)
SHADER_BUFFER_END()

SHADER_BUFFER_BEGIN(ImageDataConstants)
SHADER_VARIABLE(AColor, Color)
SHADER_VARIABLE(Math::Vector, ImageOffset)
SHADER_VARIABLE(Math::Vector, ImageScale)
SHADER_BUFFER_END()

SHADER_STRUCT_BEGIN(VSInput)
SHADER_LAYOUT_REG(Math::Vector, Pos,        ATTRIB0)
SHADER_LAYOUT_REG(Math::Vector, Normal,     ATTRIB1)
SHADER_LAYOUT_REG(Math::Vector, UV,         ATTRIB2)
SHADER_LAYOUT_REG(Math::Vector, Data,       ATTRIB3)

SHADER_LAYOUT_REG(Math::Vector, MtrxRow0,   ATTRIB4)
SHADER_LAYOUT_REG(Math::Vector, MtrxRow1,   ATTRIB5)
SHADER_LAYOUT_REG(Math::Vector, MtrxRow2,   ATTRIB6)
SHADER_LAYOUT_REG(Math::Vector, MtrxRow3,   ATTRIB7)
SHADER_STRUCT_END()

SHADER_STRUCT_BEGIN(PSInput)
SHADER_LAYOUT_REG(Math::Vector, Pos,        SV_POSITION)
SHADER_LAYOUT_REG(Math::Vector, UV,         TEX_COORD)
SHADER_STRUCT_END()

SHADER_STRUCT_BEGIN(PSOutput)
SHADER_LAYOUT_REG(Math::Vector, Color,      SV_TARGET)
SHADER_STRUCT_END()

::SharedReference<EnvironmentConstants> environmentConstants = CreateShared<EnvironmentConstants>();
::SharedReference<EnvironmentConstants> environmentConstants2 = CreateShared<EnvironmentConstants>();
::SharedReference<ImageDataConstants> textConstants = CreateShared<ImageDataConstants>();
::SharedReference<ImageDataConstants> pixelConstants = CreateShared<ImageDataConstants>();

void loadExample(Graphics::GraphicsContext2 &gc, Graphics::RenderBuffer &renderBuffer)
{
    SpriteMaterial.VertexShader.Constants.push_back(environmentConstants);
    SpriteMaterial.VertexShader.InputLayout = CreateShared<VSInput>();
    SpriteMaterial.VertexShader.OutputLayout = CreateShared<PSInput>();
    SpriteMaterial.PixelShader.Variables.push_back(pixelConstants);
    SpriteMaterial.PixelShader.InputLayout = SpriteMaterial.VertexShader.OutputLayout;
    SpriteMaterial.PixelShader.OutputLayout = CreateShared<PSOutput>();
    SpriteMaterial.TextureSamplers.push_back({"g_Texture", Graphics::Texture::getPlaceholder()});
    SpriteMaterial.VertexShader.SourceCode = R"(
    void main(in  VSInput VSIn,
            out PSInput PSIn) 
    {
        // HLSL matrices are row-major while GLSL matrices are column-major. We will
        // use convenience function MatrixFromRows() appropriately defined by the engine
        float4x4 InstanceTransform = MatrixFromRows(VSIn.MtrxRow0, VSIn.MtrxRow1, VSIn.MtrxRow2, VSIn.MtrxRow3);
        
        // Apply instance transformation
        float4 TransformedPos = mul(float4(VSIn.Pos.xyz, 1.0), InstanceTransform);
        
        // Apply view-projection matrix
        PSIn.Pos = mul(TransformedPos, g_ViewProj);
        PSIn.UV.xy  = VSIn.UV.xy;
    }
    )";

    SpriteMaterial.PixelShader.SourceCode = R"(
    void main(in  PSInput  PSIn,
            out PSOutput PSOut)
    {
        PSOut.Color = Color * g_Texture.Sample(g_Texture_sampler, (PSIn.UV.xy * ImageScale.xy) + ImageOffset.xy); 
    }
    )";

    TextMaterial.VertexShader.Constants.push_back(environmentConstants2);
    TextMaterial.VertexShader.InputLayout = CreateShared<VSInput>();
    TextMaterial.VertexShader.OutputLayout = CreateShared<PSInput>();
    TextMaterial.PixelShader.Variables.push_back(textConstants);
    TextMaterial.PixelShader.InputLayout = SpriteMaterial.VertexShader.OutputLayout;
    TextMaterial.PixelShader.OutputLayout = CreateShared<PSOutput>();
    TextMaterial.TextureSamplers.push_back({"g_Texture", Graphics::Texture::getPlaceholder()});
    TextMaterial.VertexShader.SourceCode = SpriteMaterial.VertexShader.SourceCode;
    TextMaterial.PixelShader.SourceCode = R"(
    void main(in  PSInput  PSIn,
            out PSOutput PSOut)
    {
        PSOut.Color = Color * g_Texture.Sample(g_Texture_sampler, PSIn.UV.xy).r; 
    }
    )";

    Batch.MaxSize = 1000000;
    CreateDrawBatch(Batch, gc.Data.m_pDevice);

    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = true;
    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = Diligent::BLEND_FACTOR_ONE;
    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOp = Diligent::BLEND_OPERATION_ADD;
    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlendAlpha = Diligent::BLEND_FACTOR_ONE;
    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlendAlpha = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
    SpritePipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOpAlpha = Diligent::BLEND_OPERATION_ADD;
    SpritePipeline.material = &SpriteMaterial;
    SpritePipeline.renderBuffer = &renderBuffer;
    SpritePipeline.CompileState(gc.Data.m_pDevice);

    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendEnable = true;
    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlend = Diligent::BLEND_FACTOR_ONE;
    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlend = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOp = Diligent::BLEND_OPERATION_ADD;
    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].SrcBlendAlpha = Diligent::BLEND_FACTOR_ONE;
    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].DestBlendAlpha = Diligent::BLEND_FACTOR_INV_SRC_ALPHA;
    TextPipeline.PSOCreateInfo.GraphicsPipeline.BlendDesc.RenderTargets[0].BlendOpAlpha = Diligent::BLEND_OPERATION_ADD;
    TextPipeline.material = &TextMaterial;
    TextPipeline.renderBuffer = &renderBuffer;
    TextPipeline.CompileState(gc.Data.m_pDevice);

}
*/
#if PLATFORM_MACOS
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#if PLATFORM_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

std::vector<Window2*> windows;

struct WindowPrivateData
{
    //Graphics::GraphicsContext2 GraphicsContext;
    //Graphics::SwapChain SwapChain;
    Math::IntegerVector Resolution;
    //Diligent::NativeWindow handle;
    GLFWwindow* window;
    bool pending = true;
};

Window2 *getWindow(GLFWwindow* w)
{
    return static_cast<Window2 *>(glfwGetWindowUserPointer(w));
}

void onResizeViewport(GLFWwindow* p, int width, int height)
{
    Window2 *w = getWindow(p);
    Math::IntegerVector resolution = { width, height };
    //w->data->SwapChain.Resize(resolution);
    //w->getComposition()->onResize(resolution);

    w->OnUpdate();
}

bool Accepted = false;


enum Key
{
    Unknown,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,

    Minus, /* - */
    Equal, /* = */
    Comma, /* , */
    Period, /* . */
    Semicolon, /* ; */
    Apostrophe, /* ' */
    LeftBracket, /* [ */
    RightBracket, /* ] */
    Slash, /* / */
    Backslash, /* \ */
    GraveAccent, /* ` */

    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
 
    NumDecimal,
    NumDivide,
    NumMultiply,
    NumSubtract,
    NumAdd,
    NumEnter,
    NumEqual,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,

    Up,
    Right,
    Down,
    Left,

    PageUp,
    PageDown,
    
    Home,
    End,

    Space,
    Tab,
    Enter,

    Insert,
    Backspace,
    Delete,

    LeftCommand,
    LeftShift,
    LeftControl,
    LeftAlt,

    RightCommand,
    RightShift,
    RightControl,
    RightAlt,

    CapsLock,
    ScrollLock,
    NumLock,

    PrintScreen,
    Pause,
    Menu,

    Esc,
};

Key convertKeyCode(int key)
{
    switch(key)
    {
    case GLFW_KEY_A:
        return Key::A;
    case GLFW_KEY_B:
        return Key::B;
    case GLFW_KEY_C:
        return Key::C;
    case GLFW_KEY_D:
        return Key::D;
    case GLFW_KEY_E:
        return Key::E;
    case GLFW_KEY_F:
        return Key::F;
    case GLFW_KEY_G:
        return Key::G;
    case GLFW_KEY_H:
        return Key::H;
    case GLFW_KEY_I:
        return Key::I;
    case GLFW_KEY_J:
        return Key::J;
    case GLFW_KEY_K:
        return Key::K;
    case GLFW_KEY_L:
        return Key::L;
    case GLFW_KEY_M:
        return Key::M;
    case GLFW_KEY_N:
        return Key::N;
    case GLFW_KEY_O:
        return Key::O;
    case GLFW_KEY_P:
        return Key::P;
    case GLFW_KEY_Q:
        return Key::Q;
    case GLFW_KEY_R:
        return Key::R;
    case GLFW_KEY_S:
        return Key::S;
    case GLFW_KEY_T:
        return Key::T;
    case GLFW_KEY_U:
        return Key::U;
    case GLFW_KEY_V:
        return Key::V;
    case GLFW_KEY_W:
        return Key::W;
    case GLFW_KEY_X:
        return Key::X;
    case GLFW_KEY_Y:
        return Key::Y;
    case GLFW_KEY_Z:
        return Key::Z;

    case GLFW_KEY_0:
        return Key::Key0;
    case GLFW_KEY_1:
        return Key::Key1;
    case GLFW_KEY_2:
        return Key::Key2;
    case GLFW_KEY_3:
        return Key::Key3;
    case GLFW_KEY_4:
        return Key::Key4;
    case GLFW_KEY_5:
        return Key::Key5;
    case GLFW_KEY_6:
        return Key::Key6;
    case GLFW_KEY_7:
        return Key::Key7;
    case GLFW_KEY_8:
        return Key::Key8;
    case GLFW_KEY_9:
        return Key::Key9;
    

    case GLFW_KEY_MINUS:
        return Key::Minus;
    case GLFW_KEY_EQUAL:
        return Key::Equal;
    case GLFW_KEY_COMMA:
        return Key::Comma;
    case GLFW_KEY_PERIOD:
        return Key::Period;
    case GLFW_KEY_SEMICOLON:
        return Key::Semicolon;
    case GLFW_KEY_APOSTROPHE:
        return Key::Apostrophe;
    case GLFW_KEY_LEFT_BRACKET:
        return Key::LeftBracket;
    case GLFW_KEY_RIGHT_BRACKET:
        return Key::RightBracket;
    case GLFW_KEY_SLASH:
        return Key::Slash;
    case GLFW_KEY_BACKSLASH:
        return Key::Backslash;
    case GLFW_KEY_GRAVE_ACCENT:
        return Key::GraveAccent;

    case GLFW_KEY_F1:
        return Key::F1;
    case GLFW_KEY_F2:
        return Key::F2;
    case GLFW_KEY_F3:
        return Key::F3;
    case GLFW_KEY_F4:
        return Key::F4;
    case GLFW_KEY_F5:
        return Key::F5;
    case GLFW_KEY_F6:
        return Key::F6;
    case GLFW_KEY_F7:
        return Key::F7;
    case GLFW_KEY_F8:
        return Key::F8;
    case GLFW_KEY_F9:
        return Key::F9;
    case GLFW_KEY_F10:
        return Key::F10;
    case GLFW_KEY_F11:
        return Key::F11;
    case GLFW_KEY_F12:
        return Key::F12;
    case GLFW_KEY_F13:
        return Key::F13;
    case GLFW_KEY_F14:
        return Key::F14;
    case GLFW_KEY_F15:
        return Key::F15;
    case GLFW_KEY_F16:
        return Key::F16;
    case GLFW_KEY_F17:
        return Key::F17;
    case GLFW_KEY_F18:
        return Key::F18;
    case GLFW_KEY_F19:
        return Key::F19;
    case GLFW_KEY_F20:
        return Key::F20;
    case GLFW_KEY_F21:
        return Key::F21;
    case GLFW_KEY_F22:
        return Key::F22;
    case GLFW_KEY_F23:
        return Key::F23;
    case GLFW_KEY_F24:
        return Key::F24;
    case GLFW_KEY_F25:
        return Key::F25;

    case GLFW_KEY_KP_0:
        return Key::Num0;
    case GLFW_KEY_KP_1:
        return Key::Num1;
    case GLFW_KEY_KP_2:
        return Key::Num2;
    case GLFW_KEY_KP_3:
        return Key::Num3;
    case GLFW_KEY_KP_4:
        return Key::Num4;
    case GLFW_KEY_KP_5:
        return Key::Num5;
    case GLFW_KEY_KP_6:
        return Key::Num6;
    case GLFW_KEY_KP_7:
        return Key::Num7;
    case GLFW_KEY_KP_8:
        return Key::Num8;
    case GLFW_KEY_KP_9:
        return Key::Num9;
 
    case GLFW_KEY_KP_DECIMAL:
        return Key::NumDecimal;
    case GLFW_KEY_KP_DIVIDE:
        return Key::NumDivide;
    case GLFW_KEY_KP_MULTIPLY:
        return Key::NumMultiply;
    case GLFW_KEY_KP_SUBTRACT:
        return Key::NumSubtract;
    case GLFW_KEY_KP_ADD:
        return Key::NumAdd;
    case GLFW_KEY_KP_ENTER:
        return Key::NumEnter;
    case GLFW_KEY_KP_EQUAL:
        return Key::NumEqual;

    case GLFW_KEY_UP:
        return Key::Up;
    case GLFW_KEY_RIGHT:
        return Key::Right;
    case GLFW_KEY_DOWN:
        return Key::Down;
    case GLFW_KEY_LEFT:
        return Key::Left;

    case GLFW_KEY_PAGE_UP:
        return Key::PageUp;
    case GLFW_KEY_PAGE_DOWN:
        return Key::PageDown;
    
    case GLFW_KEY_HOME:
        return Key::Home;
    case GLFW_KEY_END:
        return Key::End;

    case GLFW_KEY_SPACE:
        return Key::Space;
    case GLFW_KEY_TAB:
        return Key::Tab;
    case GLFW_KEY_ENTER:
        return Key::Enter;

    case GLFW_KEY_INSERT:
        return Key::Insert;
    case GLFW_KEY_BACKSPACE:
        return Key::Backspace;
    case GLFW_KEY_DELETE:
        return Key::Delete;

    case GLFW_KEY_LEFT_SUPER:
        return Key::LeftCommand;
    case GLFW_KEY_LEFT_SHIFT:
        return Key::LeftShift;
    case GLFW_KEY_LEFT_CONTROL:
        return Key::LeftControl;
    case GLFW_KEY_LEFT_ALT:
        return Key::LeftAlt;

    case GLFW_KEY_RIGHT_SUPER:
        return Key::RightCommand;
    case GLFW_KEY_RIGHT_SHIFT:
        return Key::RightShift;
    case GLFW_KEY_RIGHT_CONTROL:
        return Key::RightControl;
    case GLFW_KEY_RIGHT_ALT:
        return Key::RightAlt;

    case GLFW_KEY_CAPS_LOCK:
        return Key::CapsLock;
    case GLFW_KEY_SCROLL_LOCK:
        return Key::ScrollLock;
    case GLFW_KEY_NUM_LOCK:
        return Key::NumLock;

    case GLFW_KEY_PRINT_SCREEN:
        return Key::PrintScreen;

    case GLFW_KEY_PAUSE:
        return Key::Pause;

    case GLFW_KEY_MENU:
        return Key::Menu;

    case GLFW_KEY_ESCAPE:
        return Key::Esc;
    };

    return Key::Unknown;
}

void onKeyInput(GLFWwindow* p, int key, int scancode, int action, int mods)
{
    Window2 *w = getWindow(p);
    ::SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
    
    switch(action)
    {
    case GLFW_PRESS:
    case GLFW_REPEAT:
    {
        AWindowKeyPressEvent e(*w, convertKeyCode(key));
        //component->onKeyPress(e);
        component->inputEventChannel.sendAcceptableEvent(e);
        Accepted = e.isAccepted();
    }
    case GLFW_RELEASE:
    {
        AWindowKeyReleaseEvent e(*w, convertKeyCode(key));
        //component->onKeyRelease(e);
        component->inputEventChannel.sendAcceptableEvent(e);
    }
    }
}

void onTextInput(GLFWwindow* p, unsigned int codepoint)
{
    Window2 *w = getWindow(p);
    ::SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();

    if(!Accepted)
    {
        AWindowKeyCharEvent e(*w, char(codepoint));
        //component->onKeyChar(e);
        component->inputEventChannel.sendAcceptableEvent(e);
    }
}

void onMouseInput(GLFWwindow* p, int button, int action, int mods)
{
    Window2 *w = getWindow(p);
    ::SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
    
    ATouchID id = [&](){
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            return ATouchID::LeftMouseButton;
        case GLFW_MOUSE_BUTTON_RIGHT:
            return ATouchID::RightMouseButton;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            return ATouchID::MiddleMouseButton;
        default:
            return ATouchID::LeftMouseButton;
        }
    }();

    switch(action)
    {
    case GLFW_PRESS:
    {
        AWindowTouchDownEvent e(*w, id, w->InputState.TouchModifier, w->InputState.MousePosition);
        component->onTouchDown(e);
        break;
    }
    case GLFW_RELEASE:
    {
        AWindowTouchUpEvent e(*w, id, w->InputState.TouchModifier, w->InputState.MousePosition);
        component->onTouchUp(e);
        break;
    }
    }
}

void onMouseMoveInput(GLFWwindow* p, double xpos, double ypos)
{
    Window2 *w = getWindow(p);
    ::SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
    w->InputState.MousePosition = Math::IntegerVector{ static_cast<int32_t>(xpos), static_cast<int32_t>(ypos) };
    
    AWindowTouchMoveEvent e(*w, ATouchID::LeftMouseButton, w->InputState.TouchModifier, w->InputState.MousePosition);
    component->onTouchMove(e);
}

void onScrollInput(GLFWwindow* p, double xoffset, double yoffset)
{
    Window2 *w = getWindow(p);
    ::SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
}

void onDropInput(GLFWwindow* p, int path_count, const char* paths[])
{
    Window2 *w = getWindow(p);
    ::SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
}
//CLASSGEN GENERATED REGION: ClassImplementation
Window2::Window2()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Window2::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    //object.insert("Composition", toJSONValue(Composition));
    object.insert("Title", toJSONValue(Title));
    object.insert("BackgroundColor", toJSONValue(BackgroundColor));
}
void Window2::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    //value = AJSONValue();
    //object.read("Composition", value);
    //fromJSONValue(value, Composition);
    value = AJSONValue();
    object.read("Title", value);
    fromJSONValue(value, Title);
    value = AJSONValue();
    object.read("BackgroundColor", value);
    fromJSONValue(value, BackgroundColor);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
/*::SharedReference<Legacy::Graphics::Composition> Window2::getComposition() const
{
    return this->Composition;
}
void Window2::setComposition(::SharedReference<Legacy::Graphics::Composition> const &Composition)
{
    this->Composition = Composition;
}
void Window2::setComposition(::SharedReference<Legacy::Graphics::Composition> &&Composition)
{
    this->Composition = std::move(Composition);
}*/
String Window2::getTitle() const
{
    return this->Title;
}
void Window2::setTitle(String const &Title)
{
    this->Title = Title;
}
void Window2::setTitle(String &&Title)
{
    this->Title = std::move(Title);
}
Color Window2::getBackgroundColor() const
{
    return this->BackgroundColor;
}
void Window2::setBackgroundColor(Color const &BackgroundColor)
{
    this->BackgroundColor = BackgroundColor;
}
void Window2::setBackgroundColor(Color &&BackgroundColor)
{
    this->BackgroundColor = std::move(BackgroundColor);
}
Math::IntegerVector Window2::getInitialSize() const
{
    return this->InitialSize;
}
void Window2::setInitialSize(Math::IntegerVector const &InitialSize)
{
    this->InitialSize = InitialSize;
}
void Window2::setInitialSize(Math::IntegerVector &&InitialSize)
{
    this->InitialSize = std::move(InitialSize);
}
//CLASSGEN END REGION

bool Window2::IsActive() const
{
    return true/*data->pending || !glfwWindowShouldClose(data->window)*/;
}


template<typename Type, auto DepthFunction = &Type::GetChildren>
struct RecursiveIterator
{
    using This = RecursiveIterator<Type, DepthFunction>;
    using IteratorType = decltype(std::invoke(DepthFunction, Type()).begin());
    struct Cursor
    {
        IteratorType pos;
        IteratorType end;
        bool atEnd() const { return pos == end; }
    };
    std::deque<Cursor> stack;

    RecursiveIterator begin() const { return *this; }
    RecursiveIterator end() const { return This(); }

    static Cursor CreateChildCursor(Type &value)
    {
        auto &children = std::invoke(DepthFunction, value);
        return Cursor{ children.begin(), children.end() };
    }
    
    RecursiveIterator()
    {
        stack.push_back(Cursor{});
    }
    
    RecursiveIterator(Type &value)
    {
        auto &container = std::invoke(DepthFunction, value);
        stack.push_back(CreateChildCursor(value));
    }
    
    /*template<typename Type>
    RecursiveIterator(Container<Type> &&container)
    {
        stack.push({ container.begin(), container.end() });
    }*/

    size_t depth() const { return stack.size(); }

    bool atEnd() const { return depth() == 1 && stack.back().atEnd(); }

    RecursiveIterator& operator++()
    {
        if(stack.back().atEnd())
        {
            return *this;
        }

        Cursor cursor = CreateChildCursor(getValue());

        ++stack.back().pos;

        if(!cursor.atEnd())
        {
            stack.push_back(cursor);
            return *this;
        }

        while(stack.back().atEnd())
        {
            if(depth() > 1)
            {
                stack.pop_back();
            }
            else
            {
                clear();
                return *this;
            }
        }

        return *this;
    }

    void emplace(size_t size)
    {
        stack.emplace(size);
    }

    void clear()
    {
        stack.resize(1);
        stack.back() = {};
    }

    Type& getValue()
    {
        return *stack.back().pos;
    }

    std::pair<size_t, Type&> get()
    {
        return { depth(), getValue() };
    }

    std::pair<size_t, Type&> operator*()
    {
        return get();
    }

    std::pair<size_t, Type&> operator->()
    {
        return get();
    }

    bool operator ==(const RecursiveIterator &it) const
    {
        return stack.back().pos == it.stack.back().pos;
    }

    bool operator !=(const RecursiveIterator &it) const
    {
        return !(*this == it);
    }
};

struct Data
{
    const char *str;
    std::vector<Data> data;
    
    std::vector<Data>& GetChildren() { return data; }
};

void Window2::OnCreate()
{
    windows.push_back(this);
}

void Render()
{

}

void Window2::OnUpdate()
{
//     if (data->pending)
//     {
//         data->pending = false;
// #if PLATFORM_WIN32
//         glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
// #else
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// #endif
//         /* Create a windowed mode window and its OpenGL context */
// 
//         GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
//         Math::IntegerRectangle ScreenArea;
//         glfwGetMonitorWorkarea(primaryMonitor, &ScreenArea.Position.X, &ScreenArea.Position.Y, &ScreenArea.Size.X, &ScreenArea.Size.Y);
// 
//         const Math::IntegerVector &resolution = getInitialSize();
//         auto WindowRectangle = Math::getCenteredRectangle(ScreenArea.Size, resolution);
// 
//         data->window = glfwCreateWindow(WindowRectangle.Size.X, WindowRectangle.Size.Y, getTitle().data(), nullptr, nullptr);
//         glfwSetWindowPos(data->window, WindowRectangle.Position.X, WindowRectangle.Position.Y);
//         glfwSetWindowUserPointer(data->window, this);
//         glfwSetFramebufferSizeCallback(data->window, &onResizeViewport);
//         glfwSetKeyCallback(data->window, &onKeyInput);
//         glfwSetCharCallback(data->window, &onTextInput);
//         glfwSetMouseButtonCallback(data->window, &onMouseInput);
//         glfwSetCursorPosCallback(data->window, &onMouseMoveInput);
//         glfwSetScrollCallback(data->window, &onScrollInput);
//         glfwSetDropCallback(data->window, &onDropInput);
// 
//         //LabelForceRendering = true;
//         OldFocusSupport = false;
//         Composition->onResize(resolution);
// 
//         void* window_handle = nullptr;
// #if PLATFORM_WIN32
//         window_handle = static_cast<void*>(glfwGetWin32Window(data->window));
// #elif PLATFORM_MACOS
//         glfwMakeContextCurrent(window);
//         window_handle = static_cast<void*>(glfwGetCocoaWindow(data->window));
// #elif PLATFORM_LINUX
//         // FIXME: Get x11 or wayland window handle using glfw
//         glfwMakeContextCurrent(data->window);
//         throw std::runtime_error("Missing window handle");
// #endif
//         data->handle = Diligent::NativeWindow{window_handle};
// 
//         data->GraphicsContext.ApplyViewport = false;
//         data->GraphicsContext.Data.InitializeWindow(data->handle, data->SwapChain);
//         glDisable(GL_FRAMEBUFFER_SRGB);
// 
//         setBackgroundColor(AColor::fromHex(0x00262626));
//         loadExample(data->GraphicsContext, data->SwapChain.RenderBuffer);
//     }
// 
//     Legacy::Graphics::HardwareHandle<Legacy::Graphics::Texture>::LoadObjects();
//     Legacy::Graphics::HardwareHandle<Legacy::Graphics::Material>::LoadObjects();
//     Legacy::Graphics::HardwareHandle<Legacy::Graphics::Mesh>::LoadObjects();
//     //Legacy::Graphics::HardwareHandle<Legacy::Graphics::Canvas>::LoadObjects();
// 
//     Legacy::Graphics::GraphicsContext::pushContext(data->GraphicsContext);
// 
//     Composition->onUpdate();
//     
//     data->GraphicsContext.Data.SetRenderBuffer(data->SwapChain.RenderBuffer);
//     data->GraphicsContext.Data.ClearRenderBuffers(getBackgroundColor());
//     data->GraphicsContext.Data.ClearDepthBuffer(1.0f);
//     
//     environmentConstants->g_ViewProj = Math::Matrix::getIdentity();//= ACamera::getCurrentCamera()->getMatrix().getTransposed();
//     data->GraphicsContext.Data.ApplyConstants(*environmentConstants);
//     environmentConstants2->g_ViewProj = Math::Matrix::getIdentity();//= ACamera::getCurrentCamera()->getMatrix().getTransposed();
//     data->GraphicsContext.Data.ApplyConstants(*environmentConstants2);
// 
//     for(auto &pair : data->GraphicsContext.Queue)
//     {
//         auto &mesh = *pair.first;
//         auto &materials = pair.second;
// 
//         Batch.Instances.resize(1);
//         for (auto &material : materials)
//         {
//             if(auto imageMaterial = DynamicCast<UI::DynamicImageMaterial>(material))
//             {
//                 Batch.Instances[0].Transform = imageMaterial->data.ModelViewProjectionMatrix;
//                 if(imageMaterial->data.Image)
//                 {
//                     if(!imageMaterial->data.Image->Data->Handle)
//                     {
//                         if(!imageMaterial->data.Image->getBuffer().empty())
//                         {
//                             Create2DTexture(*imageMaterial->data.Image, data->GraphicsContext.Data.m_pDevice);
//                         }
//                     }
//                     if (SpriteMaterial.TextureSamplers[0].Texture != imageMaterial->data.Image)
//                     {
//                         SpriteMaterial.TextureSamplers[0].Texture = imageMaterial->data.Image;
//                     }
//                 }
// 
//                 pixelConstants->Color = imageMaterial->data.Color;
//                 pixelConstants->ImageOffset = imageMaterial->data.ImageOffset;
//                 pixelConstants->ImageScale = imageMaterial->data.ImageScale;
// 
//                 data->GraphicsContext.Data.ApplyConstants(*pixelConstants);
//                 SpritePipeline.Binding->GetVariableByName(Diligent::SHADER_TYPE_PIXEL, pixelConstants->Name)->Set(pixelConstants->Data->Handle);
//                 SpritePipeline.BindTextures();
//     
//                 data->GraphicsContext.Data.SetState(SpritePipeline);
//             }
//             else if(auto labelMaterial = DynamicCast<UI::DynamicLabelMaterial>(material))
//             {
//                 Batch.Instances[0].Transform = labelMaterial->data.ModelViewProjectionMatrix;
//                 if(labelMaterial->data.TextMask)
//                 {
//                     if(!labelMaterial->data.TextMask->Data->Handle)
//                     {
//                         Create2DTexture(*labelMaterial->data.TextMask, data->GraphicsContext.Data.m_pDevice);
//                     }
//                     if (TextMaterial.TextureSamplers[0].Texture != labelMaterial->data.TextMask)
//                     {
//                         TextMaterial.TextureSamplers[0].Texture = labelMaterial->data.TextMask;
//                     }
//                 }
// 
//                 textConstants->Color = labelMaterial->data.Color;
//                 
//                 data->GraphicsContext.Data.ApplyConstants(*textConstants);
//                 TextPipeline.Binding->GetVariableByName(Diligent::SHADER_TYPE_PIXEL, textConstants->Name)->Set(textConstants->Data->Handle);
//                 TextPipeline.BindTextures();
// 
//                 data->GraphicsContext.Data.SetState(TextPipeline);
//             }
// 
//             data->GraphicsContext.Data.Upload(Batch);
//             data->GraphicsContext.Data.Render(mesh, Batch);
//         }
//     }
// 
//     data->GraphicsContext.Queue.clear();
//     Legacy::Graphics::GraphicsContext::popContext();
// 
//     data->SwapChain.Swap();
}

Window2::~Window2()
{
    rng::remove(windows, this);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
