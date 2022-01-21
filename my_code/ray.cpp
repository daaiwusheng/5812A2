//
// Created by 王宇 on 2022/1/19.
//

#include "ray.h"

ray::ray() {}

ray::ray(const point3 &origin, const vec3 &direction, double time)
        : orig(origin), dir(direction), tm(time)
{}

point3 ray::origin() const { return orig; }

vec3 ray::direction() const { return dir; }

double ray::time() const { return tm; }

point3 ray::at(double t) const {
    return orig + t*dir;
}