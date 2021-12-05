#include "AWindow.h"

#include <Console.pch.hpp>

#include "MetaObject.h"

AStaticRun(AWindowMetaObject)
{
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<AWindow>();
    object.baseObject = &manager.getMetaObject<AObject>();
    object.registerMetaProperty<AWindow, AColor>("BackgroundColor", &AWindow::getBackgroundColor, &AWindow::setBackgroundColor);
    object.registerMetaProperty<AWindow, Array<::SharedReference<ASpace>>>("Spaces", &AWindow::getSpaces, &AWindow::setSpaces);
    object.registerMetaProperty<AWindow, Math::IntegerRectangle>("Geometry", &AWindow::getGeometry, &AWindow::setGeometry);
    object.registerMetaProperty<AWindow, String>("Title", &AWindow::getTitle, &AWindow::setTitle);
    object.registerMetaProperty<AWindow, bool>("Visible", &AWindow::getVisible, &AWindow::setVisible);
    object.registerMetaProperty<AWindow, WindowFlags>("Flags", &AWindow::getFlags, &AWindow::setFlags);
}

#include "ASpace.h"
#include "AWindowEvents.h"

#include "Canvas.h"

/*#include "Includes/ViewWindow.gen.h"
#include "Includes/RelativeLayout.gen.h"
#include "Includes/Label.gen.h"
#include "Includes/TextField.gen.h"
#include "SuggestionsModel.h"

//TODO: remove dependency on UI framework
class ConsoleController : public AObject
{
    bool enabled = false;
    AWindow *window = nullptr;
public:
    UI::PerspectiveCamera camera;
    Legacy::Graphics::AForwardRenderer renderer;

    ::SharedReference<UI::BorderImageView> backgroundView = Create<UI::BorderImageView>();
    ::SharedReference<UI::Label> historyView = Create<UI::Label>();
    ::SharedReference<UI::TextField> inputView = Create<UI::TextField>();

    ::SharedReference<ASpace> consoleSpace = Create<ASpace>(renderer, camera);
    ::SharedReference<AEntity> consoleEntity = Create<AEntity>();
    ::SharedReference<UI::Component> consoleComponent = Create<UI::Component>(*consoleEntity, true);
    ::SharedReference<UI::SuggestionsComponent> suggestionsComponent = Create<UI::SuggestionsComponent>();

    ConsoleController(AWindow *window):window(window)
    {
        auto commands = Console::getInstance().getCommands();
        for (const auto command : commands)
        {
            suggestionsComponent->items.append(command.first);
        }
        suggestionsComponent->upDirection = true;
        suggestionsComponent->addView(*inputView);

        consoleEntity->addComponent(consoleComponent);
        consoleSpace->addEntity(consoleEntity);

        //Core::FontEngine::getInstance().load(getAsset("consola"));
        //Core::Font ConsoleFont("Consolas", "Regular", 12);

        auto &view = consoleComponent->getView();

        historyView->setSizePolicy(UI::SizePolicy::Expanded);
        historyView->setText("Console loaded");
        //historyView->setFont(ConsoleFont);
        //inputView->setFont(ConsoleFont);

        backgroundView->setSizePolicy(UI::SizePolicy::Expanded);
        backgroundView->setColor(AColor::fromHex(0x55080808));
        
        ::SharedReference<UI::RelativeLayout> relativeLayout = new UI::RelativeLayout();
        relativeLayout->addConstraint(*backgroundView, UI::ConstraintAnchor::Left, *view, UI::ConstraintAnchor::Left, 4);
        relativeLayout->addConstraint(*backgroundView, UI::ConstraintAnchor::Bottom, *view, UI::ConstraintAnchor::Bottom, 4);
        relativeLayout->addConstraint(*backgroundView, UI::ConstraintAnchor::Right, *view, UI::ConstraintAnchor::Right, 4);
        relativeLayout->addConstraint(*backgroundView, UI::ConstraintAnchor::Top, *view, UI::ConstraintAnchor::Top, 4);

        relativeLayout->addConstraint(*inputView, UI::ConstraintAnchor::Left, *view, UI::ConstraintAnchor::Left, 8);
        relativeLayout->addConstraint(*inputView, UI::ConstraintAnchor::Bottom, *view, UI::ConstraintAnchor::Bottom, 8);
        relativeLayout->addConstraint(*inputView, UI::ConstraintAnchor::Right, *view, UI::ConstraintAnchor::Right, 8);

        relativeLayout->addConstraint(*historyView, UI::ConstraintAnchor::Left, *view, UI::ConstraintAnchor::Left, 8);
        relativeLayout->addConstraint(*historyView, UI::ConstraintAnchor::Top, *view, UI::ConstraintAnchor::Top, 8);
        relativeLayout->addConstraint(*historyView, UI::ConstraintAnchor::Bottom, *inputView, UI::ConstraintAnchor::Top, 8);
        relativeLayout->addConstraint(*historyView, UI::ConstraintAnchor::Right, *view, UI::ConstraintAnchor::Right, 8);
        view->setLayout(relativeLayout);
        view->addView(backgroundView);
        view->addView(historyView);
        view->addView(inputView);

        //renderer.debugName = "UI";
        camera.fieldOfView = 45.0f;
        camera.farClipping = 100;
        camera.nearClipping = 0.1;

        renderer.setDepthFunction(Legacy::Graphics::API::DepthFunction::LessOrEqual);

        ARegisterEventCallback(onResize);
        ARegisterEventCallback(onKeyPress);
        ARegisterEventCallback(onKeyRelease);
    }

    void onResize(UIResizeEvent &event)
    {
        auto &view = consoleComponent->getView();
        view->setSize(event.getValue());
    }

    void onKeyPress(AWindowKeyPressEvent &event)
    {
        if (event.getKey() == 192) // ~
        {
            if (enabled)
            {
                enabled = false;
                window->removeSpace(consoleSpace);
                window->removeFocus(*inputView);
            }
            else
            {
                enabled = true;
                window->addSpace(consoleSpace);
                window->setFocus(*inputView);
            }

            event.accept();
            return;
        }

        if (enabled) //enter
        {
            switch (event.getKey())
            {
            case 38: //up arrow
                inputView->setText(Console::getInstance().getPreviousCommand());
                break;
            case 40: //down arrow
                inputView->setText(Console::getInstance().getNextCommand());
                break;
            case 13: //enter
                if (inputView->getText() == "clear")
                {
                    historyView->setText(String());
                }
                else
                {
                    Console::getInstance().applyCommand(inputView->getText());
                    historyView->setText(historyView->getText() + "|" + inputView->getText());
                }
                inputView->setText(String());
                return;
            }
        }
    }

    void onKeyRelease(AWindowKeyReleaseEvent &event)
    {

    }
};*/

