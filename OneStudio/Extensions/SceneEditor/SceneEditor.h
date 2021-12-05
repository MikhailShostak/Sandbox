#pragma once

#include "Includes/Editor.gen.h"

#include "RotationRecognizer.h"

namespace UI
{

class Viewport2 : public CanvasView
{
public:

    SharedReference<Graphics::ModelMaterial> material = new Graphics::ModelMaterial();
    using Super = CanvasView;

    Array<SharedReference<ASpace>> spaces;

    SharedReference<Graphics::Mesh> mesh = Graphics::generateSphere2(0.5f, { 32, 32 });

    Viewport2()
    {

    }

    void onDrawContent(AUpdateEvent &event) override
    {
        Super::onDrawContent(event);

        if (!mesh->isLoaded())
        {
            mesh->load();
        }

        if (!material->isLoaded())
        {
            material->load();
        }

        for (auto &space : spaces)
        {
            space->getCamera()->resolution = getSize();
            space->update(event);
        }

        material->ModelViewProjectionMatrix = /*Math::Matrix::getScale3(getSize().getYYY<Math::Vector>()) * t.getMatrix() * getGlobalMatrix() **/ ACamera::getCurrentCamera()->getMatrix();
        Graphics::GraphicsContext::getCurrent().draw(mesh, material);
    }
};


class ViewportContainer : public Overlay
{
    SharedReference<ImageView> XAxis = new ImageView();
    SharedReference<ImageView> YAxis = new ImageView();
    SharedReference<ImageView> ZAxis = new ImageView();
    SharedReference<ImageView> grid = new ImageView();

    SharedReference<APerspectiveCamera> camera = new APerspectiveCamera();
    
public:
    using Super = Overlay;

    SharedReference<Viewport2> viewport = new Viewport2();

    ViewportContainer()
    {
        viewport->setCamera(camera);
        //viewport->getCamera()->transform.Position = Math::Vector{ 0, -100, 0 };

        RotationRecognizer* rotationRecognizer = new RotationRecognizer();
        rotationRecognizer->rotationUpdated = [&](const Math::Quaternion &rotation) {
            viewport->getCamera()->transform.Rotation = rotation;
        };
        addGestureRecognizer(rotationRecognizer);

        setData({ OverlayData{ {}, Core::Alignment::Start, Core::Alignment::Start } });
        //viewport->setSize({ 0, 0 });
        viewport->setSizePolicy(SizePolicy::Expanded);
        addView(viewport);

        Math::IntegerVector size{ 200, 200, 2 };
        APixmap pixmap;
        pixmap.setBuffer(Array<uint8_t>(size.getArea3()), size, APixmapDataFormat::GrayAlpha);

        drawCheck(pixmap, 1, 0, AColor::fromBytes(0.0f, 0.0f), AColor::fromBytes(0.0f));

        drawGrid(pixmap, 10, 0, AColor(0.17f, 1.0f), Blending::Replace);
        drawGrid(pixmap, 100, 0, AColor(0.15f, 1.0f), Blending::Replace);

        SharedReference<Graphics::Texture> texture = new Graphics::Texture();
        texture->setPixmap(pixmap);
        texture->setFiltration(Graphics::TextureFiltration::Nearest);
        texture->setWrapping(Graphics::TextureWrapping::TiledWrapping);
        texture->load();

        grid->setSize({ 2000, 2000 });
        grid->setSizePolicy(SizePolicy::Fixed);
        grid->setImage(texture);
        grid->setRotation(Math::Quaternion::getXRotation(-90));
        viewport->addView(grid);

        XAxis->setImage(Graphics::Texture::getWhiteTexture());
        XAxis->setColor(AColor::RedColor());
        XAxis->setSize({ 2000, 1 });
        viewport->addView(XAxis);

        YAxis->setImage(Graphics::Texture::getWhiteTexture());
        YAxis->setColor(AColor::GreenColor());
        YAxis->setSize({ 1, 2000 });
        viewport->addView(YAxis);

        ZAxis->setImage(Graphics::Texture::getWhiteTexture());
        ZAxis->setColor(AColor::BlueColor());
        ZAxis->setRotation(grid->getRotation());
        ZAxis->setSize({ 1, 2000 });
        viewport->addView(ZAxis);
    }

    void onLayout(AUpdateEvent &event) override
    {
        Super::onLayout(event);

        camera->resolution = getSize();

        //TODO: should be replace with adjusted pivot...
        auto s = getSize().getHalf2();

        auto s2 = grid->getSize().getHalf2();
        grid->setPosition(s + Math::Vector{ -s2.X, 0, -s2.Y, });

        s2 = XAxis->getSize().getHalf2();
        XAxis->setPosition(s + Math::Vector{ -s2.X, 0 });

        s2 = YAxis->getSize().getHalf2();
        YAxis->setPosition(s + Math::Vector{ 0, -s2.Y });

        s2 = ZAxis->getSize().getHalf2();
        ZAxis->setPosition(s + Math::Vector{ 0, 0, -s2.Y });
    }
};

class SceneEditor : public FlexBox, public LegacyClassGen::Editor
{
    SharedReference<ViewportContainer> sceneViewport = new ViewportContainer();
public:
    SceneEditor()
    {
        sceneViewport->setSizePolicy(SizePolicy::Expanded);
        addView(sceneViewport);
        setData({ {} });
    }
};

}
