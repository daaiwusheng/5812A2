//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLELIST_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLELIST_H

#include "HittableObject.h"
#include <vector>

class HittableList : public HittableObject {
public:
    HittableList();
    HittableList(shared_ptr<HittableObject> object);

    void clear();
    void add(shared_ptr<HittableObject> object);

    virtual bool hitTest(
            const ray& r, double t_min, double t_max, HitRecord& rec) override;
    virtual bool boundingBox(
            double time0, double time1, AABBStructure& output_box) override;

public:
    std::vector<shared_ptr<HittableObject>> objects;
};

#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLELIST_H
