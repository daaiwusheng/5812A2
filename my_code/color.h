//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_COLOR_H
#define RAYTRACERENDERWINDOWRELEASE_COLOR_H

#include "vec3.h"
#include <fstream>
#include <iostream>
#include "../RGBAValue.h"


struct color_record {
    char r = 0;
    char g = 0;
    char b = 0;
};


void write_color(std::ostream &out, color pixel_color);

void write_color(std::ofstream &out, color pixel_color);

void write_color(std::ofstream &out, color pixel_color, int samples_per_pixel);

RGBAValue get_color(color pixel_color, int samples_per_pixel);

#endif //RAYTRACERENDERWINDOWRELEASE_COLOR_H
