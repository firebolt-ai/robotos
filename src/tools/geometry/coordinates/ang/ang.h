#ifndef ANGULARCOORDINATE_H
#define ANGULARCOORDINATE_H

#include "../coordinates.h"
#include "../angle/angle.h"

#include <iostream>

class AngularCoordinate : public Coordinate, public Angle
{
public:
    AngularCoordinate();

    AngularCoordinate(float x, float y, float phi);

    friend std::ostream &operator<<(std::ostream &output, const AngularCoordinate &ac);
};

#endif