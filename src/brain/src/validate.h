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
#ifndef ROBOT_VALIDATION_H
#define ROBOT_VALIDATION_H

#include <algorithm>
#include <atomic>
#include <exception>
#include <map>
#include <memory>
#include <set>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

class Text;
class Word;
class Image;
struct ImageAlgorithm;

int image() {
    // TODO: Create the image validation algorithm
    #ifndef SERVE_IMAGE
    #define SERVE_IMAGE
    #endif
    uint UTIL_isValidImage(const unsigned char h[5]);
}


int word() {
    // TODO: Create the word validation algorithm
}

int text() {
    // TODO: Create the text validation algorithm
}

void ThreadCheck(int thread);
bool ThreadRunning();

#endif // ROBOT_VALIDATION_H