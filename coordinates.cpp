#pragma onceA
#include "coordinates.hh"

Coordinates::Coordinates(double x, double y, double z)
                 : x_(x), _y(y), _z(z)
{
}

void Coordinates::Set(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}
