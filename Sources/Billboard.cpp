#include "Billboard.h"
#include "Image.h"

Billboard::Billboard(Billboard* const derivative):
    derivative(derivative)
{
}

Fk::Image Billboard::toImage() const
{
    Fk::Image* image{dynamic_cast<Fk::Image*>(derivative)};
    return *image;
}
