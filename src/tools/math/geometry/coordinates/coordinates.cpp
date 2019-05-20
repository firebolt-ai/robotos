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

#include "coordinates.h"

#include "../vector/vector.h"

#include <math.h>

Coordinate::Coordinate()
{
    this->_x = 0.0;
    this->_y = 0.0;
}

Coordinate::Coordinate(float x, float y)
{
    this->_x = x;
    this->_y = y;
}

float Coordinate::x()
{
    return this->_x;
}

float Coordinate::y()
{
    return this->_y;
}

Vector
Coordinate::getVector(Coordinate target)
{
    float dx = (target.x() - this->_x);
    float dy = (target.y() - this->_y);

    float length = sqrt((dx * dx) + (dy * dy));
    float direction = atan2(dy, dx);

    return Vector(length, direction);
}

std::ostream &operator<<(std::ostream &output, const Coordinate &c)
{
    output << c._x << "," << c._y;
    return output;
}
