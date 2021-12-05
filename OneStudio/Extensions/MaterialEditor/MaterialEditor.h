#pragma once

#include <Experimental>
#include <ClassGenLibrary>
#include "GraphEditor.gen.h"
#include "NodeSearchView.gen.h"

#include "Viewport.h"

#include "RotationRecognizer.h"

#include "LavaTextures.h"


namespace Graphics
{

template<typename VertexFunctor, typename FaceFunctor>
inline SharedReference<Mesh> generateGrid(const Math::IntegerVector &size, const VertexFunctor &vertexFunctor, const FaceFunctor &faceFunctor)
{
    Array<AVertex> verticies;
    Math::IntegerVector points = size + Math::IntegerVector{ 1, 1 };
    for (size_t y = 0; y < points.Y; ++y)
    {
        for (size_t x = 0; x < points.X; ++x)
        {
            verticies.emplaceBack(vertexFunctor(Math::IntegerVector{ x, y }));
        }
    }

    Array<AFace> faces;
    for (size_t y = 0; y < size.Y; ++y)
    {
        for (size_t x = 0; x < size.X; ++x)
        {
            auto quad = faceFunctor(y * points.x + x);
            faces.emplaceBack(std::move(quad.first));
            faces.emplaceBack(std::move(quad.second));
        }
    }

    return Create<Mesh>(std::move(verticies), std::move(faces));
}

inline SharedReference<Mesh> generatePlain(const Math::IntegerVector &segments, const Math::FloatVector segmentSize = { 1.0, 1.0 })
{
    Math::FloatVector step = segments.getXY<Math::FloatVector>();
    return generateGrid(segments, [&](const Math::IntegerVector &coordinates) {
        return AVertex(coordinates.X * segmentSize.X, coordinates.Y * segmentSize.Y, 0.0f, 0.0f, 0.0f, 0.1f, Math::FloatType(coordinates.X) / segments.X, Math::FloatType(coordinates.Y) / segments.Y);
    }, [&](size_t i) {
        return APair<AFace, AFace>{
            AFace{ i, i + segments.X + 1, i + 1 },
            AFace{ i + 1, i + segments.X + 1, i + segments.X + 2 },
        };
    });
}

/*inline SharedReference<Mesh> generateRectangle()
{
    SharedReference<Mesh> mesh = new Mesh();
    // 0 +-------+ 1   | y
    //   |     / |     |
    //   |   /   |     +---- x
    //   | /     |    /
    // 2 +-------+ 3 z

    mesh->setVertices({
        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
        });
    mesh->setFaces({
        { 0, 2, 1 },
        { 1, 2, 3 },
        });
    return mesh;
}

inline std::array<AVertex, 4> generateSprite()
{

}

inline SharedReference<Mesh> generateBox(const Math::IntegerVector &size)
{

    Array<AVertex> verticies = {
        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },

        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
    };
    Math::IntegerVector points = size + Math::IntegerVector{ 1, 1 };
    for (size_t y = 0; y < points.Y; ++y)
    {
        for (size_t x = 0; x < points.X; ++x)
        {
            verticies.emplaceBack(vertexFunctor(Math::IntegerVector{ x, y }));
        }
    }

    Array<AFace> faces;
    for (size_t y = 0; y < size.Y; ++y)
    {
        for (size_t x = 0; x < size.X; ++x)
        {
            auto quad = faceFunctor(y * points.x + x);
            faces.emplaceBack(std::move(quad.first));
            faces.emplaceBack(std::move(quad.second));
        }
    }

    return new Mesh(std::move(verticies), std::move(faces));
}*/

inline SharedReference<Mesh> generateSphere2(float radius, const Math::IntegerVector &segments)
{
    Math::FloatVector steps = radius / segments.getXY<Math::FloatVector>();
    return generateGrid(segments, [&](const Math::IntegerVector &coordinates) {
        const Math::FloatVector normalizedCoords = coordinates.getXY<Math::FloatVector>() / segments.getXY<Math::FloatVector>();
        const Math::FloatType theta = Math::Constants::PiTwoTimes * normalizedCoords.X;
        const Math::FloatType phi = Math::Constants::Pi * normalizedCoords.Y;
        const Math::FloatType sinPhi = sinf(phi);
        const Math::FloatVector halfNormal = {
            cosf(theta) * sinPhi,
            cosf(phi),
            sinf(theta) * sinPhi,
        };
        const Math::FloatVector position = halfNormal * radius;
        const Math::FloatVector normal = halfNormal * 2 * 0.1f;
        return AVertex(
            position.X, position.Y, position.Z,
            normal.X, normal.Y, normal.Z,
            Math::FloatType(coordinates.X) / segments.X, Math::FloatType(coordinates.Y) / segments.Y);
    }, [&](size_t i) {
        return APair<AFace, AFace>{
            AFace{ i, i + segments.X + 1, i + 1 },
            AFace{ i + 1, i + segments.X + 1, i + segments.X + 2 },
        };
    });
}

}

namespace UI
{

class PreviewMaterial : public Graphics::Material
{
public:

    typedef Graphics::Material Super;
    typedef PreviewMaterial This;

