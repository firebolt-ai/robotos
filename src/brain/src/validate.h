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

int image() {
    // TODO: Create the image validation algorithm
    #ifndef SERVE_IMAGE
    #define SERVE_IMAGE
    #endif
}

int word() {
    // TODO: Create the word validation algorithm
}

int text() {
    // TODO: Create the text validation algorithm
}

#endif // ROBOT_VALIDATION_H