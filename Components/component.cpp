#include "component.h"

Component::Component()
{
    relativeLocation = {0,0};
    relativeRotation = 0.0f;
}

void Component::setRelativeLocation(QPoint newPosition)
{
    relativeLocation = newPosition;
}

void Component::setRelativeRotation(float newRotation)
{
    relativeRotation = newRotation;
}

QPoint Component::getRelativeLocation()
{
    return relativeLocation;
}

Component::~Component()
{

}
