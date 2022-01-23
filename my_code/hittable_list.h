//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLE_LIST_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

class hittable_list : public hittable {
public:
    hittable_list();
    hittable_list(shared_ptr<hittable> object);

    void clear();
    void add(shared_ptr<hittable> object);

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) override;
    virtual bool bounding_box(
            double time0, double time1, aabb& output_box) override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLE_LIST_H
