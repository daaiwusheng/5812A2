//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLE_LIST_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLE_LIST_H

#include "HittableObject.h"
#include <vector>

class hittable_list : public HittableObject {
public:
    hittable_list();
    hittable_list(shared_ptr<HittableObject> object);

    void clear();
    void add(shared_ptr<HittableObject> object);

    virtual bool hit(
            const ray& r, double t_min, double t_max, HitRecord& rec) override;
    virtual bool bounding_box(
            double time0, double time1, AABBStructure& output_box) override;

public:
    std::vector<shared_ptr<HittableObject>> objects;
};

#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLE_LIST_H
