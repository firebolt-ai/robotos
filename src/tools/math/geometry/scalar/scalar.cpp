#include "scalar.h"

#include <math.h>

Scalar::Scalar()
{
    this->setMagnitude(0.0);
}

Scalar::Scalar(float magnitude)
{
    this->setMagnitude(magnitude);
}

void Scalar::setMagnitude(float magnitude)
{
    this->_magnitude = fabs(magnitude);
}

float Scalar::magnitude()
{
    return this->_magnitude;
}

std::ostream &operator<<(std::ostream &output, const Scalar &s)
{
    output << s._magnitude;
    return output;
}
