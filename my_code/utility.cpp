//
// Created by 王宇 on 2022/1/19.
//

#include "utility.h"
#include <cmath>

double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

double randomDouble() {
    // Returns a random real value in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double randomDoubleInRange(double min, double max) {
    // Returns a random real value in [min,max).
    return min + (max-min) * randomDouble();
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(randomDoubleInRange(min, max + 1));
}