    String vertexShader;
    String fragmentShader;

    String generateVertexShader() const override { return vertexShader; }
    String generateFragmentShader() const override { return fragmentShader; }

    Math::Matrix ModelViewProjectionMatrix;
    Map<String, SharedReference<Graphics::Texture>> Textures;

    void apply() const override
    {
        Super::apply();
        getHandle()->setMatrix("u_ModelViewProjectionMatrix", ModelViewProjectionMatrix);
        for (auto &pair : Textures)
        {
            getHandle()->setTexture(("u_" + pair.first).toUtf8().data(), *pair.second);
        }
    }

};
/*
class PinNodeView : public UI::ContentNodeView
{
protected:
    SharedReference<FlexBox> container = Create<FlexBox>();
    SharedReference<FlexBox> inputPins = Create<FlexBox>();
    SharedReference<Overlay> content = Create<Overlay>();
    SharedReference<FlexBox> outputPins = Create<FlexBox>();
public:

    class Pin : public UI::Overlay 
    {
    public:
        SharedReference<ImageView> socket = Create<ImageView>();
        SharedReference<Label> label = Create<Label>();
        
        enum PinType
        {
            Input,
            Output,
        } type;

        void onLoad(ALoadEvent &event)
        {
            Super::onLoad(event);

            setSizePolicy(SizePolicy::ContentWrapped);

            socket->setImage(::Pin);
            socket->setColor(AColor(1.0f, 0.9f));
            socket->setSize({ 10, 10 });
            socket->setSizePolicy(SizePolicy::Fixed);

            label->setSizePolicy(SizePolicy::ContentWrapped);
            if (!socket->getParent() && !label->getParent())
            {
                addView(socket);
                addView(label);
                setData({ OverlayData{ { 4, 4, 4, 4, }, Core::Alignment::Start, Core::Alignment::Center }, OverlayData{ { 4, 4, 4, 18 } } });
            }
        }

        PinType getType() const
        {
            return type;
        }

        void setType(PinType type)
        {
            this->type = type;
            requestLayoutUpdate();
        }

        void onLayout(AUpdateEvent &event)
        {
            switch (this->type)
            {
            case Input:
                label->setTextAlign(Core::TextAlign::Start);
                Data[0].HorizontalAlignment = Core::Alignment::Start;
                Data[1].HorizontalAlignment = Core::Alignment::Start;
                Data[1].Padding.Right = 4;
                Data[1].Padding.Left = 18;
                break;
            case Output:
                label->setTextAlign(Core::TextAlign::End);
                Data[0].HorizontalAlignment = Core::Alignment::End;
                Data[1].HorizontalAlignment = Core::Alignment::End;
                Data[1].Padding.Right = 18;
                Data[1].Padding.Left = 4;
                break;
            }

            Super::onLayout(event);
        }
    };

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        inputPins->setDirection(UI::Direction::Vertical);
        inputPins->setSizePolicy(SizePolicy::ContentWrapped);

        content->setSizePolicy(SizePolicy::ContentWrapped);
        content->setData({ {} });

        outputPins->setDirection(UI::Direction::Vertical);
        outputPins->setSizePolicy(SizePolicy::ContentWrapped);

        container->setSizePolicy(SizePolicy::ContentWrapped);
        container->setDirection(UI::Direction::Horizontal);
        container->setData({ {}, {}, {} });

        if (!inputPins->getParent() && !content->getParent() && !outputPins->getParent() && !container->getParent())
        {
            container->addView(inputPins);
            container->addView(content);
            container->addView(outputPins);
            addView(container);
        }
    }
};

class PinNodeViewWithPreview : public PinNodeView
{
    SharedReference<ImageView> imageView = Create<ImageView>();
public:
    PinNodeViewWithPreview()
    {
        imageView->setImage(::Node);
        imageView->setSizePolicy(SizePolicy::Fixed);
        imageView->setSize({ 100, 100 });
        content->addView(imageView);
    }

    SharedReference<View> getContent() { return nullptr; }
};*/

class ValuePin : public PinNodeView::Pin
{
public:
    SharedReference<PinNodeView> getParentNode() const
    {
        //HACK
        auto &views = getParent()->getParent()->getParent()->getParent()->getViews();
        SharedReference<View> view = *std::find_if(views.begin(), views.end(), [&](const auto &v) { return getParent()->getParent()->getParent() == v.data(); });
        return view.as<PinNodeView>();
    }

    //SharedReference<LegacyClassGen::BaseCGType> type;
    String type;
};

class MaterialF
{
public:

    LegacyClassGen::Function functionData;
    virtual String generateShader(const Array<String> &paramaters) const = 0;
    virtual APixmap generatePreview() { return APixmap(); }
};

class MaterialNodeView : public PinNodeView, public PinNodeAdapter
{
    String type;
    SharedReference<MaterialF> function;
public:
    using Super = PinNodeView;

    /*AJSONValue serialize() const override { return AJSONValue(); }
    void deserialize(const AJSONValue &data) override {}*/

