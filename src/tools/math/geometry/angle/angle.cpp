/*
The MIT License

Copyright (c) 2019 - Present Firebolt, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "angle.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <iostream>

Angle::Angle()
{
    this->setPhi(0.0);
}

Angle::Angle(float phi, bool degrees)
{
    if (degrees)
        this->setPhi(phi * (180.0 / M_PI));
    else
        this->setPhi(phi);
}

void Angle::setPhi(float phi)
{

    float newPhi = fmod(phi, 2 * M_PI);

    if (newPhi > M_PI)
        this->_phi = newPhi - (2 * M_PI);
    else if (newPhi < -M_PI)
        this->_phi = newPhi + (2 * M_PI);
    else
        this->_phi = newPhi;
}

float Angle::phi()
{
    return this->_phi;
}

float Angle::degrees()
{
    return (this->_phi * 180) / M_PI;
}

void Angle::reverse()
{
    this->setPhi(this->_phi + M_PI);
}

Angle Angle::deltaAngle(Angle angle)
{
    return Angle(angle.phi() - this->_phi);
}

std::ostream &operator<<(std::ostream &output, const Angle &a)
{
    output << "ø" << a._phi;
    return output;
}
