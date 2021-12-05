#pragma once

#include <Foundation>

class ACamera
{
    struct CameraManager : public ASingleton<CameraManager>
    {
        Array<ACamera *> cameras;
    };

    static Array<ACamera *> &cameras()
    {
        return CameraManager::getInstance().cameras;
    }
public:
    static void pushCamera(ACamera &camera)
    {
        cameras().push_back(&camera);
    }

    static void popCamera()
    {
        cameras().pop_back();
    }

    static ACamera *getCurrentCamera()
    {
        AAssert(!cameras().empty(), "There's no a set camera");
        return cameras().back();
    }

    float viewLenght = 0.0f;
    Math::IntegerVector resolution;

    Math::Transform transform;

    virtual Math::Matrix getViewMatrix() const
    {
        auto transform = this->transform;
        transform.reflect();
        return Math::Matrix::getTranslation(transform.Position) * transform.Rotation.toMatrix();
    }

    virtual Math::Matrix getProjectionMatrix()const = 0;

    Math::Matrix getMatrix() const
    {
        return getViewMatrix() * getProjectionMatrix();
    }

};
