//
// Created by 王宇 on 2022/1/23.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_MYSCENE_H
#define RAYTRACERENDERWINDOWRELEASE_MYSCENE_H

#include "hittable_list.h"
#include "../Cartesian3.h"

class MyOwnScene{
public:
    const double aspect_ratio = 1.0 / 1.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    Cartesian3 background;
    // Camera
    Cartesian3 lookfrom;
    Cartesian3 lookat;
    Cartesian3 vup;
    double dist_to_focus = 10.0;
    double aperture = 0.0;
    double vfov = 40.0;
    double time0 = 0.0;
    double time1 = 1.0;

    MyOwnScene();
    hittable_list getMyOwnScene();

};



#endif //RAYTRACERENDERWINDOWRELEASE_MYSCENE_H
