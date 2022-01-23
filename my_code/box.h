//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_BOX_H
#define RAYTRACERENDERWINDOWRELEASE_BOX_H

#include "../Cartesian3.h"
#include "aarect.h"
#include "hittable_list.h"

class box : public HittableObject  {
public:
    box() {}
    box(const Cartesian3& p0, const Cartesian3& p1, shared_ptr<Material> ptr);

    virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& rec) override;

    virtual bool bounding_box(double time0, double time1, AABBStructure& output_box) override;

public:
    Cartesian3 box_min;
    Cartesian3 box_max;
    hittable_list sides;
};


#endif //RAYTRACERENDERWINDOWRELEASE_BOX_H
