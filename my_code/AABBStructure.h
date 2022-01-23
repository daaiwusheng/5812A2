//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_AABBSTRUCTURE_H
#define RAYTRACERENDERWINDOWRELEASE_AABBSTRUCTURE_H


#include "../Cartesian3.h"
#include "ray.h"

class AABBStructure {
public:
    AABBStructure();
    AABBStructure(const Cartesian3& a, const Cartesian3& b);

    Cartesian3 min() const;
    Cartesian3 max() const;

    bool hit(const ray& r, double t_min, double t_max) const;

    Cartesian3 minimum;
    Cartesian3 maximum;
};

AABBStructure surrounding_box(AABBStructure box0, AABBStructure box1);


#endif //RAYTRACERENDERWINDOWRELEASE_AABBSTRUCTURE_H
