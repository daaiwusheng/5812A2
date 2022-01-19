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

double degrees_to_radians(double degrees);
double random_double();
double random_double(double min, double max);
double clamp(double x, double min, double max);
int random_int(int min, int max);

#endif //RAYTRACERENDERWINDOWRELEASE_UTILITY_H
