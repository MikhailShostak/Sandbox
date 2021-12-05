#pragma once

#include "Includes/View.gen.h"
#include "Includes/BorderImageView.gen.h"
#include "Core/AStyle.h"
#include "Includes/Alignment.gen.h"

#include "UIMath.h"

namespace UI
{

class Line : public View
{
public:
    typedef Line This;
    typedef View Super;
private:
public:
    virtual SharedReference<Legacy::Graphics::Texture> const &getImage() const;
    virtual void setImage(SharedReference<Legacy::Graphics::Texture> const &image);
    virtual UIOffsets const &getBorder() const;
    virtual void setBorder(UIOffsets const &border);
    Math::IntegerVector getContentSize() const override { return Math::IntegerVector{}; } //TODO: implement
    SharedReference<BorderImageView> backgroundView = std::make_shared<BorderImageView>();
public:
    struct Anchor
    {
        Math::Vector offset;
        SharedReference<View> view;
        Core::Alignment alignments[2];

        Math::Vector getPosition(View &parent) const
        {
            Math::Vector result = offset;

            if (view)
            {
                result += /*view->getPosition() + */Math::Vector{
                    Core::align<float>(0.0f, view->getSize().X, alignments[0]),
                    Core::align<float>(0.0f, view->getSize().Y, alignments[1])
                };

                auto parentSize = parent.getSize().getXY<Math::Vector>();
                result = mapFromLocalSpaceToLocalSpace(*view, parent, result) * parentSize;
            }

            return result;
        }
    };

    Anchor sourceAnchor;
    Anchor destinationAnchor;

    Line()
    {
        backgroundView->setImage(Legacy::Graphics::Texture::getWhiteTexture());
        addView(backgroundView);
        ApplyStyle(*this);
    }

    void onLayout(AUpdateEvent &event) override
    {
        auto sourcePoint = sourceAnchor.getPosition(*getParent());
        auto destinationPoint = destinationAnchor.getPosition(*getParent());

        Math::IntegerVector size = backgroundView->getImage() ? backgroundView->getImage()->getSize() : Math::IntegerVector{};
        size.x = Math::getDistance2(sourcePoint, destinationPoint);
        auto direction = destinationPoint - sourcePoint;

        //size.x = std::max<int32_t>(size.x, std::sqrt(std::pow(destinationPoint.x, 2) + std::pow(destinationPoint.y, 2)) + backgroundView->getBorder().left / 2 + backgroundView->getBorder().right / 2);
        backgroundView->setSize(size);
        backgroundView->setPosition({ 0.0f, -size.getHalfY() });
        setPosition(sourcePoint);
        setRotation(Math::Quaternion::getZRotation(-std::atan2(direction.y, direction.x) * Math::Constants::RadiansToDegreeRatio));
        setSize(size);
    }
};

inline UIOffsets const &Line::getBorder() const
{
    return backgroundView->getBorder();
}

inline void Line::setBorder(UIOffsets const &border)
{
    backgroundView->setBorder(border);
}

inline SharedReference<Legacy::Graphics::Texture> const &Line::getImage() const
{
    return backgroundView->getImage();
}

inline void Line::setImage(SharedReference<Legacy::Graphics::Texture> const &image)
{
    backgroundView->setImage(image);
    requestLayoutUpdate();
}

}
