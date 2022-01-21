//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_AABB_H
#define RAYTRACERENDERWINDOWRELEASE_AABB_H

//#include "vec3.h"
#include "../Cartesian3.h"
#include "ray.h"

class aabb {
public:
    aabb();
    aabb(const Cartesian3& a, const Cartesian3& b);

    Cartesian3 min() const;
    Cartesian3 max() const;

    bool hit(const ray& r, double t_min, double t_max) const;

    Cartesian3 minimum;
    Cartesian3 maximum;
};

aabb surrounding_box(aabb box0, aabb box1);


#endif //RAYTRACERENDERWINDOWRELEASE_AABB_H
