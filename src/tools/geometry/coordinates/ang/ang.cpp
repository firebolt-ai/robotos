#include "ang.h"
#include "../coordinates.h"
#include <iostream>

AngularCoordinate::AngularCoordinate()
    : Coordinate::Coordinate(),
      Angle::Angle()
{
}

AngularCoordinate::AngularCoordinate(float x, float y, float phi)
    : Coordinate::Coordinate(x, y),
      Angle::Angle(phi)
{
}

std::ostream &operator<<(std::ostream &output, const AngularCoordinate &ac)
{
    output << (Coordinate)ac << " " << (Angle)ac;
    return output;
}