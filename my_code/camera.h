//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_CAMERA_H
#define RAYTRACERENDERWINDOWRELEASE_CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera {
public:
    camera(
            point3 lookfrom,
            point3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double _time0 = 0,
            double _time1 = 0
    );

    ray get_ray(double s, double t) const;

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    vec3 u, v, w;
    double lens_radius;
    double time0, time1;  // shutter open/close times
};


#endif //RAYTRACERENDERWINDOWRELEASE_CAMERA_H
