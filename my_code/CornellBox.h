//
// Created by 王宇 on 2022/1/20.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_CORNELLBOX_H
#define RAYTRACERENDERWINDOWRELEASE_CORNELLBOX_H

#include "hittable_list.h"
#include "vec3.h"

class cornellBox{
public:
    const double aspect_ratio = 1.0 / 1.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    color background;
    // Camera
    point3 lookfrom;
    point3 lookat;
    vec3 vup;
    double dist_to_focus = 10.0;
    double aperture = 0.0;
    double vfov = 40.0;
    double time0 = 0.0;
    double time1 = 1.0;

    cornellBox();
    hittable_list cornell_box();

};



#endif //RAYTRACERENDERWINDOWRELEASE_CORNELLBOX_H