    void setData(const LegacyClassGen::NodeData &data, const SharedReference<MaterialF> &function)
    {
        title->setText(function->functionData.Identifier);
        this->function = function;
        adapter = this;
        updateData();
    }

    size_t getCountInputPins() const { return function->functionData.InputArguments.size(); }
    SharedReference<View> getInputPin(size_t index)
    {
        SharedReference<ValuePin> pin = Create<ValuePin>();
        pin->label->setText(function->functionData.InputArguments[index].Name);
        pin->type = function->functionData.InputArguments[index].Type.Name;
        pin->setType(UI::PinType::Input);
        return pin;
    }
    size_t getCountOutputPins() const { return function->functionData.OutputArguments.size(); }
    SharedReference<View> getOutputPin(size_t index)
    {
        SharedReference<ValuePin> pin = Create<ValuePin>();
        pin->label->setText(function->functionData.OutputArguments[index].Name);
        pin->type = function->functionData.OutputArguments[index].Type.Name;
        pin->setType(UI::PinType::Output);
        return pin;
    }
    SharedReference<View> getContent() { return nullptr; }
};

class MaterialPreview : public Viewport
{
    Graphics::AForwardRenderer renderer;
    APerspectiveCamera camera;
    //SharedReference<ASpace> space = new ASpace(forwardRenderer, camera);
    SharedReference<PreviewMaterial> material = Create<PreviewMaterial>();

    SharedReference<Graphics::Mesh> mesh;
    
    Math::Transform t;

public:

    enum PreviewType
    {
        Plain,
        Box,
        Sphere,
    };

    PreviewType previewType = Sphere;

    using Super = Viewport;

    MaterialPreview()
    {
        reloadMesh();

        auto recognizer = Create<RotationRecognizer>();
        recognizer->rotationUpdated = [&](const Math::Quaternion &rotation) {
            t.Rotation = rotation;
            //t.Rotation = Math::Quaternion::getZYXEulerRotation(Math::clamp(event.getPoint().Y - getSize().getHalfY(), -90.0f, 90.0f), -event.getPoint().X - getSize().getHalfX(), 0.0f);
        };
        addGestureRecognizer(recognizer);

        //spaces.append(space);

        Math::IntegerVector size{ 100, 100, 3 };
        Array<uint8_t> buffer;
        buffer.resize(size.getArea3());
        for (size_t y = 0; y < size.Y; ++y)
        {
            for (size_t x = 0; x < size.X; ++x)
            {
                buffer[y * size.x * size.z + x * size.z + 0] = 255 * Math::FloatType(x) / size.x;
                buffer[y * size.x * size.z + x * size.z + 1] = 255 * Math::FloatType(y) / size.y;
                buffer[y * size.x * size.z + x * size.z + 2] = 0;
            }
        }

        APixmap p;
        p.setBuffer(buffer, size, APixmapDataFormat::RGB);

        Graphics::Texture *texture = Create<Graphics::Texture>();
        texture->setPixmap(p);
        texture->load();

        material = Create<PreviewMaterial>();
        material->Textures["ColorMap"] = Lava_005_COLOR;
        material->Textures["DisplacementMap"] = Lava_005_DISP;
        material->Textures["AmbientOcclusionMap"] = Lava_005_OCC;
    }

    void setMaterialShaders(const String &vertexShader, const String &fragmentShader)
    {
        material->unload();
        material->vertexShader = vertexShader;
        material->fragmentShader = fragmentShader;
        material->load();
    }

    void reloadMesh()
    {
        switch (previewType)
        {
        case Plain:
            mesh = Graphics::generatePlain({ 256, 256 }, { 1 / 256.f, 1 / 256.f });
            break;
        case Box:
            mesh = Graphics::generateBox();
            break;
        default:
            mesh = Graphics::generateSphere2(0.5f, { 256, 256 });
            break;
        }
        mesh->load();
    }

    void onDrawContent(AUpdateEvent &event) override
    {
        Super::onDrawContent(event);

        if (!material->isLoaded())
        {
            material->load();
        }

        if (!material->isLoaded())
        {
            setVisible(false);
            return;
        }

        t.Position = Math::Vector{ 0, 0, -100, 0 } + getSize().getXY<Math::Vector>() / 2;

        material->ModelViewProjectionMatrix = Math::Matrix::getScale3(getSize().getYYY<Math::Vector>()) * t.getMatrix() * getGlobalMatrix() * ACamera::getCurrentCamera()->getMatrix();
        Graphics::GraphicsContext::getCurrent().draw(mesh, material);
    }
};

namespace MaterialFunctions
{

class Float : public MaterialF
{
public:
    float value;
    String generateShader(const Array<String> &paramaters) const override { return String::number(value); }
};

class Vector2 : public MaterialF
{
public:
    float value[2];
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("vec2({}, {})", value[0], value[1]); }
};

class Vector3 : public MaterialF
{
public:
    float value[3];
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("vec3({}, {}, {})", value[0], value[1], value[2]); }
};

class Vector4 : public MaterialF
{
public:
    float value[4];
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("vec4({}, {}, {}, {})", value[0], value[1], value[2], value[3]); }
};

