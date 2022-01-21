//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_BOX_H
#define RAYTRACERENDERWINDOWRELEASE_BOX_H


#include "aarect.h"
#include "hittable_list.h"

class box : public hittable  {
public:
    box() {}
    box(const point3& p0, const point3& p1, shared_ptr<material> ptr);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

public:
    point3 box_min;
    point3 box_max;
    hittable_list sides;
};


#endif //RAYTRACERENDERWINDOWRELEASE_BOX_H