AWindow::AWindow()
{
    Storage::getInstance().windows.push_back(this);
    platformWindow = std::move(APlatformInstance().createWindow(*this));

    //UIApplication::getOperationDispatcher().addDelegate([this]() {
    //    console = UniqueReference<AObject>(Create<ConsoleController>(this));
    //    return AError::getEmptyError();
    //}, true);

    ARegisterEventCallback(onShow);
    ARegisterEventCallback(onHide);
    ARegisterEventCallback(onClose);
    ARegisterEventCallback(onUpdate);

    ARegisterEventCallback(onMove);
    ARegisterEventCallback(onResize);
    ARegisterEventCallback(onGeometryChange);
    ARegisterEventCallback(onTitleChange);
    ARegisterEventCallback(onFlagsChange);

    ARegisterEventCallback(onTouchDown);
    ARegisterEventCallback(onTouchMove);
    ARegisterEventCallback(onTouchUp);
    ARegisterEventCallback(onTouchWheel);

    ARegisterEventCallback(onKeyPress);
    ARegisterEventCallback(onKeyRelease);
    ARegisterEventCallback(onKeyChar);
}

AWindow::~AWindow()
{
    AUnregisterEventCallback(onKeyChar);
    AUnregisterEventCallback(onKeyRelease);
    AUnregisterEventCallback(onKeyPress);

    AUnregisterEventCallback(onTouchWheel);
    AUnregisterEventCallback(onTouchUp);
    AUnregisterEventCallback(onTouchMove);
    AUnregisterEventCallback(onTouchDown);

    AUnregisterEventCallback(onFlagsChange);
    AUnregisterEventCallback(onTitleChange);
    AUnregisterEventCallback(onGeometryChange);
    AUnregisterEventCallback(onResize);
    AUnregisterEventCallback(onMove);

    AUnregisterEventCallback(onUpdate);
    AUnregisterEventCallback(onClose);
    AUnregisterEventCallback(onHide);
    AUnregisterEventCallback(onShow);

    ArrayUtils::Remove(Storage::getInstance().windows, this);
}