class RandomFloat : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return String::number((rand() % 255) / 255.0f); }
};

class RandomVector2 : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("vec2({}, {})", (rand() % 255) / 255.0f, (rand() % 255) / 255.0f); }
};

class RandomVector3 : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("vec3({}, {}, {})", (rand() % 255) / 255.0f, (rand() % 255) / 255.0f, (rand() % 255) / 255.0f); }
};

class RandomVector4 : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("vec4({}, {}, {}, {})", (rand() % 255) / 255.0f, (rand() % 255) / 255.0f, (rand() % 255) / 255.0f, (rand() % 255) / 255.0f); }
};

class Parameter : public MaterialF
{
public:
    String type;
    String name;
    String generateShader(const Array<String> &paramaters) const override { return name; }
};

class Time : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return "Time"; }
};

class Texture : public MaterialF
{
public:
    String sampler = "u_ColorMap";
    String generateShader(const Array<String> &paramaters) const override { return fmt::format("texture({}, {})", sampler, paramaters[0]); }
};

class Function : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return functionData.Identifier + "(" + String::join(paramaters, ", ") + ")"; }
};

class Add : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return String::join(paramaters, '+'); }
};

class Subtract : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return String::join(paramaters, '-'); }
};

class Multiply : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return String::join(paramaters, '*'); }
};

class Divide : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return String::join(paramaters, '/'); }
};

class HotFix : public MaterialF
{
public:
    String generateShader(const Array<String> &paramaters) const override { return "vec4(" + paramaters[0] + ", 1.0)"; }
};

}

class MaterialEditor : public LegacyClassGen::GraphEditor
{
    SharedReference<MaterialPreview> preview = Create<MaterialPreview>();
    SharedReference<ValuePin> sourcePin;
    SharedReference<ValuePin> targetPin;
public:

    using Super = GraphEditor;

    struct MaterialParameter
    {
        String type;
        String name;
    };

    Array<MaterialParameter> vertexData;
    Array<MaterialParameter> parameters;

    class FunctionViewer : public ListView, public ItemAdapter
    {
    public:
        Array<SharedReference<MaterialF>> functions;

        ADelegate<void(const SharedReference<MaterialF> &function)> functionCreated;
        
        void onLoad(ALoadEvent &event)
        {
            Super::onLoad(event);
            setAdapter(this);
        }
        
        SizeType getCountItems(const AObject &sender) const override { return functions.size(); }
        SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override
        { 
            UI::Label *label = CreateShared<UI::Label>();
            label->setText(functions[index]->functionData.Identifier);
            return label;
        }

