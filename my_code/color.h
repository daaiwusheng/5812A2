//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_COLOR_H
#define RAYTRACERENDERWINDOWRELEASE_COLOR_H

#include "../Cartesian3.h"
#include <fstream>
#include <iostream>
#include "../RGBAValue.h"

RGBAValue getColor(Cartesian3 pixelColor, int samplesPerPixel);

#endif //RAYTRACERENDERWINDOWRELEASE_COLOR_H
