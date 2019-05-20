#ifndef SCALAR_H
#define SCALAR_H

#include <iostream>

class Scalar
{
public:
    Scalar();

    Scalar(float magnitude);

    float magnitude();

    void setMagnitude(float magnitude);

    friend std::ostream &operator<<(std::ostream &output, const Scalar &s);

private:
    float
        _magnitude;
};

#endif
