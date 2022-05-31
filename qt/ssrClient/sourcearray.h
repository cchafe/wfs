#ifndef SOURCEARRAY_H
#define SOURCEARRAY_H

#include <QObject>

#define nChans 62

class SourceArray
{
public:
    SourceArray();
    void setX(double x);
    void setY(double y);
    void moveX(double dX);
    void moveY(double dY);
    double getX(int i);
    double getY(int i);
private:
    double xOff;
    double xInc;
    double x[nChans];
    double yOff;
    double yInc;
    double y[nChans];
    void update();
};

#endif // SOURCEARRAY_H