const Array<::SharedReference<ASpace>> &AWindow::getSpaces() const
{
    return this->spaces;
}

void AWindow::setSpaces(const Array<::SharedReference<ASpace>> &spaces)
{
    for (auto &space : this->spaces)
    {
        ARemoveFromWindowEvent e(*this);
        space->sendEvent(e);
    }
    this->spaces = spaces;
    for (auto &space : this->spaces)
    {
        AAddToWindowEvent e(*this);
        space->sendEvent(e);
    }
}

void AWindow::addSpace(const ::SharedReference<ASpace> &space)
{
    spaces.push_back(space);
    AAddToWindowEvent e(*this);
    space->sendEvent(e);
}

void AWindow::insertSpace(const ::SharedReference<ASpace> &space, size_t index)
{
    spaces.insert(spaces.begin() + index, space);
    AAddToWindowEvent e(*this);
    space->sendEvent(e);
}

void AWindow::removeSpace(const ::SharedReference<ASpace> &space)
{
    ArrayUtils::Remove(spaces, space);
    ARemoveFromWindowEvent e(*this);
    space->sendEvent(e);
}

void AWindow::show() { setVisible(true); }
void AWindow::hide() { setVisible(false); }
void AWindow::close() { ACloseEvent e(*this);  onClose(e); }

const Math::IntegerRectangle &AWindow::getGeometry() const
{
    return geometry;
}

void AWindow::setGeometry(const Math::IntegerRectangle &geometry)
{
    UIGeometryChangeEvent e(*this, geometry);
    onGeometryChange(e);
}

void AWindow::move(const Math::IntegerVector &position)
{
    UIMoveEvent e(*this, position);
    onMove(e);
}

void AWindow::resize(const Math::IntegerVector &size)
{
    UIResizeEvent e(*this, size);
    onResize(e);
}

const String &AWindow::getTitle() const
{
    return this->title;
}

void AWindow::setTitle(const String &title)
{
    UITitleChangeEvent e(*this, title);
    onTitleChange(e);
}

bool AWindow::getVisible() const
{
    return visible;
}

void AWindow::setVisible(bool visible)
{
    if (visible)
    {
        AShowEvent e(*this);
        onShow(e);
    }
    else
    {
        AHideEvent e(*this);
        onHide(e);
    }
}

WindowFlags AWindow::getFlags() const
{
    return flags;
}

void AWindow::setFlags(const WindowFlags &flags)
{
    UIPropertyChangeEvent<WindowFlags> e(*this, flags);
    onFlagsChange(e);
}

/*template<typename T>
void LoadHardwareObjects()
{
    auto &queue = Legacy::Graphics::HardwareHandle<T>::Storage::getInstance().queue;
    std::vector<Legacy::Graphics::HardwareHandle<T>*> handles;
    while(queue.size() > 0)
    {
        handles.push_back(queue.front());
        queue.pop();
    }
    
    for(auto &handle : handles | rngv::unique)
    {
        if(!handle->isLoaded())
        {
            handle->hardwareObject.load(*static_cast<T*>(handle));
        }
    }
    queue.empty();
}*/

void AWindow::onUpdate(AUpdateEvent &event)
{
    Legacy::Graphics::HardwareHandle<Legacy::Graphics::Texture>::LoadObjects();
    Legacy::Graphics::HardwareHandle<Legacy::Graphics::Material>::LoadObjects();
    Legacy::Graphics::HardwareHandle<Legacy::Graphics::Mesh>::LoadObjects();
    Legacy::Graphics::HardwareHandle<Legacy::Graphics::Canvas>::LoadObjects();

    Legacy::Graphics::API::setBackgroundColor(backgroundColor);
    Legacy::Graphics::API::clear();
    eventChannel.sendEvent(event);

    for (auto &space : spaces)
    {
        space->getCamera()->resolution = geometry.size;
        space->update(event);
    }

    if (GraphicsClock.lastFPSFrame == GraphicsClock.currentFrame)
    {
        UITitleChangeEvent e(*this, fmt::format("{} | FPS {} | Frame {} | Objects {}", getTitle(), GraphicsClock.currentFPS, GraphicsClock.currentFrame, MetaObjectInformation::getInstance().allocatedObjects.size()));
        eventChannel.sendEvent(e);
    }
}

