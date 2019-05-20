#ifndef VOLUMECOORDINATE_H
#define VOLUMECOORDINATE_H

#include "../coordinates.h"
#include <iostream>

class VolumeCoordinate : public Coordinate
{
public:
    VolumeCoordinate();
    VolumeCoordinate(float x, float y, float z);

    float z();

    friend std::ostream &operator<<(std::ostream &output, const VolumeCoordinate &vc);

private:
    float
        _z;
};

#endif
