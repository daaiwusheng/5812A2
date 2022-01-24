//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_UTILITY_H
#define RAYTRACERENDERWINDOWRELEASE_UTILITY_H

#include <limits>


// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

double degreesToRadians(double degrees);
double randomDouble();
double randomDoubleInRange(double min, double max);
double clamp(double x, double min, double max);
int random_int(int min, int max);

#endif //RAYTRACERENDERWINDOWRELEASE_UTILITY_H
