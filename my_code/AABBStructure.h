//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_AABBSTRUCTURE_H
#define RAYTRACERENDERWINDOWRELEASE_AABBSTRUCTURE_H


#include "../Cartesian3.h"
#include "ray.h"

//the AABB structure is easy to explain, A and B are two  Axis-Aligned planes. Then
//we can use four planes to construct a box. Then we can calculate if a ray hits
//the AABB box.

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

AABBStructure getSurroundingBox(AABBStructure box0, AABBStructure box1);


#endif //RAYTRACERENDERWINDOWRELEASE_AABBSTRUCTURE_H
