//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_RAY_H
#define RAYTRACERENDERWINDOWRELEASE_RAY_H

#include "vec3.h"

class ray {
public:
    ray();
    ray(const point3& origin, const vec3& direction, double time = 0.0);

    point3 origin() const;
    vec3 direction() const;
    double time() const;

    point3 at(double t) const;

public:
    point3 orig;
    vec3 dir;
    double tm;//这个时间,关键用处在于判断光线是否hit object, 并且此时物体的位置也根据这个时间来判断,都对hit产生影响
};

#endif //RAYTRACERENDERWINDOWRELEASE_RAY_H