void AWindow::onShow(AShowEvent &event)
{
    if (visible)
    {
        return;
    }
    visible = true;
    eventChannel.sendEvent(event);
    if (onVisibilityChanged)
    {
        onVisibilityChanged(true);
    }
}

void AWindow::onHide(AHideEvent &event)
{
    if (!visible)
    {
        return;
    }
    visible = false;
    eventChannel.sendEvent(event);
    if (onVisibilityChanged)
    {
        onVisibilityChanged(false);
    }
}

void AWindow::onClose(ACloseEvent &event)
{
    visible = false;
    eventChannel.sendEvent(event);
    if (onClosed)
    {
        onClosed();
    }
}

void AWindow::onFlagsChange(UIPropertyChangeEvent<WindowFlags> &event)
{
    flags = event.getValue();
    eventChannel.sendEvent(event);
}

void AWindow::onTitleChange(UITitleChangeEvent &event)
{
    title = event.getValue();
    eventChannel.sendEvent(event);
}

void AWindow::onMove(UIMoveEvent &event)
{
    geometry.position = event.getValue();
    eventChannel.sendEvent(event);
}

void AWindow::onResize(UIResizeEvent &event)
{
    /*if (console)
    {
        console->sendEvent(event);
    }*/
    geometry.size = event.getValue();
    eventChannel.sendEvent(event);
    graphicsContext.setViewPort(Math::IntegerRectangle{ { 0, 0 }, geometry.size });
    Legacy::Graphics::API::setViewport(Math::IntegerRectangle{ { 0, 0 }, geometry.size });
}

void AWindow::onGeometryChange(UIGeometryChangeEvent &event)
{
    geometry = event.getValue();
    eventChannel.sendEvent(event);
    graphicsContext.setViewPort(Math::IntegerRectangle{ { 0, 0 }, geometry.size });
    Legacy::Graphics::API::setViewport(Math::IntegerRectangle{ { 0, 0 }, geometry.size });
}

void AWindow::onTouchDown(AWindowTouchDownEvent &event)
{
    inputEventChannel.sendAcceptableEvent(event);
}

void AWindow::onTouchMove(AWindowTouchMoveEvent &event)
{
    inputEventChannel.sendAcceptableEvent(event);
}

void AWindow::onTouchUp(AWindowTouchUpEvent &event)
{
    inputEventChannel.sendAcceptableEvent(event);
}

void AWindow::onTouchWheel(AWindowTouchWheelEvent &event)
{
    inputEventChannel.sendAcceptableEvent(event);
}

void AWindow::onKeyPress(AWindowKeyPressEvent &event)
{
    auto it = std::find_if(Shortcuts.begin(), Shortcuts.end(), [&](const auto &pair) {
        Core::KeyModifier modifier;
        if (GetKeyState(VK_CONTROL) < 0)
        {
            modifier |= Core::KeyModifier::Ctrl;
        }
        if (GetKeyState(VK_MENU) < 0)
        {
            modifier |= Core::KeyModifier::Alt;
        }
        if (GetKeyState(VK_SHIFT) < 0)
        {
            modifier |= Core::KeyModifier::Shift;
        }
        return pair.first.KeyCode == event.getKey() && pair.first.KeyModifier.value == modifier.value;
    });

    if (it != Shortcuts.end())
    {
        it->second();
        event.accept();
        return;
    }

    /*if (console)
    {
        console->sendEvent(event);
    }*/
    if (!event.isAccepted())
    {
        inputEventChannel.sendAcceptableEvent(event);
    }
}

void AWindow::onKeyRelease(AWindowKeyReleaseEvent &event)
{
    /*if (console)
    {
        console->sendEvent(event);
    }*/
    if (!event.isAccepted())
    {
        inputEventChannel.sendAcceptableEvent(event);
    }
}

void AWindow::onKeyChar(AWindowKeyCharEvent &event)
{
    inputEventChannel.sendAcceptableEvent(event);
}