        void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index) override
        {
            functionCreated(functions[index]);
        }
    };

    SharedReference<FunctionViewer> functionsViewer = Create<FunctionViewer>();

    Map<String, SharedReference<MaterialF>> functions;

    StringsHashMap types = {
        { "Float", "float" },
        { "Vector2", "vec2" },
        { "Vector3", "vec3" },
        { "Vector4", "vec4" },
        { "Matrix", "mat4" },
        { "Texture", "sampler2D" },
    };

    void registerVertexData(const MaterialParameter &parameter)
    {
        SharedReference<MaterialFunctions::Parameter> function = Create<MaterialFunctions::Parameter>();
        function->type = parameter.type;
        function->name = "v_" + parameter.name;
        function->functionData.Identifier = parameter.name;
        function->functionData.OutputArguments = { LegacyClassGen::Parameter{ parameter.type, "Value" } };

        functions.insert({ parameter.name, function });
        vertexData.append(parameter);
    }

    void registerParameter(const MaterialParameter &parameter)
    {
        if (parameter.type == "Texture")
        {
            SharedReference<MaterialFunctions::Texture> function = Create<MaterialFunctions::Texture>();
            function->sampler = "u_" + parameter.name;
            function->functionData.Identifier = parameter.name;
            function->functionData.InputArguments = { LegacyClassGen::Parameter{ "Vector2", "UV" } };
            function->functionData.OutputArguments = { LegacyClassGen::Parameter{ "Vector3", "Color" } };
            functions.insert({ parameter.name, function });
        }
        else
        {
            SharedReference<MaterialFunctions::Parameter> function = Create<MaterialFunctions::Parameter>();
            function->type = parameter.type;
            function->name = "u_" + parameter.name;
            function->functionData.Identifier = parameter.name;
            function->functionData.OutputArguments = { LegacyClassGen::Parameter{ parameter.type, "Value" } };
            functions.insert({ parameter.name, function });
        }
        parameters.append(parameter);
    }

    template<typename Type>
    void registerFunction(const String &identifier, const Array<LegacyClassGen::Parameter> &input, const Array<LegacyClassGen::Parameter> &output)
    {
        SharedReference<Type> function = Create<Type>();
        function->functionData.Identifier = identifier;
        function->functionData.InputArguments = input;
        function->functionData.OutputArguments = output;

        functions.insert({ identifier, function });
    }

    bool hasNodeData(const String &identifier) const
    {
        auto it = std::find_if(nodesData.begin(), nodesData.end(), [&](const auto &n) { return n.Identifier == identifier; });
        return it != nodesData.end();
    }

    const LegacyClassGen::NodeData &findNodeData(const String &identifier) const
    {
        auto it = std::find_if(nodesData.begin(), nodesData.end(), [&](const auto &n) { return n.Identifier == identifier; });
        return *it;
    }

    String processNode(const LegacyClassGen::NodeData &node, String &code)
    {
        const SharedReference<MaterialF> &f = findMaterialFunction(node);

        Array<String> parameters;
        parameters.resize(f->functionData.InputArguments.size());
        size_t i = 0;
        for (const LegacyClassGen::Parameter &p : f->functionData.InputArguments)
        {
            auto c = findConnection(node, p.Name);
            if (c)
            {
                auto cn = findConnectedNode(node, *c);
                parameters[i] = processNode(*cn, code);

                ALogMessage("", "Process %s.%s(%s) connected to %s (%s)", node.Identifier, p.Name, c->Source, cn->Identifier, c->Target);
            }
            else
            {
                ALogMessage("", "Use default value for %s.%s", node.Identifier, p.Name);
                parameters[i] = "1.0";
            }
            ++i;
        }

        return f->generateShader(parameters);
    }

    const UI::Connection *findConnection(const LegacyClassGen::NodeData &node, const String &parameter) const
    {
        auto it = std::find_if(node.Connections.begin(), node.Connections.end(), [&](const UI::Connection &c) {
            return c.Source == parameter;
        });

        return it != node.Connections.end() ? &(*it) : nullptr;
    };

    const LegacyClassGen::NodeData *findConnectedNode(const LegacyClassGen::NodeData &node, const UI::Connection &connection) const
    {
        auto it = std::find_if(nodesData.begin(), nodesData.end(), [&](const LegacyClassGen::NodeData &n) {
            return n.Identifier == connection.Target.split('/')[0];
        });

        return it != nodesData.end() ? &(*it) : nullptr;
    };

    const SharedReference<MaterialF> &findMaterialFunction(const LegacyClassGen::NodeData &node) const
    {
        String typeName;
        node.Data.read("Function", typeName);
        return functions.at(typeName);
    }

    String generateVertexShader()
    {
        String code;
        for (const MaterialParameter &parameter : vertexData)
        {
            code.append("attribute " + types[parameter.type] + " a_" + parameter.name + ";\r\n");
            code.append("varying " + types[parameter.type] + " v_" + parameter.name + ";\r\n");
        }
        for (const MaterialParameter &parameter : parameters)
        {
            code.append("uniform " + types[parameter.type] + " u_" + parameter.name + ";\r\n");
        }

        code.append("void VertexShader(vec4 position) { gl_Position = position; }\r\n");
        code.append("void main() {\r\n");

        for (const MaterialParameter &parameter : vertexData)
        {
            code.append("v_" + parameter.name + " = a_" + parameter.name + ";\r\n");
        }
        code.append(processNode(findNodeData("VertexShader"), code) + ";\r\n");
        code.append("}\r\n");
        ALogMessage("", "VertexShader:\r\n\r\n%s\r\n", code);
        return code;
    }

    String generateFragmentShader()
    {
        String code;
        for (const MaterialParameter &parameter : parameters)
        {
            code.append("uniform " + types[parameter.type] + " u_" + parameter.name + ";\r\n");
        }
        for (const MaterialParameter &parameter : vertexData)
        {
            code.append("varying " + types[parameter.type] + " v_" + parameter.name + ";\r\n");
        }
        code.append("void FragmentShader(vec3 color, float opacity) { gl_FragColor = vec4(color, opacity); }\r\n");
        code.append("void main() {\r\n");
        code.append(processNode(findNodeData("FragmentShader"), code) + ";\r\n");
        code.append("}\r\n");
        ALogMessage("", "FragmentShader:\r\n\r\n%s\r\n", code);
        return code;
    }

    MaterialEditor()
    {

        registerFunction<MaterialFunctions::Float>("Float", {}, { LegacyClassGen::Parameter{ "Float", "Value" } });
        registerFunction<MaterialFunctions::Vector2>("Vector2", {}, { LegacyClassGen::Parameter{ "Vector2", "Value" } });
        registerFunction<MaterialFunctions::Vector3>("Vector3", {}, { LegacyClassGen::Parameter{ "Vector3", "Value" } });
        registerFunction<MaterialFunctions::Vector4>("Vector4", {}, { LegacyClassGen::Parameter{ "Vector4", "Value" } });

        registerFunction<MaterialFunctions::RandomFloat>("RandomFloat", {}, { LegacyClassGen::Parameter{ "Float", "Value" } });
        registerFunction<MaterialFunctions::RandomVector2>("RandomVector2", {}, { LegacyClassGen::Parameter{ "Vector2", "Value" } });
        registerFunction<MaterialFunctions::RandomVector3>("RandomVector3", {}, { LegacyClassGen::Parameter{ "Vector3", "Value" } });
        registerFunction<MaterialFunctions::RandomVector4>("RandomVector4", {}, { LegacyClassGen::Parameter{ "Vector4", "Value" } });

        registerFunction<MaterialFunctions::Multiply>("Transform", { LegacyClassGen::Parameter{ "Matrix", "Matrix" }, LegacyClassGen::Parameter{ "Vector4", "Vector" }, }, { LegacyClassGen::Parameter{ "Vector4", "Vector" }, });
        registerFunction<MaterialFunctions::Multiply>("Multiply", { LegacyClassGen::Parameter{ "Vector3", "A" }, LegacyClassGen::Parameter{ "Vector3", "B" } }, { LegacyClassGen::Parameter{ "Vector3", "Result" } });
        registerFunction<MaterialFunctions::Divide>("Divide", { LegacyClassGen::Parameter{ "Vector3", "A" }, LegacyClassGen::Parameter{ "Vector3", "B" } }, { LegacyClassGen::Parameter{ "Vector3", "Result" } });
        registerFunction<MaterialFunctions::Add>("Add", { LegacyClassGen::Parameter{ "Vector3", "A" }, LegacyClassGen::Parameter{ "Vector3", "B" } }, { LegacyClassGen::Parameter{ "Vector3", "Result" } });
        registerFunction<MaterialFunctions::Subtract>("Subtract", { LegacyClassGen::Parameter{ "Vector3", "A" }, LegacyClassGen::Parameter{ "Vector3", "B" } }, { LegacyClassGen::Parameter{ "Vector3", "Result" } });

        registerFunction<MaterialFunctions::HotFix>("Hot-Fix :(", { LegacyClassGen::Parameter{ "Vector3", "Vector3" } }, { LegacyClassGen::Parameter{ "Vector4", "Vector4" } });

        registerVertexData({ "Vector3", "Position" });
        registerVertexData({ "Vector3", "Normal" });
        registerVertexData({ "Vector2", "UV" });

        registerParameter({ "Matrix", "ModelViewProjectionMatrix" });

        registerParameter({ "Texture", "ColorMap" });
        registerParameter({ "Texture", "DisplacementMap" });
        registerParameter({ "Texture", "AmbientOcclusionMap" });

        registerFunction<MaterialFunctions::Texture>("IlluminanceTexture", { LegacyClassGen::Parameter{ "Vector2", "UV" } }, { LegacyClassGen::Parameter{ "Float", "Color" } });
        registerFunction<MaterialFunctions::Texture>("GrayscaleTexture", { LegacyClassGen::Parameter{ "Vector2", "UV" } }, { LegacyClassGen::Parameter{ "Vector2", "Color" } });
        registerFunction<MaterialFunctions::Texture>("RGBTexture", { LegacyClassGen::Parameter{ "Vector2", "UV" } }, { LegacyClassGen::Parameter{ "Vector3", "Color" } });
        registerFunction<MaterialFunctions::Texture>("RGBATexture", { LegacyClassGen::Parameter{ "Vector2", "UV" } }, { LegacyClassGen::Parameter{ "Vector4", "Color" } });

        registerFunction<MaterialFunctions::Function>("VertexShader", { LegacyClassGen::Parameter{ "Vector4", "Position" } }, {});
        registerFunction<MaterialFunctions::Function>("FragmentShader", { LegacyClassGen::Parameter{ "Vector3", "Color" }, LegacyClassGen::Parameter{ "Float", "Opacity" } }, {});
        //registerFunction<MaterialFunctions::Float>("PRBMaterial", { { "", "Color" }, "Metallic", "Roughness", "Normal", "Occlusion", "Emission" }, {});

    }

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        SharedReference<UI::TextButton> button = CreateShared<UI::TextButton>();
        button->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
            preview->setMaterialShaders(generateVertexShader(), generateFragmentShader());
            preview->setVisible(true);
        });
        button->setSize({ 90, 20 });
        button->setSizePolicy(SizePolicy::Fixed);
        button->setText("Recompile");
        preview->addView(button);

        /*preview->setSizePolicy(SizePolicy::Fixed);
        preview->setSize(Math::IntegerVector{ 200, 200 });
        insertView(0, preview);

        auto data = getData();
        data.insert(data.begin(), {});
        setData(data);*/
        
        auto checkSourcePin = [this](const SharedReference<View> &view) {
            sourcePin = view.cast<ValuePin>();
            return sourcePin.isValid();
        };
        auto checkDestinationPin = [this](const SharedReference<View> &view) {
            targetPin = view.cast<ValuePin>();
            return targetPin
                && targetPin != sourcePin
                && targetPin->type
                && targetPin->type == sourcePin->type;
            return nodes.find_first_of(view.as<UI::NodeView>()) != InvalidIndex;
        };

        linking->setTouchModifier(ATouchModifier::Undefined);
        linking->sourcePredicate = checkSourcePin;
        linking->targetPredicate = checkDestinationPin;
        linking->targetPredicate = checkDestinationPin;
        linking->linked = [this](const SharedReference<View> &sourceView, const SharedReference<View> &targetView) {

            SharedReference<ValuePin> sourcePin = sourceView.as<ValuePin>();
            SharedReference<ValuePin> targetPin = targetView.as<ValuePin>();
            SharedReference<PinNodeView> sourceNode = sourcePin->getParentNode();
            SharedReference<PinNodeView> targetNode = targetPin->getParentNode();

            if (sourcePin->getType() == targetPin->getType())
            {
                return;
            }

            auto createConnection = [this](
                const SharedReference<PinNodeView> &sourceNode, const SharedReference<ValuePin> &sourcePin,
                const SharedReference<PinNodeView> &targetNode, const SharedReference<ValuePin> &targetPin)
            {
                UI::Connection connection;
                connection.Source = sourcePin->label->getText();
                connection.Target = targetNode->getIdentifier() + "/" + targetPin->label->getText();
                size_t nodeIndex = graphView->getNodeIndexForItemView(*sourceNode);
                connections.append(sourceNode->connect(sourceNode, targetNode, connection));
                nodesData[nodeIndex].Connections.append(std::move(connection));
            };

            if (sourcePin->getType() == UI::PinType::Input)
            {
                createConnection(sourceNode, sourcePin, targetNode, targetPin);
            }
            else
            {
                createConnection(targetNode, targetPin, sourceNode, sourcePin);
            }

            graphView->notifyInsertConnections(connections.size() - 1);
        };

        FlexBox *fb = Create<FlexBox>();
        fb->setDirection(UI::Direction::Vertical);
        fb->setSizePolicy(SizePolicy::ContentWrapped, SizePolicy::Expanded);
        fb->setData({ {}, {} });
        insertView(0, fb);

        functionsViewer->functions.reserve(functions.size());
        for (auto &pair : functions)
        {
            functionsViewer->functions.append(pair.second);
        }
        functionsViewer->notifyUpdateAllItems();

        preview->setSizePolicy(SizePolicy::Fixed);
        preview->setSize(Math::IntegerVector{ 300, 200 });
        fb->addView(preview);

        functionsViewer->functionCreated = [&](const SharedReference<MaterialF> &function) {
            LegacyClassGen::NodeData nodeData;
            nodeData.Data.insert("Function", function->functionData.Identifier);
            nodeData.Identifier = getNextName(function->functionData.Identifier, [&](const String &name) {
                return std::find_if(nodesData.begin(), nodesData.end(), [&](const LegacyClassGen::NodeData &value) { return name == value.Identifier; }) == nodesData.end();
            });
            auto node = createNode(nodeData);
            node->identifier = nodeData.Identifier;
            nodes.append(node);
            nodesData.append(std::move(nodeData));
            graphView->notifyInsertNodes(nodes.size() - 1);
        };
        functionsViewer->setSizePolicy(SizePolicy::Fixed, SizePolicy::Expanded);
        functionsViewer->setSize(Math::IntegerVector{ 300, 0 });
        fb->addView(functionsViewer);


        auto data = getData();
        data.insert(data.begin(), {});
        setData(data);

        /*SharedReference<MenuView> menuView = Create<MenuView>();
        menuView->addAction(MenuAction{ "Add state...", [this](TapGestureEvent &event) {
            LegacyClassGen::NodeData data;
            data.Identifier = getNextName("Function", [&](const String &name) {
                return std::find_if(nodesData.begin(), nodesData.end(), [&](const LegacyClassGen::NodeData &value) { return name == value.Identifier; }) == nodesData.end();
            });
            nodes.append(createNode(data));
            nodesData.append(std::move(data));
            graphView->notifyInsertNodes(nodesData.size() - 1);
        } });
        AttachMenuToView(graphView, menuView);*/

        SharedReference<UI::NodeSearchView> nodeSearchView = CreateShared<UI::NodeSearchView>();
        AttachMenuToView(graphView, nodeSearchView);
    }

    Array<String> parentMaterialNodes = {
        "FragmentShader",
        "VertexShader",
    };

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        Super::onLoad(data, type);

        int32_t offset = 0;
        for (const String &parentMaterialNode : parentMaterialNodes)
        {
            if (!hasNodeData(parentMaterialNode))
            {
                LegacyClassGen::NodeData nodeData;
                nodeData.Data.insert("Function", parentMaterialNode);
                nodeData.Identifier = getNextName(parentMaterialNode, [&](const String &name) {
                    return std::find_if(nodesData.begin(), nodesData.end(), [&](const LegacyClassGen::NodeData &value) { return name == value.Identifier; }) == nodesData.end();
                });
                auto node = createNode(nodeData);
                node->setPosition({ 0, offset });
                offset += node->getContentSize().Y;
                nodes.append(node);
                nodesData.append(std::move(nodeData));
                //graphView->notifyInsertNodes(nodesData.size() - 1);
                graphView->notifyUpdateAllItems();
            }
        }

        preview->setMaterialShaders(generateVertexShader(), generateFragmentShader());
    }

    SharedReference<UI::NodeView> createNode(const LegacyClassGen::NodeData &data) override
    {
        SharedReference<MaterialNodeView> nodeView = Create<MaterialNodeView>();
        String functionIdentifier;
        if (data.Data.read("Function", functionIdentifier))
        {
            auto it = functions.find(functionIdentifier);// std::find_if(functions.begin(), functions.end(), [&](const LegacyClassGen::MaterialFunction &function) { return function.Identifier == functionIdentifier; });
            if (it != functions.end())
            {
                nodeView->setData(data, it->second);
            }
        }
        nodeView->setName(functionIdentifier);
        nodeView->setSize(nodeView->getContentSize());
        //nodeView->setSizePolicy(SizePolicy::Fixed);
        //nodeView->setSize({ 200, 80 });

        /*DraggingGestureRecognizer *recognizer = new DraggingGestureRecognizer();
        recognizer->moveViewToFront = false;
        recognizer->gridSize = 1;
        nodeView->addGestureRecognizer(recognizer);*/

        AttachMenuToView(nodeView, createMenu(nodeView));

        return nodeView;
    }

    SharedReference<MenuView> createMenu(const AWeakPointer<MaterialNodeView> &item)
    {
        SharedReference<MenuView> menuView = Create<MenuView>();
        /*menuView->addAction(MenuAction{ "Add view...", [this, item](TapGestureEvent &event) {

            Node* newItem = new Node{ "NewView" };
            newItem->type = "UI.View";
            newItem->parent = item;

            SharedReference<NodeView> view = createNode(newItem, item->view.data());
            view->setSize(Math::IntegerVector{ 100, 100 });
            newItem->view = view;

            newItem->updateInstance();

            item->items.append(newItem);
            if (item->treeitem)
            {
                if (!item->treeitem->getExpandable())
                {
                    item->treeitem->setExpandable(true);
                }
                if (item->isExpanded)
                {
                    outliner->notifyUpdateChildren(item);
                }
            }
        } });*/
        menuView->addAction(MenuAction{ "Disconnect", [this, item](TapGestureEvent &event) {
            size_t i = graphView->getNodeIndexForItemView(*item);
            LegacyClassGen::NodeData &data = nodesData[i];

            for (size_t cIndex = 0; cIndex < connections.size(); ++cIndex)
            {
                const SharedReference<UI::Line> &c = connections[cIndex];
                for (const UI::NodeView::ConnectionInfo &ci : item->connections)
                {
                    if (ci.view == c)
                    {
                        ALogMessage("", "Delete connection %s at %d", ci.data.Target, cIndex);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --cIndex;
                        break;
                    }
                }
            }
            item->connections.clear();
            data.Connections.clear();

            SizeType j = 0;
            for (const SharedReference<UI::NodeView> &n : nodes)
            {
                for (size_t ni = 0; ni < n->connections.size(); ++ni)
                {
                    const UI::NodeView::ConnectionInfo &ci = n->connections[ni];
                    if (ci.data.Target.split('/')[0] == data.Identifier)
                    {
                        size_t cIndex = graphView->getConnectionIndexForItemView(*ci.view);
                        ALogMessage("", "Delete connection %s from %s at %d", ci.data.Target, n->getIdentifier(), cIndex);
                        n->connections.erase(n->connections.begin() + ni);
                        nodesData[j].Connections.erase(nodesData[j].Connections.begin() + ni);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --ni;
                    }
                }
                ++j;
            }
        } });

        menuView->addAction(MenuAction{ "Remove", [this, item](TapGestureEvent &event) {

            size_t i = graphView->getNodeIndexForItemView(*item);
            const LegacyClassGen::NodeData &data = nodesData[i];

            for (size_t cIndex = 0; cIndex < connections.size(); ++cIndex)
            {
                const SharedReference<UI::Line> &c = connections[cIndex];
                for (const UI::NodeView::ConnectionInfo &ci : item->connections)
                {
                    if (ci.view == c)
                    {
                        ALogMessage("", "Delete connection %s at %d", ci.data.Target, cIndex);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --cIndex;
                        break;
                    }
                }
            }

            SizeType j = 0;
            for (const SharedReference<UI::NodeView> &n : nodes)
            {
                for (size_t ni = 0; ni < n->connections.size(); ++ni)
                {
                    const UI::NodeView::ConnectionInfo &ci = n->connections[ni];
                    if (ci.data.Target.split('/')[0] == data.Identifier)
                    {
                        size_t cIndex = graphView->getConnectionIndexForItemView(*ci.view);
                        ALogMessage("", "Delete connection %s from %s at %d", ci.data.Target, n->getIdentifier(), cIndex);
                        n->connections.erase(n->connections.begin() + ni);
                        nodesData[j].Connections.erase(nodesData[j].Connections.begin() + ni);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --ni;
                    }
                }
                ++j;
            }

            ALogMessage("", "Delete %s at %d", data.Identifier, i);
            nodesData.erase(nodesData.begin() + i);
            nodes.erase(nodes.begin() + i);
            graphView->notifyRemoveNodes(i);
        } });
        /*menuView->addAction(MenuAction{ "Clear", [this, item](TapGestureEvent &event) {
            for (auto &child : item->items)
            {
                child->view->removeFromParent();
            }
            item->items.clear();
            if (item->treeitem)
            {
                item->treeitem->setExpandable(false);
                outliner->notifyUpdateChildren(item);
            }
        } });*/

        return menuView;
    }
};

}
