#pragma once

#include <Foundation>

#include "Graphics/AGraphicsContext.h"
#include "Core/APlatformInegration.h"
#include "Core/ACommonEvents.h"
#include "Core/AFlags.h"
#include "Core/FrameClock.h"
#include "Includes/Shortcut.gen.h"

class ASpace;
class AGraphicsContext;

class AWindowTouchDownEvent;
class AWindowTouchMoveEvent;
class AWindowTouchUpEvent;
class AWindowTouchWheelEvent;

class AWindowKeyPressEvent;
class AWindowKeyReleaseEvent;
class AWindowKeyCharEvent;

enum class WindowFlags
{
    Borderless = 0,
    HasTitle = 1 << 1,
    HasButtons = 1 << 2,
    MinimizeSupport = 1 << 3,
    MaximizeSupport = 1 << 4,
    ResizeSupport = 1 << 5,
    PopUp = 1 << 6,
    Tool = 1 << 7,
    DragAndDropSupport = 1 << 8,

    Window = HasTitle | HasButtons | MinimizeSupport | MaximizeSupport | ResizeSupport,
    ToolWindow = HasTitle | HasButtons | ResizeSupport | Tool,
    Dialog = HasTitle | ResizeSupport,
    Menu = PopUp | Tool
};

ADeclareFlagsOperators(WindowFlags)

class AWindow : public AObject
{
    AGraphicsContext graphicsContext;

    Array<::SharedReference<ASpace>> spaces;

    AColor backgroundColor;
    WindowFlags flags = WindowFlags::Window;
    String title;
    Math::IntegerRectangle geometry;
    bool visible = false;
    AObject *focusedObject = nullptr;

    UniqueReference<AObject> platformWindow;

    struct Storage : public ASingleton<Storage>
    {
        Array<AWindow *> windows;
    };
public:
    Array<AObject*> delegates;

    static const Array<AWindow *> &getWindows() { return Storage::getInstance().windows; }

    Array<APair<Core::Shortcut, ADelegate<void()>>> Shortcuts;

    AEventChannel eventChannel;
    AEventChannel inputEventChannel;

    AWindow();
    ~AWindow();

    ADelegate<void()> onClosed;
    ADelegate<void(bool visible)> onVisibilityChanged;

    const AColor &getBackgroundColor() const
    {
        return backgroundColor;
    }
    void setBackgroundColor(const AColor &color)
    {
        backgroundColor = color;
    }

    const Array<::SharedReference<ASpace>> &getSpaces() const;
    void setSpaces(const Array<::SharedReference<ASpace>> &spaces);
    void addSpace(const ::SharedReference<ASpace> &space);
    void insertSpace(const ::SharedReference<ASpace> &space, size_t index);
    void removeSpace(const ::SharedReference<ASpace> &space);

    void show();
    void hide();
    void close();
    const Math::IntegerRectangle &getGeometry() const;
    void setGeometry(const Math::IntegerRectangle &geometry);
    void move(const Math::IntegerVector &position);
    void resize(const Math::IntegerVector &size);
    const String &getTitle() const;
    void setTitle(const String &title);
    bool getVisible() const;
    void setVisible(bool visible);
    WindowFlags getFlags() const;
    void setFlags(const WindowFlags &flags);

    AObject *getFocus() const
    {
        return focusedObject;
    }

    void setFocus(AObject &object)
    {
        if (focusedObject == &object)
        {
            return;
        }

        if (focusedObject)
        {
            AFocusOutEvent e(*this);
            focusedObject->sendEvent(e);
        }
        focusedObject = &object;
        AFocusInEvent e(*this);
        focusedObject->sendEvent(e);
    }

    void removeFocus(AObject &object)
    {
        if (focusedObject == &object)
        {
            AFocusOutEvent e(*this);
            focusedObject->sendEvent(e);
            focusedObject = nullptr;
        }
    }

    void removeFocus()
    {
        if (focusedObject != nullptr)
        {
            AFocusOutEvent e(*this);
            focusedObject->sendEvent(e);
            focusedObject = nullptr;
        }
    }

protected:

    void onUpdate(AUpdateEvent &event);
    void onShow(AShowEvent &event);
    void onHide(AHideEvent &event);
    void onClose(ACloseEvent &event);
    void onTitleChange(UITitleChangeEvent &event);
    void onFlagsChange(UIPropertyChangeEvent<WindowFlags> &event);
    void onMove(UIMoveEvent &event);

    void onResize(UIResizeEvent &event);
    void onGeometryChange(UIGeometryChangeEvent &event);

	void onTouchDown(AWindowTouchDownEvent &event);
	void onTouchMove(AWindowTouchMoveEvent &event);
    void onTouchUp(AWindowTouchUpEvent &event);
    void onTouchWheel(AWindowTouchWheelEvent &event);

    void onKeyPress(AWindowKeyPressEvent &event);
    void onKeyRelease(AWindowKeyReleaseEvent &event);
    void onKeyChar(AWindowKeyCharEvent &event);

};
