//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_COLOR_H
#define RAYTRACERENDERWINDOWRELEASE_COLOR_H

#include "../Cartesian3.h"
#include <fstream>
#include <iostream>
#include "../RGBAValue.h"


struct color_record {
    char r = 0;
    char g = 0;
    char b = 0;
};


void write_color(std::ostream &out, Cartesian3 pixel_color);

void write_color(std::ofstream &out, Cartesian3 pixel_color);

void write_color(std::ofstream &out, Cartesian3 pixel_color, int samples_per_pixel);

RGBAValue get_color(Cartesian3 pixel_color, int samples_per_pixel);

#endif //RAYTRACERENDERWINDOWRELEASE_COLOR_H
