//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_CAMERA_H
#define RAYTRACERENDERWINDOWRELEASE_CAMERA_H

#include "../Cartesian3.h"
#include "ray.h"

class camera {
public:
    camera(
            Cartesian3 lookfrom,
            Cartesian3 lookat,
            Cartesian3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double _time0 = 0,
            double _time1 = 0
    );

    ray get_ray(double s, double t) const;

private:
    Cartesian3 origin;
    Cartesian3 lower_left_corner;
    Cartesian3 horizontal;
    Cartesian3 vertical;

    Cartesian3 u, v, w;
    double lens_radius;
    double time0, time1;  // shutter open/close times
};


#endif //RAYTRACERENDERWINDOWRELEASE_CAMERA_H
