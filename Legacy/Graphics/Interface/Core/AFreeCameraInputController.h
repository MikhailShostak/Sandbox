#pragma once

#include "AInputController.h"

class AFreeCameraInputController : public AInputController
{
    ACamera &camera;
    Math::IntegerVector lastPosition;

    float xAxis = 0;
    float yAxis = 0;

    bool forwardVel = false;
    bool backwardVel = false;
    bool leftVel = false;
    bool rightVel = false;
    bool sprint = false;

    bool isCursorLocked = false;
    Math::IntegerVector lastCursorPosition;

    Math::Vector velocity;
public:
    float xAxisSensetivity = 0.1f;
    float yAxisSensetivity = 0.1f;

    float speed = 0.04f;
    float sprintFactor = 5.0f;
    float damping = 0.1f;
    AFreeCameraInputController(AWindow &window, ACamera &camera):
        AInputController(window),
        camera(camera)
    {

    }

protected:

    void onTouchDown(AWindowTouchDownEvent &event) override
    {
        if (!event.isPressed(ATouchID::RightMouseButton) || isCursorLocked)
        {
            return;
        }

        hideCursor();
        lastPosition = event.getPosition();
        isCursorLocked = true;
        lastCursorPosition = getCursorPosition();

        event.accept();
    }

    void onTouchMove(AWindowTouchMoveEvent &event) override
    {
        if (!event.isPressed(ATouchID::RightMouseButton))
        {
            return;
        }

        if (isCursorLocked)
        {
            Math::IntegerVector delta = event.getPosition() - lastPosition;
            lastPosition = event.getPosition();
            xAxis += delta.y * xAxisSensetivity;
            yAxis += delta.x * yAxisSensetivity;

            camera.transform.Rotation = Math::Quaternion::getXRotation(xAxis) * Math::Quaternion::getYRotation(yAxis);

            Math::IntegerVector windowSize = window.getGeometry().size;
            if (delta.x > (windowSize.x / 4) && delta.y > (windowSize.y / 4))
            {
                ALogMessage("Controller", "Warning: %d %d - mouse delta is too high", delta.x, delta.y);
            }
            if (lastPosition.x < 0)
            {
                Math::IntegerVector p = getCursorPosition();
                p.x += windowSize.x;
                lastPosition.x += windowSize.x;
                setCursorPosition(p);
            }
            else if (lastPosition.x >= windowSize.x)
            {
                Math::IntegerVector p = getCursorPosition();
                p.x -= windowSize.x;
                lastPosition.x -= windowSize.x;
                setCursorPosition(p);
            }
            else if (lastPosition.y < 0)
            {
                Math::IntegerVector p = getCursorPosition();
                p.y += windowSize.y;
                lastPosition.y += windowSize.y;
                setCursorPosition(p);
            }
            else if (lastPosition.y >= windowSize.y)
            {
                Math::IntegerVector p = getCursorPosition();
                p.y -= windowSize.y;
                lastPosition.y -= windowSize.y;
                setCursorPosition(p);
            }

            event.accept();
        }
    }

    void onTouchUp(AWindowTouchUpEvent &event) override
    {
        if (event.getTouchID() != ATouchID::RightMouseButton)
        {
            return;
        }

        if (isCursorLocked)
        {
            showCursor();
            isCursorLocked = false;
            setCursorPosition(lastCursorPosition);

            event.accept();
        }
    }

    void onKeyPress(AWindowKeyPressEvent &event) override
    {
        switch (event.getKey())
        {
        case 'w':
        case 'W':
            forwardVel = true;
            break;
        case 's':
        case 'S':
            backwardVel = true;
            break;
        case 'a':
        case 'A':
            leftVel = true;
            break;
        case 'd':
        case 'D':
            rightVel = true;
            break;
        case 16: //shift
            sprint = true;
            break;
        }
        updateVelocity();

        event.accept();
    }

    void onKeyRelease(AWindowKeyReleaseEvent &event) override
    {
        switch (event.getKey())
        {
        case 'w':
        case 'W':
            forwardVel = false;
            break;
        case 's':
        case 'S':
            backwardVel = false;
            break;
        case 'a':
        case 'A':
            leftVel = false;
            break;
        case 'd':
        case 'D':
            rightVel = false;
            break;
        case 16: //shift
            sprint = false;
            break;
        }
        updateVelocity();

        event.accept();
    }

    void onUpdate(AUpdateEvent &event) override
    {
        if (forwardVel == backwardVel && rightVel == leftVel)
        {
            velocity = velocity - velocity * damping;
        }
        Math::Quaternion rotation = camera.transform.Rotation.getNormalized();
        camera.transform.Position += rotation.getRotatedVector(velocity);
    }

private:

    void updateVelocity()
    {
        if (forwardVel == backwardVel && rightVel == leftVel)
        {
            return;
        }
        velocity = Math::Vector{ (float)rightVel - (float)leftVel, 0.0f, (float)backwardVel - (float)forwardVel }.getNormalized3() * (sprint ? speed * sprintFactor : speed);
    }
};
