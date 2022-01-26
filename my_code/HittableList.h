//
// Created by 王宇 on 2022/1/19.
//

#ifndef RAYTRACERENDERWINDOWRELEASE_HITTABLELIST_H
#define RAYTRACERENDERWINDOWRELEASE_HITTABLELIST_H

#include "HittableObject.h"
#include <vector>

//this class is also a subclass of HittableObject,
//but it has a container,which can store all hittable objects.
//Then we can test if one of them is hit by the Ray.
//the key method is hitTest.

class HittableList : public HittableObject {
public:
    HittableList();
    HittableList(shared_ptr<HittableObject> object);

    void add(shared_ptr<HittableObject> object);

    virtual bool hitTest(const Ray& r, double t_min, double t_max, HitRecord& rec) override;
    virtual bool boundingBox(double time0, double time1, AABBStructure& outputBox) override;

public:
    std::vector<shared_ptr<HittableObject>> objectsInScene;
};

#endif //RAYTRACERENDERWINDOWRELEASE_HITTABLELIST_H
