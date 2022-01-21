//
// Created by 王宇 on 2022/1/19.
//

#include "ray.h"

ray::ray() {}

ray::ray(const Cartesian3 &origin, const Cartesian3 &direction, double time)
        : orig(origin), dir(direction), tm(time)
{}

Cartesian3 ray::origin() const { return orig; }

Cartesian3 ray::direction() const { return dir; }

double ray::time() const { return tm; }

Cartesian3 ray::at(double t) const {
    return orig + t*dir;
}
