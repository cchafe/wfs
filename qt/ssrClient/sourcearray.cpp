#include "sourcearray.h"

// multichannel source for Soundscape Renderer

SourceArray::SourceArray() : xOff(0.1), xInc(0.058),
    yOff(0.1), yInc(0.0)
{
    update();
}

void SourceArray::setX(double x)
{
    xOff = x;
    update();
}

void SourceArray::setY(double y)
{
    yOff = y;
    update();
}

void SourceArray::moveX(double dX)
{
    xOff -= dX;
    update();
}

void SourceArray::moveY(double dY)
{
    yOff += dY;
    update();
}

void SourceArray::update()
{
    for (int i=0; i<nChans; i++)
    {
        x[i] = xOff + i*xInc;
        y[i] = yOff + i*yInc;
    }
}

double SourceArray::getX(int i)
{
    return x[i];
}

double SourceArray::getY(int i)
{
    return y[i];
}
