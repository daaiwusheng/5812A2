//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_RAY_H
#define RAYTRACERENDERWINDOWRELEASE_RAY_H

#include "../Cartesian3.h"

class ray {
public:
    ray();
    ray(const Cartesian3& origin, const Cartesian3& direction, double time = 0.0);

    Cartesian3 origin() const;
    Cartesian3 direction() const;
    double time() const;

    Cartesian3 at(double t) const;

public:
    Cartesian3 orig;
    Cartesian3 dir;
    double tm;//这个时间,关键用处在于判断光线是否hit object, 并且此时物体的位置也根据这个时间来判断,都对hit产生影响
};

#endif //RAYTRACERENDERWINDOWRELEASE_RAY_H
